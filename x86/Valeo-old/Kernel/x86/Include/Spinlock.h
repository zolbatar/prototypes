#ifndef __SPINLOCK_H__
#define __SPINLOCK_H__

#include <Atomic.h>

typedef struct {
    volatile uint32 m_nLock;
}
sSpinlock_t;

static inline void Spinlock_Init( sSpinlock_t *psLock ) {
    psLock->m_nLock = 0;
}

static inline void Spinlock_Lock( sSpinlock_t *psLock ) {

    // Spin until we get lock
    while ( Atomic_TestAndSet( ( uint32 * ) & psLock->m_nLock ) )
        ;
}

static inline void Spinlock_Unlock( sSpinlock_t *psLock ) {

    // Unlock spinlock
    psLock->m_nLock = 0;
}

static inline bool Spinlock_Trylock( sSpinlock_t *psLock ) {
    return Atomic_TestAndSet( ( uint32 * ) & psLock->m_nLock );
}

#endif // __SPINLOCK_H__

