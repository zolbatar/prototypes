#ifndef __OS_ARCH_X86_SPINLOCK_H__
#define __OS_ARCH_X86_SPINLOCK_H__

#include <sys/types.h>
#include <arch/x86/os-atomic.h>

typedef struct {
    volatile uint32 m_nLock;
}
OS_sSpinlock_t;

static inline void OS_Spinlock_Init( OS_sSpinlock_t *psLock ) {
    psLock->m_nLock = 0;
}

static inline void OS_Spinlock_Lock( OS_sSpinlock_t *psLock ) {

    // Spin until we get lock
    while ( OS_Atomic_TestAndSet( ( uint32 * ) & psLock->m_nLock ) )
        ;
}

static inline void OS_Spinlock_Unlock( OS_sSpinlock_t *psLock ) {

    // Unlock spinlock
    psLock->m_nLock = 0;
}

static inline bool OS_Spinlock_Trylock( OS_sSpinlock_t *psLock ) {
    return OS_Atomic_TestAndSet( ( uint32 * ) & psLock->m_nLock );
}

#endif // __OS_ARCH_X86_SPINLOCK_H__

