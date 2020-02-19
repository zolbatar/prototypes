#ifndef __LOCKING_H__
#define __LOCKING_H__

// Locking depth
extern uint32 g_nLockLevel;

// Locking struct
typedef struct {
    sSpinlock_t m_sSpinlock;
}
sLock_t;

static inline void Lock_Init( sLock_t *psLock ) {

    // Init spinlock
    Spinlock_Init( &psLock->m_sSpinlock );
}

static inline void Lock_Lock( sLock_t *psLock ) {

    // Only need locks if multi-tasking enabled
    if ( g_bKernelInitDone == true ) {
        Spinlock_Lock( &psLock->m_sSpinlock );
        g_nLockLevel++;
    }
}

static inline bool Lock_TryLock( sLock_t *psLock ) {

    // Only need locks if multi-tasking enabled
    if ( g_bKernelInitDone == true ) {
        return Spinlock_TryLock( &psLock->m_sSpinlock );
    } else {
        return false;
    }
}

static inline void Lock_Unlock( sLock_t * psLock ) {

    // Only need locks if multi-tasking enabled
    if ( g_bKernelInitDone == true ) {
        Spinlock_Unlock( &psLock->m_sSpinlock );
        g_nLockLevel--;
    }
}

#endif // __LOCKING_H__
