#include <OSCalls.h>
#include <CI-Interrupt.h>

uint32 Interrupt_nHandle;
uint32 Interrupt_nAttachHandler;
uint32 Interrupt_nEnableInterrupt;

void KInterrupt_Init() {

    // Get handle
    Interrupt_nHandle = KModule_GetHandle( "InterruptManager" );

    // Get call codes
    Interrupt_nAttachHandler = KModule_GetCallID( Interrupt_nHandle, "AttachHandler" );
    Interrupt_nEnableInterrupt = KModule_GetCallID( Interrupt_nHandle, "EnableInterrupt" );
}

void KInterrupt_AttachHandler( char *pszName, uint16 nInterrupt, void *pHandler ) {

    // Check if initialised
    if ( Interrupt_nHandle == NULL )
        KInterrupt_Init();

    KInterrupt_sAttachHandler_t sData;
    sData.m_pszName = pszName;
    sData.m_nInterrupt = nInterrupt;
    sData.m_pHandler = pHandler;
    KModule_Call( Interrupt_nHandle, Interrupt_nAttachHandler, &sData );
}

void KInterrupt_EnableInterrupt( uint16 nInterrupt ) {

    // Check if initialised
    if ( Interrupt_nHandle == NULL )
        KInterrupt_Init();

    KInterrupt_sIRQ_t sData;
    sData.m_nInterrupt = nInterrupt;
    KModule_Call( Interrupt_nHandle, Interrupt_nEnableInterrupt, &sData );
}

