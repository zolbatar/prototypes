#ifndef __OS_PROCESS_H__
#define __OS_PROCESS_H__

typedef struct {
    uint32 m_nEIP;
    uint32 m_nTID;
}
OS_Process_CreateThread_t;

static inline OS_KStatus OS_Process_Createthread( void *nEIP, uint32 *nTID ) {

    // Create create thread struct
    OS_Process_CreateThread_t sThread;
    sThread.m_nEIP = ( uint32 ) nEIP;

    // Call kernel function
    uint32 nEAX = OS_PROCESS_CREATETHREAD;
    OS_KStatus nResult;
asm volatile( "int $0x80" : "=a" ( nResult ) : "a" ( nEAX ), "b" ( &sThread ) );

    // Extract return information
    *nTID = sThread.m_nTID;

    return nResult;
}

static inline void OS_Process_Relinquish( ) {

    // Call kernel function
    uint32 nEAX = OS_PROCESS_RELINQUISH;
    OS_KStatus nResult;
asm volatile( "int $0x80;" : "=a" ( nResult ) : "a" ( nEAX ) );

}

static inline void OS_Process_EndThread( ) {

    // Call kernel function
    uint32 nEAX = OS_PROCESS_ENDTHREAD;
    OS_KStatus nResult;
asm volatile( "int $0x80" : "=a" ( nResult ) : "a" ( nEAX ) );

    // Now, switch threads, keep repeating until we definately switch thread
    while ( 1 ) {
        OS_Process_Relinquish();
    }
}

#endif // __OS_PROCESS_H__
