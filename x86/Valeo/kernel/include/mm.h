#ifndef __MM_H__
#define __MM_H__

#define MM_RELOCADJUST 0x7FF00000

#define MM_PAGESIZE 4096
#define MM_PAGESIZESHIFT 12

#define MM_KERNELSTACK 16
#define MM_KERNELADDRPAGED 0x80000000
#define MM_MODULEAREATOP 0x8FC00000
#define MM_PAGETABLES 0x8FC00000
#define MM_PAGETABLESEND 0x90000000
#define MM_PHYSICALMEMMAPAREA 0xF0000000
#define MM_PHYSICALMEMMAPPAGES 0x10000000 >> MM_PAGESIZESHIFT
#define MM_KERNELDATA 0x90000000
#define MM_KERNELDATAEND 0xF0000000
#define MM_KERNELDATAPAGES (MM_KERNELDATAEND - MM_KERNELDATA) >> MM_PAGESIZESHIFT

#define MM_FREESBETWEENCOALESCING 10

#define MM_PTEFLAGS_PRESENT (1 << 0)
#define MM_PTEFLAGS_SYSTEM (1 << 1)

// Not x86 PTE, but OS specific
#define MM_FLAGS_USER (1 << 0)
#define MM_FLAGS_KERNEL (1 << 1)
#define MM_FLAGS_READONLY (1 << 2)
#define MM_FLAGS_READWRITE (1 << 3)

// Bits 9/10/11 are available
#define MM_PAGETYPE_GET(x) (x & (7 << 9) >> 9)
#define MM_PAGETYPE_UNDEFINED 0
#define MM_PAGETYPE_ZEROFILL 1

#define MM_PAGEALIGN(pAddress) ((((uint32)pAddress) >> MM_PAGESIZESHIFT) << MM_PAGESIZESHIFT)

// Allocation struct, used for adding allocated pages to the process
#define MM_ENTRIESPERPROCESSPAGESTRUCT 32
#define MM_PROCESSPAGESTRUCTFULL 0xFFFFFFFF
#define MM_PAGENOTMAPPED 0xFFFFFFFF
#define MM_KERNELPTEs 512
#define MM_USERPTEs 512
#define MM_NOPTEENTRY 0xFFFFFFFF
typedef struct sProcessPages sProcessPages_t;
struct sProcessPages {
    uint32 m_nMap;	      	      	   	    		// 32 bits to signify which entries are used
    uint32 m_nPhysicalAddr[ MM_ENTRIESPERPROCESSPAGESTRUCT ];
    uint32 m_nVirtualAddr[ MM_ENTRIESPERPROCESSPAGESTRUCT ];
    sProcessPages_t *m_psNext;
};

// Initial process page struct
extern sProcessPages_t g_sKernelProcessPageStruct;

// Free page stack
typedef struct {
    uint32 m_nPhysicalAddr;
}
sFreePageStack_t;

// Main kernel memory allocated structure used for allocating heap memory
typedef struct sMMAlloc sMMAlloc_t;
struct sMMAlloc {
    uint32 m_nSize;
    sMMAlloc_t *m_psNext;
};

typedef struct sMMFreeRegion sMMFreeRegion_t;
struct sMMFreeRegion {
    uint32 m_nSize;
    sMMFreeRegion_t *m_psNext;
};

typedef struct {
    void *m_pHeap;
    uint32 m_nPages;
    uint32 m_nFreesSinceCoalesce;

    sMMAlloc_t *m_psAllocHead;
    sMMFreeRegion_t *m_psFreeHead;
}
sMMAllocator_t;

void MM_Init( sMBInfo_t *psMBInfo );
void MM_CreateObjects( void );
void MM_Lock( void );
void MM_Unlock( void );

// Page struct functions
void MM_ZeroPageStruct( sProcessPages_t *psProcessPages );
void MM_AddPage( uint32 nVirtualAddr, uint32 nPhysicalAddr );

// Memory manager, page table/directory functions
void MM_Page_Map( uint32 nPhysicalAddr, uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags );
void MM_Page_Unmap( uint32 nVirtualAddr, uint32 nPageCount );
void MM_Page_MapZeroFill( uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags );
void MM_Page_Allocate( uint32 nVirtualAddr, bool bZeroFill );
void MM_Page_Free( uint32 nVirtualAddr, uint32 nPageCount );
void MM_Page_AddFree( uint32 nPhysicalAddr );
uint32 MM_GetPTAddress( uint32 nVirtualAddr );
uint32 MM_GetPTValue( uint32 nVirtualAddr );

// Memory manager (generic)
void MM_AllocInit( sMMAllocator_t *psAllocator, void *pAddress, uint32 nPages );
void *MM_Alloc( uint32 nSize, sMMAllocator_t *psAllocator );
void *MM_Expand ( void *pAllocation, uint32 nAdditionalSize, sMMAllocator_t *psAllocator );
void MM_Free( void *pAllocation, sMMAllocator_t *psAllocator );
void MM_Coalesce( sMMAllocator_t *psAllocator );

// Memory manager (kernel alloc)
void *MM_KAlloc( uint32 nSize );
void MM_KFree ( void *pAllocation );
void *MM_KExpand ( void *pAllocation, uint32 nAdditionalSize );

// Debug routines
#ifdef DEBUG
void MM_DumpProcessPages( sProcessPages_t *psProcessPages );
void MM_DumpKernelPTEs( void );
void MM_DumpAllocation( sMMAllocator_t *psAllocator );
void MM_KDumpAlloction( void );
void MM_DumpFreeMap( sMMAllocator_t *psAllocator );
void MM_KDumpFreeMap( void );
#endif

#endif // __MM_H__

