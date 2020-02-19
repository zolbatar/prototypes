#ifndef __ATOMIC_H__
#define __ATOMIC_H__

static inline uint32 Atomic_TestAndSet( uint32 *pnValue ) {
    uint32 nReturn;
asm volatile( "movl $1,%0;xchgl %0,%1;" : "=a" ( nReturn ) : "m" ( *pnValue ) : "memory" );
    return nReturn;
}

static inline uint32 Atomic_Add( uint32 *pnTarget, uint32 nValue ) {
    uint32 nReturn;
asm volatile( "lock; addl %1,%0;" : "=m" ( *pnTarget ) : "r" ( nValue ), "m" ( *pnTarget ) );
    return nReturn;
}

static inline uint32 Atomic_Sub( uint32 *pnTarget, uint32 nValue ) {
    uint32 nReturn;
asm volatile( "lock; subl %1,%0;" : "=m" ( *pnTarget ) : "r" ( nValue ), "m" ( *pnTarget ) );
    return nReturn;
}

#endif // __ATOMIC_H__
