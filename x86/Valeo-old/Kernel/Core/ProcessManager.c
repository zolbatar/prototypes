#include <Kernel.h>

extern uint32 g_nLocksHeld;
bool bCreateThreadStack = false;
bool g_bTaskSwitchWaiting = false;

// Locks
extern sLock_t sFSLock;
extern sLock_t sIOLock;
extern sLock_t sMemoryLock;
extern sLock_t sObjectLock;

void ProcessManager_Init() {

    // Initialise kernel variables
    g_sKernel.m_nProcessID = 1;
    g_sKernel.m_nThreadID = 1;

    // Create running process (kernel process)
    ProcessManager_CreateProcess( "Kernel", &g_sKernel.m_psRunningProcessID, &g_sKernel.m_psRunningProcess );

    // Set process settings
    sObject_t *psProcesObject = g_sKernel.m_psRunningProcess;
    sProcess_t *psProcess = ( sProcess_t * ) psProcesObject->m_pData;
    psProcess->m_psAllocator = &g_sKernel.m_psAllocator;
    psProcess->m_nSS = KERNELDS;
    psProcess->m_nCS = KERNELCS;
    psProcess->m_nDS = KERNELDS;
    psProcess->m_nES = KERNELDS;
    psProcess->m_nFS = KERNELDS;
    psProcess->m_nGS = KERNELDS;
    psProcess->m_nSS = KERNELDS;

    // Create thread (kernel thread, eventually become idle loop)
    ProcessManager_CreateThread( psProcess, 0, &g_sKernel.m_psRunningThreadID, &g_sKernel.m_psRunningThread );

    // Set thread as running (because it is) and set stack to current kernel stack
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t *psThread = ( sThread_t * ) psThreadObject->m_pData;
    psThread->m_nState = PM_THREAD_RUNNING;

    // Future threads will need stack creation
    bCreateThreadStack = true;

    // Setup TSS for switching to kernel
    sTSS_t *m_sTSS = &g_sKernel.m_sTSS;
    m_sTSS->cs = KERNELCS;
    m_sTSS->ds = KERNELDS;
    m_sTSS->es = KERNELDS;
    m_sTSS->fs = KERNELDS;
    m_sTSS->gs = KERNELDS;
    m_sTSS->ss = KERNELDS;
    m_sTSS->ss0 = KERNELDS;
    m_sTSS->ss1 = 0;
    m_sTSS->ss2 = 0;
    m_sTSS->cr3 = ( uint32 ) g_sKernel.m_pnPageDirectory;
    Descriptor_SetBase( TSS, ( uint32 ) m_sTSS );
    Descriptor_SetLimit( TSS, sizeof( sTSS_t ) );
    Descriptor_SetAccess( TSS, 0x89 );

    // Set first TSS entry
    LoadTaskRegister( TSS );

    // Attach scheduler to timer
    TimerManager_AttachTimerHandler( "Scheduler", 0, ProcessManager_Preempt );

    // Create module calls
    ProcessManager_CreateModuleInterface();

    KPrint( "PROCESSES", "Scheduler initialised\n" );
}

KStatus ProcessManager_CreateProcess( char *pszName, uint32 *nPID, sObject_t **psProcessOut ) {

    // Construct object path and key
    ObjectManager_Lock();
    ObjectManager_ConstructPath( "/System/Processes/" );
    char szID[ OM_NAMELENGTH ] = "";
    snprintf( ( char * ) szID, OM_NAMELENGTH, "Process %u", g_sKernel.m_nProcessID );
    ObjectManager_ConstructKey( ( char * ) & szID );

    // Create object
    sObject_t * psObject = ObjectManager_CreateObject( OM_PROCESS, sizeof( sProcess_t ) );
    *psProcessOut = psObject;
    psObject->m_nTypeIndex = g_sKernel.m_nProcessID;

    // Create process data
    sProcess_t *psProcess = ( sProcess_t * ) psObject->m_pData;
    psProcess->m_szName[ 0 ] = '\0';
    strcat( psProcess->m_szName, pszName );
    psProcess->m_nBasePriority = PM_THREADPRIORITY_NORMAL;
    psProcess->m_nPID = g_sKernel.m_nProcessID++;
    psProcess->m_nThreadCount = 0;
    psProcess->m_psAllocator = NULL;
    *nPID = psProcess->m_nPID;
    ObjectManager_Unlock();

    return NULL;
}

KStatus ProcessManager_CreateThread( sProcess_t *psProcess, uint32 nEIP, uint32 *nTID, sObject_t **psThreadOut ) {

    // Construct object path and key
    ObjectManager_Lock();
    ObjectManager_ConstructPath( "/System/Threads/" );
    char szID[ OM_NAMELENGTH ] = "";
    snprintf( ( char * ) szID, OM_NAMELENGTH, "Thread %u", g_sKernel.m_nThreadID );
    ObjectManager_ConstructKey( ( char * ) & szID );

    // Create object
    sObject_t * psObject = ObjectManager_CreateObject( OM_THREAD, sizeof( sThread_t ) );
    *psThreadOut = psObject;
    psObject->m_nTypeIndex = g_sKernel.m_nThreadID;

    // Create thread data
    sThread_t *psThread = ( sThread_t * ) psObject->m_pData;
    psThread->m_psProcess = psProcess;
    psThread->m_nBasePriority = psProcess->m_nBasePriority;
    psThread->m_nCurrentPriority = psProcess->m_nBasePriority;
    psThread->m_nState = PM_THREAD_NEW;
    psThread->m_nTID = g_sKernel.m_nThreadID++;
    psThread->m_nCPUTime = 0;
    psThread->m_psMessagePort = NULL;
    psThread->m_nNestDepth = 1;
    if ( nTID != NULL ) {
        *nTID = psThread->m_nTID;
    }

    // Create page for stack
    if ( bCreateThreadStack == true ) {

        // Get memory for stack from heap
        void * nStackSpace = MemoryManager_KAlloc ( PM_KERNELTHREADSTACKSIZE );

        // Clear memory now (this makes sure its paged in properly too)
        memset( nStackSpace, 0, PM_KERNELTHREADSTACKSIZE );

        // Move stack pointer to end
        nStackSpace += PM_KERNELTHREADSTACKSIZE;

        // Set stack (register) settings
        sCallStack_t *psStack = ( sCallStack_t * ) psThread->m_nESP[ 0 ] = ( ( uint32 ) nStackSpace ) - sizeof( sCallStack_t );
        psThread->m_nESP[ 0 ] += 4;
        psThread->m_nSS = psProcess->m_nSS;
        psStack->eflags = 0x203246;
        psStack->eip = nEIP;
        psStack->cs = psProcess->m_nCS;
        psStack->ds = psProcess->m_nDS;
        psStack->es = psProcess->m_nDS;
        psStack->fs = psProcess->m_nDS;
        psStack->gs = psProcess->m_nDS;
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

    ObjectManager_Unlock();

    return NULL;
}

sThread_t *ProcessManager_GetThreadObject( uint32 nTID ) {
    sObject_t * psObject = ObjectManager_SearchInClassTypeIndex( NULL, OM_THREAD, nTID );
    if ( psObject != NULL ) {
        sThread_t * psThread = ( sThread_t * ) psObject->m_pData;
        return psThread;
    }
    return NULL;
}

KStatus ProcessManager_RunThread( uint32 nTID ) {

    // Find thread
    ObjectManager_Lock();
    sThread_t * psThread = ProcessManager_GetThreadObject( nTID );
    if ( psThread == NULL ) {
        ObjectManager_Unlock();
        return NULL;
    }
    psThread->m_nState = PM_THREAD_READY;
    ObjectManager_Unlock();
    return NULL;
}

void ProcessManager_UpdateThreads() {

    // Search for thread
    sObject_t * psObject = NULL;
    while ( 1 ) {

        // Get next thread
        psObject = ObjectManager_SearchInClass( psObject, OM_THREAD );
        if ( psObject == NULL ) {
            break;
        }

        // Get pointer to thread data
        sThread_t * psThread = ( sThread_t * ) psObject->m_pData;

        // And process threads
        if ( psThread->m_nState == PM_THREAD_SLEEPING ) {       // See if sleeper

            // See if it wants to sleep forever
            if ( psThread->m_nSleepTimeOut != PM_SLEEPFOREVER ) {

                // Decrement timeout
                psThread->m_nSleep--;

                // Awaken if necessary
                if ( psThread->m_nSleep == 0 ) {
                    psThread->m_nState = PM_THREAD_READY;
                }
            }

        } else if ( psThread->m_nState == PM_THREAD_RUNNING ) {
            psThread->m_nCPUTime++;
        }
    }
}

sObject_t *ProcessManager_GetNextThread( sObject_t *psThreadObject ) {

    // Local copy of thread object
    sObject_t * psThreadObjectLocal = psThreadObject;

    while ( 1 ) {

        // Get next thread
        psThreadObjectLocal = ObjectManager_SearchInClass( psThreadObjectLocal, OM_THREAD );

        // If we are at end, go back to beginning
        if ( psThreadObjectLocal == NULL ) {
            psThreadObjectLocal = ObjectManager_SearchInClass( NULL, OM_THREAD );
        }

        // Check we haven't looped round to the start
        if ( psThreadObjectLocal == psThreadObject )
            break;

        // See if this thread is in a state to run
        sThread_t * psThread = ( sThread_t * ) psThreadObjectLocal->m_pData;
        if ( psThread->m_nState == PM_THREAD_READY )
            break;

    }
    return psThreadObjectLocal;
}

void ProcessManager_SaveContext( sCallStack_t *psStack ) {

    // Get index of currently running thread
    sObject_t * psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Check we haven't exceeded nesting depth, this is fatal
    if ( psThread->m_nNestDepth == PM_NESTDEPTH ) {
        KPrint( "PROCESSES", "Kernel nesting exceeded maximum - Halting\n" );
        halt();
    }

    // Save nested stack info
    psThread->m_nSS = psStack->sss;
    psThread->m_nESP[ psThread->m_nNestDepth ] = psStack->sesp;

    // Increment nest counter
    psThread->m_nNestDepth++;
}

void ProcessManager_RestoreContext( sCallStack_t *psStack ) {

    // Get index of currently running thread
    sObject_t * psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Decrement nest counter
    psThread->m_nNestDepth--;

    psStack->sss = psThread->m_nSS;
    psStack->sesp = psThread->m_nESP[ psThread->m_nNestDepth ];
}

void ProcessManager_NextThread( sCallStack_t *psStack ) {

    // Update threads (i.e. awaken sleepers etc)
    g_bTaskSwitchWaiting = false;
    ProcessManager_UpdateThreads();

    // Get index of currently running thread
    sObject_t *psCurrentThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psCurrentThread = ( sThread_t * ) psCurrentThreadObject->m_pData;

    // Round robin scheduler, choose next thread
    sObject_t * psNewThreadObject = ProcessManager_GetNextThread( psCurrentThreadObject );
    sThread_t * psNewThread = ( sThread_t * ) psNewThreadObject->m_pData;

    // See if no new thread to execute
    if ( psCurrentThread == psNewThread ) {
        return ;
    }

    // Save context
    ProcessManager_SaveContext( psStack );

    // Mark new thread as running and previous as ready (if running) and set current thread
    if ( psCurrentThread->m_nState == PM_THREAD_RUNNING ) {
        psCurrentThread->m_nState = PM_THREAD_READY;
    }
    psNewThread->m_nState = PM_THREAD_RUNNING;
    g_sKernel.m_psRunningThread = psNewThreadObject;
    g_sKernel.m_psRunningThreadID = psNewThread->m_nTID;

    // Restore context
    ProcessManager_RestoreContext( psStack );

    return ;
}

KStatus ProcessManager_Preempt( sCallStack_t *psStack ) {

    // Can we switch?
    if ( g_nLocksHeld == 0 ) {
        ObjectManager_Lock();
        ProcessManager_NextThread( psStack );
        ObjectManager_Unlock();
    } else {
        g_bTaskSwitchWaiting = true;
    }

    // Show current thread in top right
    g_pConsoleVideo[ 158 ] = ( g_sKernel.m_psRunningThreadID & 0xFF ) + 48;
    g_pConsoleVideo[ 159 ] = 15;

    return NULL;
}

KStatus ProcessManager_Sleep( uint32 nTimeOut ) {

    // Set sleep timeout
    ObjectManager_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;
    psThread->m_nSleep = nTimeOut;
    psThread->m_nSleepTimeOut = nTimeOut;
    psThread->m_nState = PM_THREAD_SLEEPING;
    ObjectManager_Unlock();

    return NULL;
}

KStatus ProcessManager_Awaken( uint32 nTID ) {

    // Search for thread and awaken it
    ObjectManager_Lock();
    sThread_t *psThread = ProcessManager_GetThreadObject( nTID );
    if ( psThread->m_nState == PM_THREAD_SLEEPING ) {
        psThread->m_nState = PM_THREAD_READY;
    }
    ObjectManager_Unlock();

    return NULL;
}

KStatus ProcessManager_Call_CreateThread( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    uint32 nEIP = ( uint32 ) MM_GetParameterVOIDPTR( pParameters );
    uint32 *nTID = MM_GetParameterUINT32PTR( pParameters );
    sObject_t *psProcesObject = g_sKernel.m_psRunningProcess;
    sProcess_t *psProcess = ( sProcess_t * ) psProcesObject->m_pData;
    sObject_t *psThread;
    return ProcessManager_CreateThread( psProcess, nEIP, nTID, &psThread );
}

KStatus ProcessManager_Call_RunThread( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    uint32 nTID = MM_GetParameterUINT32( pParameters );
    return ProcessManager_RunThread( nTID );
}

KStatus ProcessManager_Call_AwakenThread( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    uint32 nTID = MM_GetParameterUINT32( pParameters );
    return ProcessManager_Awaken( nTID );
}

KStatus ProcessManager_Call_Sleep( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    uint32 nTime = MM_GetParameterUINT32( pParameters );
    KStatus nRet = ProcessManager_Sleep( nTime );

    // Now switch task
    ObjectManager_Lock();
    ProcessManager_NextThread( psStack );
    ObjectManager_Unlock();

    return nRet;
}

KStatus ProcessManager_Call_Relinquish( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Call relinquish
    ObjectManager_Lock();
    ProcessManager_NextThread( psStack );
    ObjectManager_Unlock();

    return NULL;
}

void ProcessManager_CreateModuleInterface() {

    // Create module calls
    ModuleManager_CreateModule( "ProcessManager" );
    ModuleManager_CreateModuleCall( "ProcessManager", "CreateThread", &ProcessManager_Call_CreateThread );
    ModuleManager_CreateModuleCall( "ProcessManager", "RunThread", &ProcessManager_Call_RunThread );
    ModuleManager_CreateModuleCall( "ProcessManager", "AwakenThread", &ProcessManager_Call_AwakenThread );
    ModuleManager_CreateModuleCall( "ProcessManager", "Sleep", &ProcessManager_Call_Sleep );
    ModuleManager_CreateModuleCall( "ProcessManager", "Relinquish", &ProcessManager_Call_Relinquish );
}


