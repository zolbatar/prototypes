#ifndef __K_MEMORYMANAGER_H__
#define __K_MEMORYMANAGER_H__

#include <Types.h>

#define K_MM_PAGESIZE 4096
#define K_MM_PAGESIZESHIFT 12

#define K_MM_KERNELSTACK 4
#define K_MM_KERNELADDRPAGED 0x80000000
#define K_MM_PAGETABLES 0x8FC00000
#define K_MM_KERNELHEAP 0x90000000
#define K_MM_HEAPPAGES (0xB0000000 - K_MM_KERNELHEAP) >> K_MM_PAGESIZESHIFT
#define K_MM_IOBUFFERAREA 0xB0000000
#define K_MM_IOBUFFERPAGES (0xE0000000 - K_MM_IOBUFFERAREA) >> K_MM_PAGESIZESHIFT
#define K_MM_MODULEAREA 0xE0000000
#define K_MM_DRIVERAREA 0xF0000000

#define K_MM_FREESBETWEENCOALESCING 10

#define K_MM_PTEFLAGS_PRESENT (1 << 0)
#define K_MM_PTEFLAGS_SYSTEM (1 << 1)
#define K_MM_FLAGS_USER (1 << 0)
#define K_MM_FLAGS_KERNEL (1 << 1)
#define K_MM_FLAGS_READONLY (1 << 2)
#define K_MM_FLAGS_READWRITE (1 << 3)
#define K_MM_PAGETYPE_ZEROFILL 512

#define PAGE_ALIGN(pAddress) ((((uint32)pAddress) >> K_MM_PAGESIZESHIFT) << K_MM_PAGESIZESHIFT)

typedef struct K_sKAlloc K_sKAlloc_t;
typedef struct K_sHeapFreeRegion K_sHeapFreeRegion_t;

// Main kernel memory allocated structure used for allocating heap memory
struct K_sKAlloc {
    uint32 m_nSize;
    K_sKAlloc_t *m_psNext;
};

struct K_sHeapFreeRegion {
    uint32 m_nSize;
    K_sHeapFreeRegion_t *m_psNext;
};

typedef struct {
    // Heap management
    void *m_pHeap;
    uint32 m_nPages;
    uint32 m_nFreesSinceCoalesce;

    K_sKAlloc_t *m_psAllocHead;
    K_sHeapFreeRegion_t *m_psFreeHead;
}
K_sKAllocator_t;

void MemoryManager_Init( K_sMBInfo_t *psMBInfo );
void MemoryManager_Lock( void );
void MemoryManager_Unlock( void );
void MemoryManager_CreateModuleInterface();
void MemoryManager_Page_AddFree( uint32 nPhysical );
uint32 MemoryManager_GetPTValue( uint32 nVirtualAddr );
uint32 MemoryManager_GetPTAddress( uint32 nVirtualAddr );
void MemoryManager_Page_Map( uint32 nPhysicalAddr, uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags );
void MemoryManager_Page_Unmap( uint32 nVirtualAddr, uint32 nPageCount );
void MemoryManager_Page_MapZeroFill( uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags );
void MemoryManager_Page_Allocate( uint32 nVirtualAddr, bool bZeroFill );
void MemoryManager_AllocInit( K_sKAllocator_t *psAllocator, void *pAddress, uint32 nPages );
void *MemoryManager_KAlloc( uint32 nSize );
void *MemoryManager_Alloc( uint32 nSize, K_sKAllocator_t *psAllocator );
void MemoryManager_KFree ( void *pAllocation );
void MemoryManager_Free( void *pAllocation, K_sKAllocator_t *psAllocator );


#endif // __K_MEMORYMANAGER_H__

