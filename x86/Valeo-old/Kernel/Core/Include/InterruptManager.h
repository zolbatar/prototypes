#ifndef __InterruptManager_H__
#define __InterruptManager_H__

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
    uint32 error;
    uint32 eip;
    uint16 cs, __csh;
    uint32 eflags;
    uint32 esp;
    uint16 ss, __ssu;
}
sCallStackWithErrorCode_t;

// Structure used when interrupt occurs, this points to a handler
// allows multiple handlers for one interrupt
typedef struct sIRQ_Handler sIRQ_Handler_t;

struct sIRQ_Handler {
    char m_szName[ OM_NAMELENGTH ];
    IRQHandler *m_pHandler;
    sIRQ_Handler_t *m_psPrevious;
};

void InterruptManager_Init( void );
void InterruptManager_CreateModuleInterface( void );
KStatus InterruptManager_EnableIRQ( uint32 nInterrupt );
KStatus InterruptManager_AttachHandler( char *pszName, uint32 nInterrupt, IRQHandler *pHandler );
void InterruptManager_CreateModuleInterface( void );

#endif // __InterruptManager_H__

