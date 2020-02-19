#include <OSCalls.h>
#include <x86.h>
#include <Core.h>

bool TimerManager_Handler();

void TimerManager_Init() {

    // Set no timers
    Kg_sKernel.m_nCurrentTimer = 0;
    Kg_sKernel.m_psLastTimer = NULL;

    // Set timer count to 0;
    Kg_sKernel.m_nTimer = 0;

    // Attach timer to the PIT and enable IRQ
    InterruptManager_AttachHandler( "Timer", 0, TimerManager_Handler );
    InterruptManager_EnableIRQ( 0x0 );

    KPrint( KDEBUG, "TIMER", "Timer initialised\n" );
}

void TimerManager_AttachTimerHandler( char *pszName, uint32 nTimeOut, TimerHandler *pHandler ) {

    // Its critical that we kill interrupts
    bool bReenableInterrupts = Kg_bInterruptsActive;
    InterruptManager_Stop();

    // Create timer struct
    K_sTimer_t * psTimer = ( K_sTimer_t * ) MemoryManager_KAlloc( sizeof( K_sTimer_t ) );
    strncpy ( ( char * ) & psTimer->m_szName, pszName, KOBJECT_NAMELENGTH );
    psTimer->m_nIndex = Kg_sKernel.m_nCurrentTimer++;
    psTimer->m_nTimeOut = nTimeOut;
    psTimer->m_nTimeOutLeft = nTimeOut;
    psTimer->m_pHandler = pHandler;

    // Add to linked list
    if ( Kg_sKernel.m_psLastTimer == NULL ) {
        psTimer->m_psPrevious = NULL;
    } else {
        K_sTimer_t *psPrevious = Kg_sKernel.m_psLastTimer;
        psTimer->m_psPrevious = psPrevious;
    }
    Kg_sKernel.m_psLastTimer = psTimer;

    // Now its safe to re-enable
    if ( bReenableInterrupts == true )
        InterruptManager_Start();
}

bool TimerManager_Handler( ) {

    // Search for module
    K_sTimer_t * psTimer = Kg_sKernel.m_psLastTimer;
    while ( psTimer != NULL ) {

        TimerHandler * psTimerHandler = psTimer->m_pHandler;
        if ( psTimer->m_nTimeOut == 0 ) {
            // Call handler
            psTimerHandler( );

        } else {
            // We have a timeout based timer
            psTimer->m_nTimeOutLeft--;

            if ( psTimer->m_nTimeOutLeft == 0 ) {
                psTimer->m_nTimeOutLeft = psTimer->m_nTimeOut;
                psTimerHandler( );
            }
        }
        psTimer = psTimer->m_psPrevious;
    }

    // Return that we have handled the interrupt
    return true;
}


