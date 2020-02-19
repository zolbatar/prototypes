#ifndef __OS_LOCKING_H__
#define __OS_LOCKING_H__

#include <arch/x86/os-spinlock.h>

// Locking struct
typedef struct {
    OS_sSpinlock_t m_sSpinlock;
}
OS_sLock_t;

static inline void OS_Lock_Init( OS_sLock_t *psLock ) {

    // Init spinlock
    OS_Spinlock_Init( &psLock->m_sSpinlock );
}

static inline void OS_Lock_Lock( OS_sLock_t *psLock ) {

    asm ( "cli;" );
    OS_Spinlock_Lock( &psLock->m_sSpinlock );
}

static inline void OS_Lock_Unlock( OS_sLock_t * psLock ) {

    OS_Spinlock_Unlock( &psLock->m_sSpinlock );
    asm ( "sti;" );
}

#endif // __OS_LOCKING_H__
