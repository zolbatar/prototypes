#ifndef __ARCH_X86_PROCESSOR_H__
#define __ARCH_X86_PROCESSOR_H__

#define KERNELCS 0x08
#define KERNELDS 0x10
#define USERCS   0x1B
#define USERDS   0x23
#define TSS      0x28

static inline void InvalidatePage( void *pAddress ) {
asm volatile ( "invlpg %0": : "m" ( pAddress ) : "memory" );
}

static inline void ReloadCR3( void ) {
asm volatile ( "movl %%cr3,%%eax ; movl %%eax,%%cr3"::: "memory" ) ;
}

static inline uint32 GetCR2() {
    uint32 cr2;
    asm volatile ( "mov %%cr2, %%eax;"
               "mov %%eax, %0": "=r" ( cr2 ) );
    return cr2;
}

static inline void LoadTaskRegister( uint16 nSelector ) {
asm volatile ( "ltr %0": : "r" ( nSelector ) );
}

static inline uint16 StoreTaskRegister() {
    unsigned int nSelector;
asm volatile ( "str %0": "=r" ( nSelector ) );
    return nSelector;
}

// Tss structure
typedef struct {
    uint16	back_link, __blh;
    uint32	esp0;
    uint16	ss0, __ss0h;
    uint32	esp1;
    uint16	ss1, __ss1h;
    uint32	esp2;
    uint16	ss2, __ss2h;
    uint32	cr3;
    uint32	eip;
    uint32	eflags;
    uint32	eax, ecx, edx, ebx;
    uint32	esp, ebp, esi, edi;
    uint16	es, __esh;
    uint16	cs, __csh;
    uint16	ss, __ssh;
    uint16	ds, __dsh;
    uint16	fs, __fsh;
    uint16	gs, __gsh;
    uint16	ldt, __ldth;
    uint16	trace, bitmap;
}
sTSS_t;

void DumpRegisters();

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

#endif // __ARCH_X86_PROCESSOR_H__

