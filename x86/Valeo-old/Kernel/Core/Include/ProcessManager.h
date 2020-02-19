#ifndef __PROCESSMANAGER_H__
#define __PROCESSMANAGER_H__

enum {
    PM_THREAD_NEW,
    PM_THREAD_RUNNING,
    PM_THREAD_READY,
    PM_THREAD_SLEEPING,
    PM_THREAD_WAITING,
    PM_THREAD_TERMINATED
};

#define PM_KERNELTHREADSTACKSIZE (MM_PAGESIZE * 16)
#define PM_NESTDEPTH 8

typedef struct sProcess sProcess_t;
struct sProcess {
    char m_szName[ PM_NAMELENGTH ];
    uint32 m_nPID;      		       // Process ID
    sMMAllocator_t *m_psAllocator;	       // Memory allocator
    uint16 m_nCS;
    uint16 m_nDS;
    uint16 m_nES;
    uint16 m_nFS;
    uint16 m_nGS;
    uint32 m_nSS;
    uint32 m_nThreadCount;		       // Thread count
    uint32 m_nBasePriority;		       // Base priority
};

typedef struct sThread sThread_t;
struct sThread {
    sProcess_t *m_psProcess;	       	       // Owning process
    uint32 m_nSS; 		       	       // Stack segment
    uint32 m_nESP[ PM_NESTDEPTH ];	       // Stack pointer position
    uint32 m_nTID;     			       // Thread ID
    uint32 m_nNestDepth;		       // Kernel call nest depth
    uint32 m_nState;			       // Thread state i.e. running etc
    uint32 m_nBasePriority;		       // Base priority
    uint32 m_nCurrentPriority;		       // Adjusted depending on usage
    uint32 m_nSleep;                           // Thread sleep parameters
    uint32 m_nSleepTimeOut;                    // Thread sleep parameters
    uint64 m_nCPUTime;			       // CPU time used
    sObject_t *m_psMessagePort;              // Message port
};

void ProcessManager_Init( void );
KStatus ProcessManager_CreateProcess( char * pszName, uint32 *nPID, sObject_t **psProcessOut );
KStatus ProcessManager_CreateThread( sProcess_t *psProcess, uint32 nEIP, uint32 *nTID, sObject_t **psThreadOut );
KStatus ProcessManager_RunThread( uint32 nPID );
KStatus ProcessManager_Sleep( uint32 nTimeOut );
KStatus ProcessManager_Awaken( uint32 nTID );
KStatus ProcessManager_Preempt( sCallStack_t *psStack );
void ProcessManager_CreateModuleInterface( void );

#endif // __PROCESSMANAGER_H__
