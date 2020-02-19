#include <OSCalls.h>
#include <x86.h>
#include <Core.h>
#include <CI-Process.h>

extern volatile uint32 Kg_nLocksHeld;
bool bCreateThreadStack = false;
volatile bool Kg_bTaskSwitchWaiting = false;
uint32 Kg_nTaskESP;
uint16 Kg_nTaskSS;

// Prototypes
bool ProcessManager_Preempt( void );
uint32 ProcessManager_CreateProcess( char * pszName );
uint32 ProcessManager_CreateThread( K_sObject_t *psProcessObject, uint32 nEIP );
uint32 ProcessManager_Handler( uint32 nCall, void * pData );

// Calls
enum {
    CREATEPROCESS,
    CREATETHREAD,
    SLEEP,
    AWAKEN,
    RELINQUISH
};

void ProcessManager_Init() {

    // Initialise kernel variables
    Kg_sKernel.m_nProcessID = 0;
    Kg_sKernel.m_nThreadID = 0;

    // Create running process (kernel process)
    ProcessManager_CreateProcess( "Kernel" );
    Kg_sKernel.m_psRunningProcess = ObjectManager_SearchInClass( NULL, KOBJECT_OBJ_PROCESS );
    Kg_sKernel.m_psRunningProcessID = 0;

    // Set process settings
    K_sProcess_t *psProcess = ( K_sProcess_t * ) Kg_sKernel.m_psRunningProcess->m_pData;
    psProcess->m_psAllocator = &Kg_sKernel.m_psAllocator;
    psProcess->m_nSS = KERNELDS;
    psProcess->m_nCS = KERNELCS;
    psProcess->m_nDS = KERNELDS;
    psProcess->m_nES = KERNELDS;
    psProcess->m_nFS = KERNELDS;
    psProcess->m_nGS = KERNELDS;
    psProcess->m_nSS = KERNELDS;

    // Create thread (kernel thread, eventually become idle loop)
    ProcessManager_CreateThread( Kg_sKernel.m_psRunningProcess, 0 );
    Kg_sKernel.m_psRunningThread = ObjectManager_SearchInClass( NULL, KOBJECT_OBJ_THREAD );
    Kg_sKernel.m_psRunningThreadID = 0;

    // Set thread as running (because it is) and set stack to current kernel stack
    K_sThread_t * psThread = ( K_sThread_t * ) Kg_sKernel.m_psRunningThread->m_pData;
    psThread->m_nState = THREAD_RUNNING;

    // Future threads will need stack creation
    bCreateThreadStack = true;

    // Setup TSS for switching to kernel
    K_sTSS_t *m_sTSS = &Kg_sKernel.m_sTSS;
    m_sTSS->cs = KERNELCS;
    m_sTSS->ds = KERNELDS;
    m_sTSS->es = KERNELDS;
    m_sTSS->fs = KERNELDS;
    m_sTSS->gs = KERNELDS;
    m_sTSS->ss = KERNELDS;
    m_sTSS->ss0 = KERNELDS;
    m_sTSS->ss1 = 0;
    m_sTSS->ss2 = 0;
    m_sTSS->cr3 = ( uint32 ) Kg_sKernel.m_pnPageDirectory;
    Descriptor_SetBase( TSS, ( uint32 ) m_sTSS );
    Descriptor_SetLimit( TSS, sizeof( K_sTSS_t ) );
    Descriptor_SetAccess( TSS, 0x89 );

    // Set first TSS entry
    LoadTaskRegister( TSS );

    // Attach scheduler to timer
    TimerManager_AttachTimerHandler( "Scheduler", 0, ( TimerHandler * ) ProcessManager_Preempt );

    // Add process manager to module list
    ModuleManager_CreateModule( "ProcessManager", ProcessManager_Handler );
    ModuleManager_CreateModuleCall( "ProcessManager", "CreateProcess", CREATEPROCESS );
    ModuleManager_CreateModuleCall( "ProcessManager", "CreateThread", CREATETHREAD );
    ModuleManager_CreateModuleCall( "ProcessManager", "Sleep", SLEEP );
    ModuleManager_CreateModuleCall( "ProcessManager", "Awaken", AWAKEN );
    ModuleManager_CreateModuleCall( "ProcessManager", "Relinquish", RELINQUISH );

    KPrint( KDEBUG, "PROCESSES", "Scheduler initialised\n" );
}

uint32 ProcessManager_CreateProcess( char * pszName ) {

    // Create object
    ObjectManager_Lock();
    K_sObject_t * psObject = ObjectManager_CreateObject( KOBJECT_OBJ_PROCESS, sizeof( K_sProcess_t ), pszName );
    psObject->m_nTypeIndex = Kg_sKernel.m_nProcessID;
    ObjectManager_Unlock();

    // Create process struct
    K_sProcess_t *psProcess = ( K_sProcess_t * ) psObject->m_pData;
    psProcess->m_nBasePriority = KPROCESS_THREADPRIORITY_NORMAL;
    psProcess->m_nID = Kg_sKernel.m_nProcessID++;
    psProcess->m_nThreadCount = 0;
    psProcess->m_psAllocator = NULL;

    return NULL;
}

uint32 ProcessManager_CreateThread( K_sObject_t *psProcessObject, uint32 nEIP ) {

    // Create object
    ObjectManager_Lock();
    K_sObject_t * psObject = ObjectManager_CreateObject( KOBJECT_OBJ_THREAD, sizeof( K_sThread_t ), "" );
    psObject->m_nTypeIndex = Kg_sKernel.m_nThreadID;
    ObjectManager_Unlock();

    // Create thread struct
    K_sThread_t * psThread = ( K_sThread_t * ) psObject->m_pData;
    psThread->m_psProcess = psProcessObject;
    K_sProcess_t *psProcess = ( K_sProcess_t * ) psProcessObject->m_pData;
    psThread->m_nBasePriority = psProcess->m_nBasePriority;
    psThread->m_nCurrentPriority = psProcess->m_nBasePriority;
    psThread->m_nState = THREAD_NEW;
    psThread->m_nID = Kg_sKernel.m_nThreadID++;
    psThread->m_nCPUTime = 0;
    psThread->m_psMessagePort = NULL;
    psThread->m_nNestDepth = 1;

    // Set thread name
    snprintf( ( char * ) & psObject->m_szName, KOBJECT_NAMELENGTH, "Thread %u", psThread->m_nID );

    // Create page for stack
    if ( bCreateThreadStack == true ) {

        void * nStackSpace = MemoryManager_KAlloc ( K_SCHEDULER_KERNELTHREADSTACKSIZE ) + K_SCHEDULER_KERNELTHREADSTACKSIZE;

        // Set stack (register) settings
        K_sCallStack_t *psStack = ( K_sCallStack_t * ) psThread->m_nESP[ 0 ] = ( ( uint32 ) nStackSpace ) - sizeof( K_sCallStack_t );
        psThread->m_nSS = psProcess->m_nSS;
        psStack->eflags = 0x203246;
        psStack->eip = nEIP;
        psStack->cs = psProcess->m_nCS;
        psStack->ds = psProcess->m_nDS;
        psStack->es = psProcess->m_nES;
        psStack->fs = psProcess->m_nFS;
        psStack->gs = psProcess->m_nGS;
        psStack->ss = psProcess->m_nSS;
        psStack->eax = 0;
        psStack->ebx = 0;
        psStack->ecx = 0;
        psStack->edx = 0;
        psStack->ebp = 0;
        psStack->esi = 0;
        psStack->edi = 0;
    }

    // Set process thread count
    psProcess->m_nThreadCount++;

    return NULL;
}

void ProcessManager_UpdateThreads() {

    // Search for thread
    K_sObject_t * psObject = NULL;
    while ( 1 ) {

        // Get next thread
        psObject = ObjectManager_SearchInClass( psObject, KOBJECT_OBJ_THREAD );
        if ( psObject == NULL ) {
            break;
        }

        // Get pointer to thread data
        K_sThread_t * psThread = ( K_sThread_t * ) psObject->m_pData;

        // And process threads
        if ( psThread->m_nState == THREAD_NEW ) { // See if new thread

            // Set into ready state
            psThread->m_nState = THREAD_READY;

        } else if ( psThread->m_nState == THREAD_SLEEPING ) {       // See if sleeper

            // See if it wants to sleep forever
            if ( psThread->m_nSleepTimeOut != KPROCESS_SLEEPFOREVER ) {

                // Decrement timeout
                psThread->m_nSleep--;

                // Awaken if necessary
                if ( psThread->m_nSleep == 0 ) {
                    psThread->m_nState = THREAD_READY;
                }
            }

        } else if ( psThread->m_nState == THREAD_RUNNING ) {
            psThread->m_nCPUTime++;
        }
    }
}

K_sObject_t *ProcessManager_GetNextThread( K_sObject_t *psThreadObject ) {

    // Local copy of thread object
    K_sObject_t * psThreadObjectLocal = psThreadObject;

    while ( 1 ) {

        // Get next thread
        psThreadObjectLocal = ObjectManager_SearchInClass( psThreadObjectLocal, KOBJECT_OBJ_THREAD );

        // If we are at end, go back to beginning
        if ( psThreadObjectLocal == NULL ) {
            psThreadObjectLocal = ObjectManager_SearchInClass( NULL, KOBJECT_OBJ_THREAD );
        }

        // Check we haven't looped round to the start
        if ( psThreadObjectLocal == psThreadObject )
            break;

        // See if this thread is in a state to run
        K_sThread_t * psThread = ( K_sThread_t * ) psThreadObjectLocal->m_pData;
        if ( psThread->m_nState == THREAD_READY )
            break;

    }
    return psThreadObjectLocal;
}

uint32 ProcessManager_NextThread( ) {

    // Update threads (i.e. awaken sleepers etc)
    ObjectManager_Lock();
    Kg_bTaskSwitchWaiting = false;
    ProcessManager_UpdateThreads();

    // Get index of currently running thread
    K_sObject_t *psCurrentThreadObject = Kg_sKernel.m_psRunningThread;
    K_sThread_t * psCurrentThread = ( K_sThread_t * ) psCurrentThreadObject->m_pData;

    // Round robin scheduler, choose next thread
    K_sObject_t * psNewThreadObject = ProcessManager_GetNextThread( psCurrentThreadObject );
    K_sThread_t * psNewThread = ( K_sThread_t * ) psNewThreadObject->m_pData;

    // See if no new thread to execute
    if ( psCurrentThreadObject == psNewThreadObject ) {
        ObjectManager_Unlock();
        return NULL;
    }

    // Mark new thread as running and previous as ready (if running) and set current thread
    if ( psCurrentThread->m_nState == THREAD_RUNNING ) {
        psCurrentThread->m_nState = THREAD_READY;
    }
    psNewThread->m_nState = THREAD_RUNNING;
    Kg_sKernel.m_psRunningThread = psNewThreadObject;
    Kg_sKernel.m_psRunningThreadID = psNewThread->m_nID;

    // Set current stack
    Kg_nTaskSS = psNewThread->m_nSS;
    Kg_nTaskESP = psNewThread->m_nESP[ psNewThread->m_nNestDepth - 1 ];
    Kg_sKernel.m_psCallStack = ( K_sCallStack_t * ) Kg_nTaskESP;

    // Unlock
    ObjectManager_Unlock();

    return NULL;
}

extern K_sLock_t sMemoryLock;
extern K_sLock_t sObjectLock;

bool ProcessManager_Preempt( ) {

    // Show current thread in top right
    Kg_pConsoleVideo[ 158 ] = ( Kg_sKernel.m_psRunningThreadID & 0xFF ) + 48;
    Kg_pConsoleVideo[ 159 ] = 15;

    static uint32 nTimer = 0;

    nTimer++;
    if ( nTimer == 1000 ) {
        nTimer = 0;
        // Can we switch?
        if ( Kg_nLocksHeld == 0 ) {
            ProcessManager_NextThread();
        } else {
            Kg_bTaskSwitchWaiting = true;
            KPrint( KDEBUG, "SWITCH", "Can't task switch - [%u %u %u]", Kg_nLocksHeld, sMemoryLock.m_sSpinlock, sObjectLock.m_sSpinlock );
            halt();
        }
    }

    return true;
}

void ProcessManager_SaveContext( ) {

    if ( bCreateThreadStack == true ) {

        // Get index of currently running thread
        K_sObject_t * psThreadObject = Kg_sKernel.m_psRunningThread;
        K_sThread_t * psThread = ( K_sThread_t * ) psThreadObject->m_pData;

        // Check we havem't exceeded nesting depth, this is fatal
        if ( psThread->m_nNestDepth == K_NESTDEPTH ) {
            KPrint( KSEVERE, "PROCESSES", "Kernel nesting exceeded maximum - Halting\n" );
            halt();
        }

        // Save nested stack info
        psThread->m_nSS = Kg_nTaskSS;
        psThread->m_nESP[ psThread->m_nNestDepth ] = Kg_nTaskESP;

        // Increment nest counter
        psThread->m_nNestDepth++;
    }

    // Set current stack
    Kg_sKernel.m_psCallStack = ( K_sCallStack_t * ) Kg_nTaskESP;
}

void ProcessManager_RestoreContext( ) {

    if ( bCreateThreadStack == true ) {

        // Get index of currently running thread
        K_sObject_t * psThreadObject = Kg_sKernel.m_psRunningThread;
        K_sThread_t * psThread = ( K_sThread_t * ) psThreadObject->m_pData;

        // Decrement nest counter
        psThread->m_nNestDepth--;

        Kg_nTaskSS = psThread->m_nSS;
        Kg_nTaskESP = psThread->m_nESP[ psThread->m_nNestDepth ];
    }
}

uint32 ProcessManager_CreateThreadCall( KProcess_sCreateThread_t * psData ) {
    return ProcessManager_CreateThread( Kg_sKernel.m_psRunningProcess, ( uint32 ) psData->m_nEIP );
}

uint32 ProcessManager_Sleep( KProcess_sSleep_t *psData ) {

    // Set sleep timeout
    ObjectManager_Lock();
    K_sThread_t * psThread = ( K_sThread_t * ) Kg_sKernel.m_psRunningThread->m_pData;
    psThread->m_nSleep = psData->m_nTimeOut;
    psThread->m_nSleepTimeOut = psData->m_nTimeOut;
    psThread->m_nState = THREAD_SLEEPING;
    ObjectManager_Unlock();

    // Now switch task and leave this thread in a sleeping state
    ProcessManager_NextThread( );

    return NULL;
}

uint32 ProcessManager_Awaken( uint32 nThreadID ) {

    // Search for thread and awaken it
    ObjectManager_Lock();
    K_sObject_t * psObjectParent = ObjectManager_SearchInClassTypeIndex( NULL, KOBJECT_OBJ_THREAD, nThreadID );
    K_sThread_t * psThread = ( K_sThread_t * ) psObjectParent->m_pData;
    if ( psThread->m_nState == THREAD_SLEEPING ) {
        psThread->m_nState = THREAD_READY;
    }
    ObjectManager_Unlock();

    return NULL;
}

uint32 ProcessManager_AwakenCall( KProcess_sAwaken_t *psData ) {
    return ProcessManager_Awaken( psData->m_nThreadID );
}

uint32 ProcessManager_Handler( uint32 nCall, void * pData ) {
    switch ( nCall ) {
    case CREATEPROCESS:
        break;
    case CREATETHREAD:
        return ProcessManager_CreateThreadCall( ( KProcess_sCreateThread_t * ) pData );
    case SLEEP:
        return ProcessManager_Sleep( ( KProcess_sSleep_t * ) pData );
    case AWAKEN:
        return ProcessManager_AwakenCall( ( KProcess_sAwaken_t * ) pData );
    case RELINQUISH:
        return ProcessManager_NextThread( );
    }

    return KMODULE_INVALIDCALL;
}

