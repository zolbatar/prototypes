#ifndef __K_InterruptManager_H__
#define __K_InterruptManager_H__

#include <Types.h>

extern volatile bool Kg_bInterruptsActive;

static inline void InterruptManager_Stop() {

    // This is used by locks so they know they can re-enable interrupts safely
    Kg_bInterruptsActive = false;

    // Now disable interrupts
    asm volatile( "cli;" );
}

static inline void InterruptManager_Start() {

    // This is used by locks so they know they can re-enable interrupts safely
    Kg_bInterruptsActive = true;

    // Now enable interrupts
    asm volatile( "sti;" );
}

typedef struct {
    uint32 edi;
    uint32 esi;
    uint32 ebp;
    uint32 edx;
    uint32 ecx;
    uint32 ebx;
    uint32 eax;
    uint16 gs, __gsh;
    uint16 fs, __fsh;
    uint16 es, __esh;
    uint16 ds, __dsh;
    uint32 eip;
    uint16 cs, __csh;
    uint32 eflags;
    uint32 esp;
    uint16 ss, __ssu;
}
K_sCallStack_t;

typedef struct {
    uint32 edi;
    uint32 esi;
    uint32 ebp;
    uint32 edx;
    uint32 ecx;
    uint32 ebx;
    uint32 eax;
    uint16 gs, __gsh;
    uint16 fs, __fsh;
    uint16 es, __esh;
    uint16 ds, __dsh;
    uint32 error;
    uint32 eip;
    uint16 cs, __csh;
    uint32 eflags;
    uint32 esp;
    uint16 ss, __ssu;
}
K_sCallStackWithErrorCode_t;

// Structure used when interrupt occurs, this points to a handler
// allows multiple handlers for one interrupt
typedef bool IRQHandler( );
typedef struct K_IRQ_Handler K_sIRQ_Handler_t;

struct K_IRQ_Handler {
    char m_szName[ KOBJECT_NAMELENGTH ];
    IRQHandler *m_pHandler;
    K_sIRQ_Handler_t *m_psPrevious;
};

void InterruptManager_Init( void );
void InterruptManager_CreateModuleInterface( void );
uint32 InterruptManager_EnableIRQ( uint16 nInterrupt );
uint32 InterruptManager_AttachHandler( char *pszName, uint16 nInterrupt, void *pHandler );

#endif // __K_InterruptManager_H__

