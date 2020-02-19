#include <Kernel.h>

bool l_bCreateThreadStack = false;

void Process_Init() {

    // Create process/thread object paths and object types
    Object_Lock();
    g_sKernel.m_psSystemProcesses = Object_CreateDirectory( g_sKernel.m_psSystemRoot, "Processes" );
    g_sKernel.m_psSystemThreads = Object_CreateDirectory( g_sKernel.m_psSystemRoot, "Threads" );
    g_sKernel.m_nTypeProcess = Object_CreateType( "Process" );
    g_sKernel.m_nTypeThread = Object_CreateType( "Thread" );
    Object_Unlock();

    // Create running process (kernel process)
    Object_Lock();
    Process_CreateProcess( &g_sKernel.m_psRunningProcessID, &g_sKernel.m_psRunningProcess, false );
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
    Object_Unlock();

    // Create thread (kernel thread, eventually become idle loop)
    // Set thread as running (because it is) and set stack to current kernel stack
    Object_Lock();
    Process_CreateThread( psProcesObject, 0, &g_sKernel.m_psRunningThreadID, &g_sKernel.m_psRunningThread );
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t *psThread = ( sThread_t * ) psThreadObject->m_pData;
    psThread->m_nState = PROCESS_THREAD_RUNNING;
    Object_Unlock();

    // Future threads will need stack creation
    l_bCreateThreadStack = true;

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
    Timer_AttachTimerHandler( 0, Process_Preempt );
}

KStatus Process_CreateProcess( uint32 *nPID, sObject_t **psProcessOut, bool bCreateProcessPageStruct ) {

    // Create process object
    char szID[ OBJECT_NAMELENGTH ];
    snprintf( ( char * ) & szID, OBJECT_NAMELENGTH, "Process %lu", g_sKernel.m_nProcessID );
    sObject_t * psObject = Object_CreateObject( g_sKernel.m_psSystemProcesses, g_sKernel.m_nTypeProcess, ( char * ) & szID, sizeof( sProcess_t ) );
    *psProcessOut = psObject;

    // Create process data
    sProcess_t *psProcess = ( sProcess_t * ) psObject->m_pData;
    psProcess->m_nPID = g_sKernel.m_nProcessID++;
    psProcess->m_nThreadCount = 0;
    psProcess->m_psAllocator = NULL;
    *nPID = psProcess->m_nPID;

    // Create used page struct
    if ( bCreateProcessPageStruct ) {
        psProcess->m_psProcessPages = MM_KAlloc( sizeof( sProcessPages_t ) );
        sProcessPages_t *m_psProcessPages = ( sProcessPages_t * ) psProcess->m_psProcessPages;
        MM_ZeroPageStruct( m_psProcessPages );
        m_psProcessPages->m_psNext = NULL;
    } else {
        psProcess->m_psProcessPages = NULL;
    }

    return NULL;
}

KStatus Process_CreateThread( sObject_t *psProcessObject, uint32 nEIP, uint32 *nTID, sObject_t **psThreadOut ) {

    // Create thread object
    char szID[ OBJECT_NAMELENGTH ] ;
    snprintf( ( char * ) & szID, OBJECT_NAMELENGTH, "Thread %lu", g_sKernel.m_nThreadID );
    sObject_t * psObject = Object_CreateObject( g_sKernel.m_psSystemThreads, g_sKernel.m_nTypeThread, ( char * ) & szID, sizeof( sThread_t ) );
    if ( psThreadOut != NULL ) {
        *psThreadOut = psObject;
    }

    // Create thread data
    sThread_t *psThread = ( sThread_t * ) psObject->m_pData;
    psThread->m_psProcess = psProcessObject;
    psThread->m_nState = PROCESS_THREAD_NEW;
    psThread->m_nTID = g_sKernel.m_nThreadID++;
    psThread->m_nCPUTime = 0;
    psThread->m_nDispatchPriority = 1;
    psThread->m_psMessagePort = NULL;
    psThread->m_nNestDepth = 1;
    if ( nTID != NULL ) {
        *nTID = psThread->m_nTID;
    }

    // Get process data
    sProcess_t *psProcess = ( sProcess_t * ) psProcessObject->m_pData;

    // Create page for stack
    if ( l_bCreateThreadStack == true ) {

        // Get memory for stack from heap
        void * nStackSpace = MM_KAlloc ( PROCESS_PROCESSSTACKSIZE );

        // Clear memory now (this makes sure its paged in properly too)
        memset( nStackSpace, 0, PROCESS_PROCESSSTACKSIZE );

        // Move stack pointer to end
        nStackSpace += PROCESS_PROCESSSTACKSIZE;

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

    return NULL;
}

KStatus Process_KillThread() {

    // Get current thread
    sObject_t * psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t *psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Set thread for deletion (it will be deleted on next thread switch)
    psThread->m_nState = PROCESS_THREAD_DEAD;

    // Return success
    return NULL;
}

void Process_UpdateThreads( ) {

    // Loop through all thread
    sObjectDirectory_t * psObjectPath = g_sKernel.m_psSystemThreads;

    // Loop through all threads
    sObject_t * psObject = psObjectPath->m_psObjectTail;
    while ( psObject != NULL ) {

        // Flag to indicate whether to use current object to get next
        bool bGoNext = true;

        // Get pointer to thread data
        sThread_t * psThread = ( sThread_t * ) psObject->m_pData;

        // Increate dispatch priority if we are waiting for CPU
        psThread->m_nDispatchPriority++;

        // What do we need to do?
        if ( psThread->m_nState == PROCESS_THREAD_NEW ) {
            psThread->m_nState = PROCESS_THREAD_READY;
        } else if ( psThread->m_nState == PROCESS_THREAD_SLEEPING ) {

            // See if it wants to sleep forever
            if ( psThread->m_nSleepTimeOut != PROCESS_SLEEPFOREVER ) {

                // Decrement timeout
                psThread->m_nSleep--;

                // Awaken if necessary
                if ( psThread->m_nSleep == 0 ) {
                    psThread->m_nState = PROCESS_THREAD_READY;
                }
            }

        } else if ( psThread->m_nState == PROCESS_THREAD_RUNNING ) {

            // Update CPU time used by active thread
            psThread->m_nCPUTime++;

            // Lower priority, so other threads may run
            psThread->m_nDispatchPriority = 1;


        } else if ( psThread->m_nState == PROCESS_THREAD_DEAD ) {

            // Save next
            sObject_t * psNext = psObject->m_psNext;

            // Dead thread, so delete
            Object_Delete( psObjectPath, psObject );

            // Go next
            bGoNext = false;
            psObject = psNext;

        }

        // Next thread
        if ( bGoNext )
            psObject = psObject->m_psNext;
    }
}

sObject_t *Process_GetNextThread( ) {

    // Loop through all thread
    sObjectDirectory_t * psObjectPath = g_sKernel.m_psSystemThreads;

    // Local copy of thread object
    sObject_t * psThreadObject = psObjectPath->m_psObjectTail;

    // Priority level and chosen object
    uint32 nPriority = 0;
    sObject_t * psChosenThreadObject = NULL;

    while ( psThreadObject != NULL ) {

        // See if this thread is in a state to run, if it is check the priority
        sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;
        if ( psThread->m_nState == PROCESS_THREAD_READY ) {
            if ( psThread->m_nDispatchPriority > nPriority ) {
                nPriority = psThread->m_nDispatchPriority;
                psChosenThreadObject = psThreadObject;
            }
        }

        // Get next thread
        psThreadObject = psThreadObject->m_psNext;

    }

    return psChosenThreadObject;
}

void Process_SaveContext( sCallStack_t *psStack ) {

    // Get index of currently running thread
    sObject_t * psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Check we haven't exceeded nesting depth, this is fatal
    if ( psThread->m_nNestDepth == PROCESS_MAXNESTDEPTH ) {
        Syslog_Lock();
        Syslog_Entry( "PROCESS", "Kernel nesting exceeded maximum - Halting\n" );
        Syslog_Unlock();
        halt();
    }

    // Save nested stack info
    psThread->m_nSS = psStack->sss;
    psThread->m_nESP[ psThread->m_nNestDepth ] = psStack->sesp;

    // Increment nest counter
    psThread->m_nNestDepth++;
}

void Process_RestoreContext( sCallStack_t *psStack ) {

    // Get index of currently running thread
    sObject_t * psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Decrement nest counter
    psThread->m_nNestDepth--;

    psStack->sss = psThread->m_nSS;
    psStack->sesp = psThread->m_nESP[ psThread->m_nNestDepth ];
}

void Process_NextThread( sCallStack_t *psStack ) {

    // Update threads (i.e. awaken sleepers/delete threads etc)
    Process_UpdateThreads( );

    // Scheduler, choose next thread
    sObject_t * psNewThreadObject = Process_GetNextThread();
    if ( psNewThreadObject == NULL ) {
        // No new threads
    } else {

        // Save context
        Process_SaveContext( psStack );

        // Mark previous as ready (if running)
        sObject_t *psCurrentThreadObject = g_sKernel.m_psRunningThread;
        sThread_t * psCurrentThread = ( sThread_t * ) psCurrentThreadObject->m_pData;
        psCurrentThread->m_nState = PROCESS_THREAD_READY;
        psCurrentThread->m_nDispatchPriority = 1;

        // Mark new thread as running
        sThread_t * psNewThread = ( sThread_t * ) psNewThreadObject->m_pData;
        psNewThread->m_nState = PROCESS_THREAD_RUNNING;
        g_sKernel.m_psRunningThread = psNewThreadObject;
        g_sKernel.m_psRunningThreadID = psNewThread->m_nTID;

        // And set new process
        sObject_t *psNewProcessObject = psNewThread->m_psProcess;
        g_sKernel.m_psRunningProcess = psNewProcessObject;

        // Restore context
        Process_RestoreContext( psStack );

    }
}

KStatus Process_Preempt( sCallStack_t *psStack ) {

    Object_Lock();

    // Display a little swirly thing to let us know the kernel hasn't stopped
    static uint32 nState = 0;
    uchar cSwirl = ' ';
    switch ( nState ) {
    case 0:
        cSwirl = '\\';
        break;
    case 1:
        cSwirl = '|';
        break;
    case 2:
        cSwirl = '/';
        break;
    case 3:
        cSwirl = '-';
        break;
    };
    nState++;
    if ( nState == 4 )
        nState = 0;
    g_pVideo[ 158 ] = cSwirl & 0xFF;
    g_pVideo[ 159 ] = TEXTCOLOUR_WHITE;

    // Choose next thread
    if ( g_sKernel.m_nThreadID > 1 ) {
        Process_NextThread( psStack );
    }

    // Show current thread in top right
    g_pVideo[ 154 ] = ( g_sKernel.m_psRunningThreadID & 0xFF ) + 48;
    g_pVideo[ 155 ] = TEXTCOLOUR_WHITE;

    Object_Unlock();

    return NULL;
}

KStatus Process_CreateThread_Call( sCallStack_t * psStack ) {

    Object_Lock();

    // Get parameters
    sObject_t * psProcessObject = g_sKernel.m_psRunningProcess;
    sObject_t *psThread;
    OS_Process_CreateThread_t *psData = ( OS_Process_CreateThread_t * ) psStack->ebx;
    uint32 nEIP = psData->m_nEIP;

    // Create thread
    Process_CreateThread( psProcessObject, nEIP, &psData->m_nTID, &psThread );

    Object_Unlock();

    return NULL;
}

KStatus Process_EndThread_Call( sCallStack_t * psStack ) {

    // Kill thread
    Object_Lock();
    Process_KillThread();
    Object_Unlock();

    return NULL;
}


