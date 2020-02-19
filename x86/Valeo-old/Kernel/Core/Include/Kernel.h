#ifndef __KERNEL_H__
#define __KERNEL_H__

#define DEBUG
#define VERBOSEDEBUG

// Standard includes
#include <Types.h>
#include <Printf.h>
#include <String.h>

// API's
#define API_IN_KERNEL
#include <API/Valeo-API.h>

// x86 Includes
#include <Descriptor.h>
#include <Processor.h>
#include <IOPort.h>
#include <Spinlock.h>
#include <8254.h>
#include <8259a.h>
#include <Console.h>

// Kernel modules
#include <MultiBoot.h>
#include <MemoryManager.h>
#include <ObjectManager.h>
#include <InterruptManager.h>
#include <ProcessManager.h>
#include <Locking.h>
#include <DeviceManager.h>
#include <MessageManager.h>
#include <ModuleManager.h>
#include <TimerManager.h>
#include <FileSystem.h>
#include <IOManager.h>
#include <Elf.h>
#include <DMMFileIO.h>

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_REVISION 1
#define VERSION_CODENAME "Sirus"

// Boot modules
#define K_BOOTMODULES_MAX 8
typedef void BootEntry( void );
typedef struct {
    void *m_pStart;
    void *m_pEnd;
    uint32 m_nLength;
    BootEntry *pEntry;
}
sBootModule_t;

// This is the main kernel structure
typedef struct {

    // Descriptors
    sIDT_t *m_sIDT;
    sGDT_t *m_sGDT;

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
    sMMAllocator_t m_psAllocator;

    // Objects
    sObject_t *m_psTailObject;
    sObject_t *m_psHeadObject;
    uint32 m_nObjectIndex;

    // Processes and threads
    sTSS_t m_sTSS;
    sObject_t *m_psRunningProcess;
    sObject_t *m_psRunningThread;
    uint32 m_psRunningProcessID;
    uint32 m_psRunningThreadID;
    uint32 m_nProcessID;
    uint32 m_nThreadID;

    // Message manager
    uint32 m_nMessageID;

    // Timers
    sTimer_t *m_psLastTimer;
    uint32 m_nCurrentTimer;
    uint64 m_nTimer;

    // Module Manager
    uint32 m_nModuleIndex;
    uint32 m_nModuleCallIndex;

    // Boot modules
    uint32 m_nBootModuleCount;
    void *m_nBootModuleEnd;
    sBootModule_t m_pBootModules[ K_BOOTMODULES_MAX ];

    // Cache
    uint32 m_nCacheEntries;
    sIOCache_t *m_psCacheEntries;

    // File I/O
    uint32 m_nFileHandleIndex;
}
sKernel_t;

extern sKernel_t g_sKernel;
extern bool g_bKernelInitDone;

// This function is in Boot.S and halts the system
extern void halt( void );

#endif // __KERNEL_H__


