#include <Kernel.h>

// Externals
extern bool g_bKernelInitDone;
extern bool g_bTaskSwitchWaiting;
extern uint32 g_nLocksHeld;

void Lock_Init( char *pszName, sLock_t *psLock ) {

    // Copy name
    strcpy( ( char * ) & psLock->m_szName, pszName );

    // Init spinlock
    Spinlock_Init( &psLock->m_sSpinlock );
}

void Lock_Lock( sLock_t *psLock ) {

    // Only need locks if multi-tasking enabled
    if ( g_bKernelInitDone == true ) {

#ifdef VERBOSEDEBUG 
        //if (g_bKernelInitDone == true) {
        //    uint32 n;
        //asm volatile ( "mov 0x2C(%%esp), %0" : "=r" ( n ) );
        //    KPrint( "LOCKTRACE", "Lock %s: 0x%X\n", &psLock->m_szName, n );
        //}
#endif

        Atomic_Add( ( uint32 * ) & g_nLocksHeld, 1 );
        Spinlock_Lock( &psLock->m_sSpinlock );
    }
}

void Lock_Unlock( sLock_t * psLock ) {

    // Only need locks if multi-tasking enabled
    if ( g_bKernelInitDone == true ) {

#ifdef VERBOSEDEBUG 
        //if (g_bKernelInitDone == true) {
        //    uint32 n;
        //asm volatile ( "mov 0x2C(%%esp), %0" : "=r" ( n ) );
        //    KPrint( "LOCKTRACE", "Unlock %s: 0x%X\n", &psLock->m_szName, n );
        //}
#endif

        Spinlock_Unlock( &psLock->m_sSpinlock );
        Atomic_Sub( ( uint32 * ) & g_nLocksHeld, 1 );

        //	if ( g_nLocksHeld == 0 && g_bTaskSwitchWaiting == true ) {
        //    ObjectManager_Lock();
        //    ProcessManager_NextThread();
        //    ObjectManager_Unlock();
        //	}
    }
}
