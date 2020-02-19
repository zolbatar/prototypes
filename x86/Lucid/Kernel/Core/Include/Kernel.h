#ifndef __K_KERNEL_H__
#define __K_KERNEL_H__

#include <Types.h>

#define K_VERSION_MAJOR 0
#define K_VERSION_MINOR 0
#define K_VERSION_REVISION 1
#define K_VERSION_CODENAME "Sirus"

// Boot modules
#define K_BOOTMODULES_MAX 8
typedef void ModuleEntry( );
typedef struct {
    void *m_pStart;
    void *m_pEnd;
    uint32 m_nLength;
    ModuleEntry *pEntry;
}
K_sBootModule_t;

// This is the main kernel structure
typedef struct {

    // Descriptors
    K_sIDT_t *m_sIDT;
    K_sGDT_t *m_sGDT;

    // Memory management
    uint32 m_nMemorySize;
    uint32 m_nKernelSize;
    void *m_nKernelEnd;
    uint32 *m_pnPageDirectory;
    uint32 *m_pnPageTables;
    uint32 *m_pnPageTablePointers;
    uint32 *m_pnFreePageStack;
    uint32 m_nFreePageStackIndex;
    void *m_pDriverAreaEnd;
    void *m_pModuleAreaEnd;

    // Memory allocation
    K_sKAllocator_t m_psAllocator;

    // Objects
    K_sObject_t *m_psTailObject;    	    	    // First
    K_sObject_t *m_psHeadObject;    	    	    // Last
    uint32 m_nObjectIndex;

    // Processes and threads
    K_sTSS_t m_sTSS;
    K_sObject_t *m_psRunningProcess;
    K_sObject_t *m_psRunningThread;
    uint32 m_psRunningProcessID;
    uint32 m_psRunningThreadID;
    uint32 m_nProcessID;
    uint32 m_nThreadID;
    K_sCallStack_t *m_psCallStack;

    // Timers
    K_sTimer_t *m_psLastTimer;
    uint32 m_nCurrentTimer;
    uint64 m_nTimer;

    // Module Manager
    uint32 m_nModuleIndex;

    // Boot modules
    uint32 m_nBootModuleCount;
    void *m_nBootModuleEnd;
    K_sBootModule_t m_pBootModules[ K_BOOTMODULES_MAX ];

    // Cache
    uint32 m_nCacheEntries;
    K_sIOCache_t *m_psCacheEntries;

    // File I/O
    uint32 m_nFileHandleIndex;

    // Debugging
    bool m_ShowDebug;
    bool m_ShowVerbose;
}
K_sKernel_t;

extern K_sKernel_t Kg_sKernel;

// This function is in Boot.S and halts the system
extern void halt( void );

#endif // __K_KERNEL_H__


