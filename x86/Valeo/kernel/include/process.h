#ifndef __PROCESS_H__
#define __PROCESS_H__

enum {
    PROCESS_THREAD_NEW,
    PROCESS_THREAD_RUNNING,
    PROCESS_THREAD_READY,
    PROCESS_THREAD_SLEEPING,
    PROCESS_THREAD_DEAD,
    PROCESS_THREAD_WAITING
};

#define PROCESS_PROCESSSTACKSIZE (MM_PAGESIZE * 16)
#define PROCESS_MAXNESTDEPTH 8

#define PROCESS_SLEEPFOREVER 0

#define PROCESS_PID_KERNEL 0
#define PROCESS_THREAD_KERNEL 0

typedef struct sProcess sProcess_t;
struct sProcess {
    uint32 m_nPID;      		       // Process ID
    sMMAllocator_t *m_psAllocator;	       // Memory allocator
    uint16 m_nCS;
    uint16 m_nDS;
    uint16 m_nES;
    uint16 m_nFS;
    uint16 m_nGS;
    uint32 m_nSS;
    uint32 m_nThreadCount;		       // Thread count
    sProcessPages_t *m_psProcessPages;	       // Allocated physical memory pages
};

typedef struct sThread sThread_t;
struct sThread {
    sObject_t *m_psProcess;	       	       // Owning process
    uint32 m_nSS; 		       	       // Stack segment
    uint32 m_nESP[ PROCESS_MAXNESTDEPTH ];     // Stack pointer position
    uint32 m_nTID;     			       // Thread ID
    uint32 m_nNestDepth;		       // Kernel call nest depth
    uint32 m_nState;			       // Thread state i.e. running etc
    uint32 m_nSleep;                           // Thread sleep parameters
    uint32 m_nSleepTimeOut;                    // Thread sleep parameters
    uint32 m_nDispatchPriority;
    uint64 m_nCPUTime;			       // CPU time used
    sObject_t *m_psMessagePort;                // Message port
};

void Process_Init( void );
KStatus Process_CreateProcess( uint32 *nPID, sObject_t **psProcessOut, bool bCreateProcessPageStruct );
KStatus Process_CreateThread( sObject_t *psProcessObject, uint32 nEIP, uint32 *nTID, sObject_t **psThreadOut );
KStatus Process_KillThread( void );
KStatus Process_Preempt( sCallStack_t *psStack );

#endif // __PROCESS_H__
