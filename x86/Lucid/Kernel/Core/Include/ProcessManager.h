#ifndef __K_PROCESSMANAGER_H__
#define __K_PROCESSMANAGER_H__

#include <Types.h>

enum {
    THREAD_NEW,
    THREAD_RUNNING,
    THREAD_READY,
    THREAD_SLEEPING,
    THREAD_WAITING,
    THREAD_TERMINATED
};

#define K_SCHEDULER_KERNELTHREADSTACKSIZE (K_MM_PAGESIZE * 16)
#define K_NESTDEPTH 16

typedef struct {
    uint32 m_nID;      			       // Process ID
    K_sKAllocator_t *m_psAllocator;	       // Memory allocator
    uint16 m_nCS;
    uint16 m_nDS;
    uint16 m_nES;
    uint16 m_nFS;
    uint16 m_nGS;
    uint32 m_nSS;
    uint32 m_nThreadCount;		       // Thread count
    uint32 m_nBasePriority;		       // Base priority
}
K_sProcess_t;

typedef struct {
    K_sObject_t *m_psProcess;	       	       // Owning process
    uint32 m_nID;      			       // Thread ID
    uint32 m_nSS; 		       	       // Stack segment
    uint32 m_nESP[ K_NESTDEPTH ];	       // Stack pointer position
    uint32 m_nNestDepth;		       // Kernel call nest depth
    uint32 m_nState;			       // Thread state i.e. running etc
    uint32 m_nBasePriority;		       // Base priority
    uint32 m_nCurrentPriority;		       // Adjusted depending on usage
    uint32 m_nSleep;                           // Thread sleep parameters
    uint32 m_nSleepTimeOut;                    // Thread sleep parameters
    uint64 m_nCPUTime;			       // CPU time used
    K_sObject_t *m_psMessagePort;              // Message port
}
K_sThread_t;

void ProcessManager_Init( void );
uint32 ProcessManager_Awaken( uint32 nThreadID );
uint32 ProcessManager_CreateThread( K_sObject_t *psProcessObject, uint32 nEIP );

#endif // __K_PROCESSMANAGER_H__
