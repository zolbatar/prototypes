#ifndef __KERNEL_H__
#define __KERNEL_H__

#define DEBUG

// Standard includes
#include <sys/io.h>
#include <sys/types.h>
#include <printf.h>
#include <string.h>

extern bool g_bKernelInitDone;

// kernel types
typedef uint32 KStatus;

// x86 Includes
#include <arch/x86/descriptor.h>
#include <arch/x86/processor.h>
#include <arch/x86/spinlock.h>
#include <arch/x86/8254.h>
#include <arch/x86/8259a.h>
#include <arch/x86/textmodevideo.h>

// Add API
#include <os.h>

// Boot modules
#define K_BOOTMODULES_MAX 8
typedef void BootEntry( void );
typedef struct {
    void *m_pStart;
    void *m_pEnd;
    uint32 m_nLength;
    BootEntry *m_pEntry;
    void *m_pLoadedAddress;
    void *m_pLoadedAddressEnd;
    uint32 m_nLoadedAddressPages;
}
sBootModule_t;

// Kernel modules
#include <multiboot.h>
#include <interrupt.h>
#include <mm.h>
#include <syslog.h>
#include <object.h>
#include <timer.h>
#include <process.h>
#include <ipc.h>
#include <module.h>
#include <elf.h>
#include <syscall.h>
#include <locking.h>

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_REVISION 1
#define VERSION_NAME "Valeo (Sirus)"

// This is the main kernel structure
typedef struct {

    // Descriptors
    sIDT_t *m_sIDT;
    sGDT_t *m_sGDT;

    // Memory management
    uint32 m_nMemorySizePages;
    uint32 m_nMemorySizeKB;
    uint32 m_nKernelSize;
    void *m_nKernelEnd;
    uint32 *m_pnPageDirectory;
    uint32 *m_pnPageTables;
    sFreePageStack_t *m_psFreePageStack;
    uint32 m_nFreePageStackIndex;
    void *m_pModuleArea;
    void *m_pPhysicalMemMapArea;
    uint32 m_nDataAreaPages;
    sObjectDirectory_t *m_psSystemMemoryManager;
    sProcessPages_t *m_psKernelProcessPages;
    uint32 *m_pnKernelPTEs;

    // Kernel memory allocator
    sMMAllocator_t m_psAllocator;

    // Boot modules
    uint32 m_nBootModuleCount;
    void *m_pBootModuleStart;
    void *m_pBootModuleEnd;
    sBootModule_t m_sBootModules[ K_BOOTMODULES_MAX ];

    // Objects
    sObjectDirectory_t *m_psRootPath;
    sObjectDirectory_t *m_psSystemRoot;
    uint32 m_nType;
    uint32 m_nTypeDirectory;
    uint32 m_nTypeWordValue;

    // Timers
    sTimer_t *m_psLastTimer;
    uint64 m_nTimer;

    // Processes and threads
    sObjectDirectory_t *m_psSystemProcesses;
    sObjectDirectory_t *m_psSystemThreads;
    sTSS_t m_sTSS;
    sObject_t *m_psRunningProcess;
    sObject_t *m_psRunningThread;
    uint32 m_psRunningProcessID;
    uint32 m_psRunningThreadID;
    uint32 m_nProcessID;
    uint32 m_nThreadID;
    uint32 m_nTypeProcess;
    uint32 m_nTypeThread;

    // Message manager
    sObjectDirectory_t *m_psSystemMessagePorts;
    sObjectDirectory_t *m_psSystemMessages;

    // IPC
    uint32 m_nMessageID;
    uint32 m_nTypeMessagePort;
    uint32 m_nTypeMessages;

    // Modules
    sObjectDirectory_t *m_psModules;
    uint32 m_nTypeModule;
}
sKernel_t;
extern sKernel_t g_sKernel;

// This function is in Boot.S and halts the system
extern void halt( void );

#endif // __KERNEL_H__


