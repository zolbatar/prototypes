#ifndef __ARCH_X86_ATOMIC_H__
#define __ARCH_X86_ATOMIC_H__

static inline uint32 Atomic_TestAndSet( uint32 *pnValue ) {
    uint32 nReturn;
asm volatile( "xchgl %0, %1;" : "=r"( nReturn ), "=m"( *pnValue ) : "0"( 1 ), "m"( *pnValue ) : "memory" );
    return nReturn;
}

static inline void Atomic_Add( uint32 *pnTarget, uint32 nValue ) {
asm volatile( "lock; addl %1,%0;" : "=m" ( *pnTarget ) : "r" ( nValue ), "m" ( *pnTarget ) );
}

static inline void Atomic_Sub( uint32 *pnTarget, uint32 nValue ) {
asm volatile( "lock; subl %1,%0;" : "=m" ( *pnTarget ) : "r" ( nValue ), "m" ( *pnTarget ) );
}

#endif // __ARCH_X86_ATOMIC_H__
