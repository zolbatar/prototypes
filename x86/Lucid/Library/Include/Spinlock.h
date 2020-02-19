#ifndef __K_STANDARD_SPINLOCK_H__
#define __K_STANDARD_SPINLOCK_H__

#include <Atomic.h>

typedef struct {
    volatile uint32 m_nLock;
}
K_sSpinlock_t;

static inline void Spinlock_Init( K_sSpinlock_t *psLock ) {
    psLock->m_nLock = 0;
}

static inline void Spinlock_Lock( K_sSpinlock_t *psLock ) {

    // Spin until we get lock
    while ( Atomic_TestAndSet( ( uint32 * ) & psLock->m_nLock ) )
        ;
}

static inline void Spinlock_Unlock( K_sSpinlock_t *psLock ) {

    // Unlock spinlock
    psLock->m_nLock = 0;
}

static inline bool Spinlock_Trylock( K_sSpinlock_t *psLock ) {
    return Atomic_TestAndSet( ( uint32 * ) & psLock->m_nLock );
}

#endif // __K_STANDARD_SPINLOCK_H__

