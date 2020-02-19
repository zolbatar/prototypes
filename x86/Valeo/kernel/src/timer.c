#include <Kernel.h>

KStatus Timer_Handler( sCallStack_t *psStack );

// Lock
sLock_t sTimerLock;

void Timer_LockInit() {
    Lock_Init( &sTimerLock );
}

void Timer_Lock() {
    Lock_Lock( &sTimerLock );
}

void Timer_Unlock() {
    Lock_Unlock( &sTimerLock );
}

void Timer_Init() {

    // Initialise locking
    Timer_LockInit();

    // Set no timers
    g_sKernel.m_psLastTimer = NULL;

    // Set timer count to 0;
    g_sKernel.m_nTimer = 0;

    // Attach timer to the PIT and enable IRQ
    Interrupt_AttachHandler( 0, Timer_Handler );
    Interrupt_EnableIRQ( 0x0 );
}

void Timer_AttachTimerHandler( uint32 nTimeOut, TimerHandler *pHandler ) {

    // Create timer struct
    Timer_Lock();
    sTimer_t * psTimer = ( sTimer_t * ) MM_KAlloc( sizeof( sTimer_t ) );
    psTimer->m_nPID = g_sKernel.m_psRunningProcessID;
    psTimer->m_nTimeOut = nTimeOut;
    psTimer->m_nTimeOutLeft = nTimeOut;
    psTimer->m_pHandler = pHandler;

    // Add to linked list
    if ( g_sKernel.m_psLastTimer == NULL ) {
        psTimer->m_psPrevious = NULL;
    } else {
        sTimer_t *psPrevious = g_sKernel.m_psLastTimer;
        psTimer->m_psPrevious = psPrevious;
    }
    g_sKernel.m_psLastTimer = psTimer;
    Timer_Unlock();
}

KStatus Timer_Handler( sCallStack_t *psStack ) {

    // Search for handler
    Timer_Lock();
    sTimer_t * psTimer = g_sKernel.m_psLastTimer;
    while ( psTimer != NULL ) {

        TimerHandler * psTimerHandler = psTimer->m_pHandler;
        if ( psTimer->m_nTimeOut == 0 ) {
            // Call handler
            psTimerHandler( psStack );

        } else {
            // We have a timeout based timer
            psTimer->m_nTimeOutLeft--;

            if ( psTimer->m_nTimeOutLeft == 0 ) {
                psTimer->m_nTimeOutLeft = psTimer->m_nTimeOut;
                psTimerHandler( psStack );
            }
        }
        psTimer = psTimer->m_psPrevious;
    }
    Timer_Unlock();

    // Return that we have handled the interrupt
    return NULL;
}


