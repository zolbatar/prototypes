#ifndef __MEMORYMANAGER_H__
#define __MEMORYMANAGER_H__

#define MM_PAGESIZE 4096
#define MM_PAGESIZESHIFT 12

#define MM_KERNELSTACK 4
#define MM_KERNELADDRPAGED 0x80000000
#define MM_PAGETABLES 0x8FC00000
#define MM_KERNELHEAP 0x90000000
#define MM_HEAPPAGES (0xB0000000 - MM_KERNELHEAP) >> MM_PAGESIZESHIFT
#define MM_IOBUFFERAREA 0xB0000000
#define MM_IOBUFFERPAGES (0xE0000000 - MM_IOBUFFERAREA) >> MM_PAGESIZESHIFT
#define MM_MODULEAREA 0xE0000000
#define MM_MODULEAREAPAGES (0xF0000000 - MM_MODULEAREA) >> MM_PAGESIZESHIFT
#define MM_DRIVERAREA 0xF0000000

#define MM_FREESBETWEENCOALESCING 10

#define MM_PTEFLAGS_PRESENT (1 << 0)
#define MM_PTEFLAGS_SYSTEM (1 << 1)
#define MM_FLAGS_USER (1 << 0)
#define MM_FLAGS_KERNEL (1 << 1)
#define MM_FLAGS_READONLY (1 << 2)
#define MM_FLAGS_READWRITE (1 << 3)
#define MM_PAGETYPE_ZEROFILL 512

#define MM_PAGEALIGN(pAddress) ((((uint32)pAddress) >> MM_PAGESIZESHIFT) << MM_PAGESIZESHIFT)

typedef struct sMMAlloc sMMAlloc_t;
typedef struct sMMFreeRegion sMMFreeRegion_t;

// Main kernel memory allocated structure used for allocating heap memory
struct sMMAlloc {
    uint32 m_nSize;
    sMMAlloc_t *m_psNext;
};

struct sMMFreeRegion {
    uint32 m_nSize;
    sMMFreeRegion_t *m_psNext;
};

typedef struct {
    // Heap management
    void *m_pHeap;
    uint32 m_nPages;
    uint32 m_nFreesSinceCoalesce;

    sMMAlloc_t *m_psAllocHead;
    sMMFreeRegion_t *m_psFreeHead;
}
sMMAllocator_t;

void MemoryManager_Init( sMBInfo_t *psMBInfo );
void MemoryManager_Lock( void );
void MemoryManager_Unlock( void );
void MemoryManager_CreateModuleInterface( void );
void MemoryManager_Page_AddFree( uint32 nPhysical );
uint32 MemoryManager_GetPTValue( uint32 nVirtualAddr );
uint32 MemoryManager_GetPTAddress( uint32 nVirtualAddr );
void MemoryManager_Page_Map( uint32 nPhysicalAddr, uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags );
void MemoryManager_Page_Unmap( uint32 nVirtualAddr, uint32 nPageCount );
void MemoryManager_Page_MapZeroFill( uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags );
void MemoryManager_Page_Allocate( uint32 nVirtualAddr, bool bZeroFill );
void MemoryManager_AllocInit( sMMAllocator_t *psAllocator, void *pAddress, uint32 nPages );
void *MemoryManager_KAlloc( uint32 nSize );
void *MemoryManager_Alloc( uint32 nSize, sMMAllocator_t *psAllocator );
void MemoryManager_KFree ( void *pAllocation );
void MemoryManager_Free( void *pAllocation, sMMAllocator_t *psAllocator );
void *MemoryManager_KExpand ( void *pAllocation, uint32 nAdditionalSize );
void *MemoryManager_Expand ( void *pAllocation, uint32 nAdditionalSize, sMMAllocator_t *psAllocator );
void MemoryManager_DumpAllocation( sMMAllocator_t *psAllocator );
void MemoryManager_DumpFreeMap( sMMAllocator_t *psAllocator );

#endif // __MEMORYMANAGER_H__

