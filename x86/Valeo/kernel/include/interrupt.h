#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

// Interrupt call stack
typedef struct {
    uint32 sesp;
    uint16 sss, __sssu;
    uint32 edi;
    uint32 esi;
    uint32 ebp;
    uint32 edx;
    uint32 ecx;
    uint32 ebx;
    uint32 eax;
    uint16 ds, __dsh;
    uint16 es, __esh;
    uint16 fs, __fsh;
    uint16 gs, __gsh;
    uint32 eip;
    uint16 cs, __csh;
    uint32 eflags;
    uint32 esp;
    uint16 ss, __ssu;
}
sCallStack_t;

// Structure for interrupt handler
typedef KStatus IRQHandler( sCallStack_t *psStack );
typedef struct sIRQ_Handler sIRQ_Handler_t;
struct sIRQ_Handler {
    uint32 m_nPID;
    IRQHandler *m_pHandler;
    sIRQ_Handler_t *m_psPrevious;
};

void Interrupt_Init( void );
KStatus Interrupt_EnableIRQ( uint32 nInterrupt );
KStatus Interrupt_AttachHandler( uint32 nInterrupt, IRQHandler *pHandler );

#endif // __INTERRUPT_H__

