#ifndef __K_LOCKING_H__
#define __K_LOCKING_H__

#include <Types.h>

// Locking struct
typedef struct {
    K_sSpinlock_t m_sSpinlock;
}
K_sLock_t;

// Externals
uint32 ProcessManager_NextThread( );
extern volatile bool Kg_bTaskSwitchWaiting;
extern volatile bool Kg_bInISR;
extern volatile uint32 Kg_nLocksHeld;

static inline void Lock_Init( K_sLock_t *psLock ) {
    Spinlock_Init( &psLock->m_sSpinlock );
}

static inline void Lock_Lock( K_sLock_t *psLock ) {

    // Its critical that we kill interrupts (if not in ISR)
    bool bReenableInterrupts = Kg_bInterruptsActive;
    if ( Kg_bInISR == false ) {
        InterruptManager_Stop();
    }

    Atomic_Add( ( uint32 * ) & Kg_nLocksHeld, 1 );
    Spinlock_Lock( &psLock->m_sSpinlock );

    // Now its safe to re-enable
    if ( Kg_bInISR == false && bReenableInterrupts == true ) {
        InterruptManager_Start();
    }
}

static inline void Lock_Unlock( K_sLock_t * psLock ) {

    // Its critical that we kill interrupts (if not in ISR)
    bool bReenableInterrupts = Kg_bInterruptsActive;
    if ( Kg_bInISR == false ) {
        InterruptManager_Stop();
    }

    Spinlock_Unlock( &psLock->m_sSpinlock );
    Atomic_Sub( ( uint32 * ) & Kg_nLocksHeld, 1 );

    if ( Kg_nLocksHeld == 0 && Kg_bTaskSwitchWaiting == true ) {
        ProcessManager_NextThread( );
    }

    // Now its safe to re-enable
    if ( Kg_bInISR == false && bReenableInterrupts == true ) {
        InterruptManager_Start();
    }
}

#endif // __K_LOCKING_H__
