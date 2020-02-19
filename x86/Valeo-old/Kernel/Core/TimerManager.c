#include <Kernel.h>

KStatus TimerManager_Handler( sCallStack_t *psStack );

void TimerManager_Init() {

    // Set no timers
    g_sKernel.m_nCurrentTimer = 0;
    g_sKernel.m_psLastTimer = NULL;

    // Set timer count to 0;
    g_sKernel.m_nTimer = 0;

    // Attach timer to the PIT and enable IRQ
    InterruptManager_AttachHandler( "Timer", 0, TimerManager_Handler );
    InterruptManager_EnableIRQ( 0x0 );

    KPrint( "TIMER", "Timer initialised\n" );
}

void TimerManager_AttachTimerHandler( char *pszName, uint32 nTimeOut, TimerHandler *pHandler ) {

    // Its critical that we kill interrupts
    if ( g_bKernelInitDone == true ) {
        asm volatile ( "cli;" );
    }

    // Create timer struct
    sTimer_t * psTimer = ( sTimer_t * ) MemoryManager_KAlloc( sizeof( sTimer_t ) );
    strncpy ( ( char * ) & psTimer->m_szName, pszName, OM_NAMELENGTH );
    psTimer->m_nIndex = g_sKernel.m_nCurrentTimer++;
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

    // Now its safe to re-enable
    if ( g_bKernelInitDone == true ) {
        asm volatile ( "sti;" );
    }
}

KStatus TimerManager_Handler( sCallStack_t *psStack ) {

    // Search for handler
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

    // Return that we have handled the interrupt
    return NULL;
}


