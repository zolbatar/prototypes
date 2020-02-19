#include <OSCalls.h>
#include <x86.h>
#include <Core.h>
#include <CI-Interrupt.h>

extern void DefaultIntHandler();

// Pointers to exception handlers
extern void EXC_00();
extern void EXC_01();
extern void EXC_02();
extern void EXC_03();
extern void EXC_04();
extern void EXC_05();
extern void EXC_INVALIDOPCODE();
extern void EXC_07();
extern void EXC_DOUBLEFAULT();
extern void EXC_09();
extern void EXC_0A();
extern void EXC_0B();
extern void EXC_STACKFAULT();
extern void EXC_GPF();
extern void EXC_PAGEFAULT();

// Pointers to hardware interrupt handlers
extern void IRQ_00();
extern void IRQ_01();
extern void IRQ_02();
extern void IRQ_03();
extern void IRQ_04();
extern void IRQ_05();
extern void IRQ_06();
extern void IRQ_07();
extern void IRQ_08();
extern void IRQ_09();
extern void IRQ_0A();
extern void IRQ_0B();
extern void IRQ_0C();
extern void IRQ_0D();
extern void IRQ_0E();
extern void IRQ_0F();

// Handler's
static K_sIRQ_Handler_t *IRQ_Handler[ 16 ];
volatile bool Kg_bInterruptsActive = false;
volatile bool Kg_bInISR = false;

// Prototypes
uint32 InterruptManager_Handler( uint32 nCall, void * pData );

// Calls
enum {
    ATTACHHANDLER,
    ENABLEINTERRUPT
};

void InterruptManager_Init() {

    // Zero all set hardware interrupt handlers
    uint32 i;
    for ( i = 0; i < 16; i++ ) {
        IRQ_Handler[ i ] = NULL;
    }

    for ( i = 0; i < 256; i++ ) {
        Descriptor_SetInterruptGate( i, &DefaultIntHandler );
    }

    // Set exception handlers
    Descriptor_SetInterruptGate( 0x00, &EXC_00 );
    Descriptor_SetInterruptGate( 0x01, &EXC_01 );
    Descriptor_SetInterruptGate( 0x02, &EXC_02 );
    Descriptor_SetInterruptGate( 0x03, &EXC_03 );
    Descriptor_SetInterruptGate( 0x04, &EXC_04 );
    Descriptor_SetInterruptGate( 0x05, &EXC_05 );
    Descriptor_SetInterruptGate( 0x06, &EXC_INVALIDOPCODE );
    Descriptor_SetInterruptGate( 0x07, &EXC_07 );
    Descriptor_SetInterruptGate( 0x08, &EXC_DOUBLEFAULT );
    Descriptor_SetInterruptGate( 0x09, &EXC_09 );
    Descriptor_SetInterruptGate( 0x0A, &EXC_0A );
    Descriptor_SetInterruptGate( 0x0B, &EXC_0B );
    Descriptor_SetInterruptGate( 0x0C, &EXC_STACKFAULT );
    Descriptor_SetInterruptGate( 0x0D, &EXC_GPF );
    Descriptor_SetInterruptGate( 0x0E, &EXC_PAGEFAULT );

    // Set Default Interrupt Handlers
    Descriptor_SetInterruptGate( 0x20, &IRQ_00 );
    Descriptor_SetInterruptGate( 0x21, &IRQ_01 );
    Descriptor_SetInterruptGate( 0x22, &IRQ_02 );
    Descriptor_SetInterruptGate( 0x23, &IRQ_03 );
    Descriptor_SetInterruptGate( 0x24, &IRQ_04 );
    Descriptor_SetInterruptGate( 0x25, &IRQ_05 );
    Descriptor_SetInterruptGate( 0x26, &IRQ_06 );
    Descriptor_SetInterruptGate( 0x27, &IRQ_07 );
    Descriptor_SetInterruptGate( 0x28, &IRQ_08 );
    Descriptor_SetInterruptGate( 0x29, &IRQ_09 );
    Descriptor_SetInterruptGate( 0x2A, &IRQ_0A );
    Descriptor_SetInterruptGate( 0x2B, &IRQ_0B );
    Descriptor_SetInterruptGate( 0x2C, &IRQ_0C );
    Descriptor_SetInterruptGate( 0x2D, &IRQ_0D );
    Descriptor_SetInterruptGate( 0x2E, &IRQ_0E );
    Descriptor_SetInterruptGate( 0x2F, &IRQ_0F );

    // Load IDT
    //    asm volatile( "lidtl idt_ptr-0x7FF00000" );
    asm volatile( "lidtl idt_ptr" );

    KPrint( KDEBUG, "INTERRUPT", "Interrupts set up\n" );
}

void InterruptManager_CreateModuleInterface() {

    // Add to module list
    ModuleManager_CreateModule( "InterruptManager", InterruptManager_Handler );
    ModuleManager_CreateModuleCall( "InterruptManager", "AttachHandler", ATTACHHANDLER );
    ModuleManager_CreateModuleCall( "InterruptManager", "EnableInterrupt", ENABLEINTERRUPT );
}

void InterruptManager_Handle( uint32 nInterrupt ) {

    // Run the first handler for the interrupt
    if ( IRQ_Handler[ nInterrupt ] == NULL ) {

        // No handler specified
        KPrint( KSEVERE, "INTERRUPT", "No handler for interrupt %d\n", nInterrupt );
        PIC_EnableIRQ( nInterrupt );

    } else {

        // Disable and acknowledge
        PIC_MaskAndAcknowledge( nInterrupt );

        // Get handler
        K_sIRQ_Handler_t * psHandler = IRQ_Handler[ nInterrupt ];

        // Loop through all listed handlers until one returns true for handled
        bool nRet = false;
        while ( psHandler != NULL ) {
            nRet = psHandler->m_pHandler( );
            if ( nRet == true )
                break;
            psHandler = psHandler->m_psPrevious;
        }
        if ( nRet == false ) {
            // Interrupt not handled by any handler,
            KPrint( KSEVERE, "INTERRUPT", "Unhandled interrupt %d\n", nInterrupt );
        }

        // Re-enable interrupt
        PIC_EnableIRQ( nInterrupt );
    }
}

uint32 InterruptManager_AttachHandler( char *pszName, uint16 nInterrupt, void *pHandler ) {

    // Its critical that we kill interrupts
    bool bReenableInterrupts = Kg_bInterruptsActive;
    InterruptManager_Stop();

    // Allocate space for handler first
    K_sIRQ_Handler_t * psHandler = ( K_sIRQ_Handler_t * ) MemoryManager_KAlloc( sizeof( K_sIRQ_Handler_t ) );

    // Set name
    strncpy( ( char * ) & psHandler->m_szName, pszName, KOBJECT_NAMELENGTH );

    // Configure handler struct
    psHandler->m_pHandler = pHandler;

    // Add to linked list
    if ( IRQ_Handler[ nInterrupt ] == NULL ) {
        psHandler->m_psPrevious = NULL;
    } else {
        K_sIRQ_Handler_t *psPrevious = IRQ_Handler[ nInterrupt ];
        psHandler->m_psPrevious = psPrevious;
    }
    IRQ_Handler[ nInterrupt ] = psHandler;

    // Now its safe to re-enable
    if ( bReenableInterrupts == true )
        InterruptManager_Start();

    KPrint( KVERBOSE, "INTERRUPT", "Attached handler [%s] for IRQ [%lu]\n", pszName, nInterrupt );

    return NULL;
}

uint32 InterruptManager_AttachHandlerCall( KInterrupt_sAttachHandler_t * pData ) {
    return InterruptManager_AttachHandler( pData->m_pszName, pData->m_nInterrupt, pData->m_pHandler );
}

uint32 InterruptManager_EnableIRQ( uint16 nInterrupt ) {
    PIC_EnableIRQ( nInterrupt );
    KPrint( KVERBOSE, "INTERRUPT", "Enabled IRQ [%lu]\n", nInterrupt );
    return NULL;
}

uint32 InterruptManager_EnableIRQCall( KInterrupt_sIRQ_t * pData ) {
    return InterruptManager_EnableIRQ( pData->m_nInterrupt );
}

uint32 InterruptManager_Handler( uint32 nCall, void * pData ) {

    switch ( nCall ) {
    case ATTACHHANDLER:
        return InterruptManager_AttachHandlerCall( ( KInterrupt_sAttachHandler_t * ) pData );
    case ENABLEINTERRUPT:
        return InterruptManager_EnableIRQCall( ( KInterrupt_sIRQ_t * ) pData );
    }

    return KMODULE_INVALIDCALL;
}

