#include <Kernel.h>

extern uint32 *CorePageTable;
extern uint32 *ZeroPageTable;
extern uint32 *PageTables;

extern void MemoryManagerAllocCall();
extern void MemoryManagerFreeCall();

/* Note: Memory Structure
0x80000000 = Kernel
           > Page Directory
           > Page Table for Page Table Mapping
           > Free page stack
           > Module + kernel space
0x8FC00000 = Page Table Mapping
0x90000000 = Kernel Heap (upto 0xAFFFFFFF)
0xB0000000 = Buffer Space (upto 0xDFFFFFFF)
0xE0000000 = Module Space (Upto 0xEFFFFFFF)
0xF0000000 = Device mapping space
*/

// Lock
sLock_t sMemoryLock;

void MemoryManager_LockInit() {
    Lock_Init( "MEMORY", &sMemoryLock );
}

void MemoryManager_Lock() {
    Lock_Lock( &sMemoryLock );
}

void MemoryManager_Unlock() {
    Lock_Unlock( &sMemoryLock );
}

void MemoryManager_Init( sMBInfo_t *psMBInfo ) {

    // See if there is a multiboot structure, if not error
    if ( !( ( psMBInfo->m_nFlags ) & ( 1 << 6 ) ) ) {
        KPrint( "MMU", "FATAL: No multiboot memory map information available - Halting\n" );
        halt();
    }

    // Set start of driver area
    g_sKernel.m_pDriverAreaEnd = ( void * ) MM_DRIVERAREA;

    // Set start of module area
    g_sKernel.m_pModuleAreaEnd = ( void * ) MM_MODULEAREA;

    // Initialise locking
    MemoryManager_LockInit();

    // Map page tables for 0x80000000/0x8FC00000 (set up in Boot.S) up to the 0x8FC- page table mapping region
    g_sKernel.m_pnPageTablePointers [ 0x80000000 >> 22 ] = ( ( uint32 ) CorePageTable ) | 3;
    g_sKernel.m_pnPageTablePointers [ 0x8FC00000 >> 22 ] = ( ( uint32 ) PageTables ) | 3;

    // Calculate Memory in 4K pages,
    // we use the passed multiboot structure to correctly allow for holes in memory
    int nNumsMMapEntries = ( psMBInfo->m_nMMAPLength ) / sizeof ( sMBMemoryMap_t );
    sMBMemoryMap_t *sMMap = ( sMBMemoryMap_t * ) psMBInfo->m_nMMAPAddr;
    uint32 nPages = 0;

    // Loop through the memory regions first and do a count of the total number of
    // entries required, we can then allocate the required space
    uint32 i;
    for ( i = 0; i < nNumsMMapEntries; i++ ) {

        // Make sure its a type 0x1, i.e. RAM
        if ( sMMap->m_nType == ( uint32 ) 0x1 ) {

            // Get RAM region (length is rounded to page size)
            nPages += ( ( sMMap->m_nLengthHigh * 256 ) + sMMap->m_nLengthLow ) >> MM_PAGESIZESHIFT;

        }
        sMMap = ( sMBMemoryMap_t * ) ( ( uint32 ) sMMap + ( sMMap->m_nSize + ( uint32 ) sizeof ( sMMap->m_nSize ) ) );
    }

    // Kernel not in free memory
    nPages -= g_sKernel.m_nKernelSize;

    // Or free page stack itself
    nPages -= nPages >> 10 ;
    g_sKernel.m_nMemorySize = nPages;
    KPrint( "MMU", "Size of memory is [%u Pages] [%u Kb]\n", g_sKernel.m_nMemorySize, g_sKernel.m_nMemorySize << 2 );

    // Align free page stack to page boundary
    nPages = ( ( nPages * 4 ) + 4095 ) >> MM_PAGESIZESHIFT;
    KPrint( "MMU", "Size of free page stack is [%u Pages]\n", nPages );

    // Allocate space for free space table, put it straight after kernel in physical ram
    g_sKernel.m_pnFreePageStack = ( uint32 * ) g_sKernel.m_nKernelEnd;
    uint32 nFreePageStackPhysical = 0x200000 + ( ( MM_KERNELSTACK + 16 ) << MM_PAGESIZESHIFT );
    uint32 nFreePageStackPhysicalEnd = nFreePageStackPhysical + ( nPages << MM_PAGESIZESHIFT );
    MemoryManager_Lock();
    MemoryManager_Page_Map( nFreePageStackPhysical, ( uint32 ) g_sKernel.m_pnFreePageStack, nPages, MM_FLAGS_KERNEL | MM_FLAGS_READWRITE );
    MemoryManager_Unlock();
    g_sKernel.m_nKernelEnd += nPages << MM_PAGESIZESHIFT;

    // Now actually store address of each free page in the free page stack
    g_sKernel.m_nFreePageStackIndex = 0;
    sMMap = ( sMBMemoryMap_t * ) psMBInfo->m_nMMAPAddr;
    for ( i = 0; i < nNumsMMapEntries; i++ ) {

        // Make sure its a type 0x1, i.e. RAM
        if ( sMMap->m_nType == ( uint32 ) 0x1 ) {

            // Get address and length of RAM region (length is rounded to pages)
            uint32 nAddr = ( sMMap->m_nBaseAddrHigh * 256 ) + sMMap->m_nBaseAddrLow;
            uint32 nLen = ( ( sMMap->m_nLengthHigh * 256 ) + sMMap->m_nLengthLow ) >> MM_PAGESIZESHIFT;

            // Add these pages to the stack
            uint32 j;
            for ( j = 0; j < nLen; j++ ) {

                if ( ( nAddr >= 0x100000 ) && ( nAddr < ( uint32 ) g_sKernel.m_nBootModuleEnd ) ) {
                    // Kernel space, ignore
                } else if ( ( nAddr >= 0x200000 ) && ( nAddr < nFreePageStackPhysicalEnd ) ) {
                    // Stack space and page table/page directory, ignore
                } else {
                    g_sKernel.m_pnFreePageStack[ g_sKernel.m_nFreePageStackIndex++ ] = nAddr;
                }

                // Move to next page
                nAddr += MM_PAGESIZE;
            }
        }
        sMMap = ( sMBMemoryMap_t * ) ( ( unsigned long ) sMMap + ( sMMap->m_nSize + sizeof ( sMMap->m_nSize ) ) );
    }
    g_sKernel.m_nFreePageStackIndex--;

    // Setup memory allocator
    MemoryManager_Lock();
    MemoryManager_AllocInit( &g_sKernel.m_psAllocator, ( void * ) MM_KERNELHEAP, MM_HEAPPAGES );
    MemoryManager_Unlock();
    KPrint( "MMU", "Kernel heap of [%u KBytes] maximum created\n", ( MM_HEAPPAGES << MM_PAGESIZESHIFT ) / 1024 );

    // Remap console to driver area
    Console_Remap();

    // Create ISR interfaces
    Descriptor_SetInterruptGate( 0x90, &MemoryManagerAllocCall );
    Descriptor_SetInterruptGate( 0x91, &MemoryManagerFreeCall );

    // Unmap identity-mapped lower 4MB of memory, we don't need it now
    //    g_sKernel.m_pnPageTablePointers[ 0 ] = 0;
    //    g_sKernel.m_pnPageDirectory[ 0 ] = 0;
    //    ReloadCR3( );
    //    MemoryManager_Page_AddFree( ( uint32 ) ZeroPageTable );

    KPrint( "MMU", "Memory manager initialised\n" );
}

void MemoryManager_CreateModuleInterface() {

    // Create memory objects
    ObjectManager_ConstructPath( "/MemoryManager/" );
    ObjectManager_ConstructKey( "MemorySize(InPages)" );
    ObjectManager_CreateEntityWord( g_sKernel.m_nMemorySize );
}

static inline uint32 MemoryManager_Page_GetFree( ) {

    if ( g_sKernel.m_nFreePageStackIndex == 0xFFFFFFFF ) {  // 0xFFFFFFFF == -1
        KPrint( "MMU", "FATAL: No memory available - Halting\n" );
        halt();
    }

    //  Get physical address of next page of free page stack and return it
    return g_sKernel.m_pnFreePageStack[ g_sKernel.m_nFreePageStackIndex-- ];
    ;
}

void MemoryManager_Page_AddFree( uint32 nPhysical ) {

    // Add page to free page stack
    g_sKernel.m_pnFreePageStack[ g_sKernel.m_nFreePageStackIndex++ ] = nPhysical;
}

uint32 MemoryManager_GetPTValue( uint32 nVirtualAddr ) {

    // Get page table address
    uint32 nPT = MemoryManager_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;
    return g_sKernel.m_pnPageTables[ nPT + nPTOffset ];
}

uint32 MemoryManager_GetPTAddress( uint32 nVirtualAddr ) {

    // Calculate PDE entry
    uint32 nPDE = nVirtualAddr >> 22;

    // Get page table entry address
    uint32 nPT = g_sKernel.m_pnPageDirectory[ nPDE ];

    // See if we need to create a new page table
    if ( nPT == 0 ) {

        // We need to get a free page to allocate for the page table
        uint32 nRealAddr = MemoryManager_Page_GetFree();

        // Map into page table area and zero all entries
        g_sKernel.m_pnPageTablePointers[ nPDE ] = nRealAddr | ( ( uint32 ) 3 );
        memset( ( void * ) ( &g_sKernel.m_pnPageTables[ nPDE << 10 ] ), 0, 4096 );

        // And add to page directory
        g_sKernel.m_pnPageDirectory[ nPDE ] = nRealAddr | ( ( uint32 ) 3 );
    }

    return ( nPDE << 22 );
}

void MemoryManager_Page_Map( uint32 nPhysicalAddr, uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags ) {

    // Get page table address and offset
    uint32 nPT = MemoryManager_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;

    // Loop through and map all pages
    uint32 i;
    for ( i = 0;i < nPageCount; i++ ) {

        // Check we haven't moved to a new page table entry
        if ( nPTOffset == 1024 ) {
            nPT = MemoryManager_GetPTAddress ( nVirtualAddr ) >> MM_PAGESIZESHIFT;
            nPTOffset = 0;
        }

        // Set page table entry
        g_sKernel.m_pnPageTables[ nPT + nPTOffset ] = nPhysicalAddr | 3;

        // Move to next page
        nPTOffset++;
        nVirtualAddr += 4096;
        nPhysicalAddr += 4096;

    }

    // Reload CR3
    ReloadCR3( );
}

void MemoryManager_Page_Unmap( uint32 nVirtualAddr, uint32 nPageCount ) {

    // Get page table address and offset
    uint32 nPT = MemoryManager_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;

    // Loop through and unmap all pages
    uint32 i;
    for ( i = 0;i < nPageCount; i++ ) {

        // Check we haven't moved to a new page table entry
        if ( nPTOffset == 1024 ) {
            nPT = MemoryManager_GetPTAddress ( nVirtualAddr ) >> MM_PAGESIZESHIFT;
            nPTOffset = 0;
        }

        // Set page table entry
        g_sKernel.m_pnPageTables[ nPT + nPTOffset ] = 0;

        // Move to next page
        nPTOffset++;
        nVirtualAddr += 4096;
    }

    // Reload CR3
    ReloadCR3( );
}

void MemoryManager_Page_MapZeroFill( uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags ) {

    // Get page table address and offset
    uint32 nPT = MemoryManager_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;

    // Loop through and zero map all pages
    uint32 i;
    for ( i = 0;i < nPageCount; i++ ) {

        // Check we haven't moved to a new page table entry
        if ( nPTOffset == 1024 ) {
            nPT = MemoryManager_GetPTAddress ( nVirtualAddr ) >> MM_PAGESIZESHIFT;
            nPTOffset = 0;
        }

        // Set page table entry
        g_sKernel.m_pnPageTables[ nPT + nPTOffset ] = MM_PAGETYPE_ZEROFILL | 2;

        // Move to next page
        nPTOffset++;
        nVirtualAddr += 4096;
    }

    // Reload CR3
    ReloadCR3( );
}

void MemoryManager_Page_Allocate( uint32 nVirtualAddr, bool bZeroFill ) {

    // Get page table address and offset
    uint32 nPT = MemoryManager_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;

    // Set page table entry to point to free physical page
    g_sKernel.m_pnPageTables[ nPT + nPTOffset ] = MemoryManager_Page_GetFree() | 3;

    // Do we need to zero fill?
    if ( bZeroFill == true ) {
        memset( ( void * ) ( nVirtualAddr ) , 0, 4096 );
    }

    // Invalidate TLB entry
    InvalidatePage( ( void * ) ( nVirtualAddr ) );
}

void MemoryManager_DumpAllocation( sMMAllocator_t *psAllocator ) {

    KPrint( "MMU", "Kernel heap - Allocation map\n" );
    sMMAlloc_t * psAlloc = psAllocator->m_psAllocHead;
    while ( psAlloc != NULL ) {
        KPrint( "MMU", "Alloc: 0x%X-0x%X (%lu bytes)\n", ( uint32 ) psAlloc + ( uint32 ) sizeof( sMMAlloc_t ), ( uint32 ) psAlloc + ( uint32 ) psAlloc->m_nSize + ( uint32 ) sizeof( sMMAlloc_t ), psAlloc->m_nSize, psAlloc->m_psNext );
        psAlloc = psAlloc->m_psNext;
    }
}

void MemoryManager_DumpFreeMap( sMMAllocator_t *psAllocator ) {

    KPrint( "MMU", "Kernel heap - Free space map\n" );
    sMMFreeRegion_t * psFreeHole = psAllocator->m_psFreeHead;
    while ( psFreeHole != NULL ) {
        KPrint( "MMU", "Free: 0x%X-0x%X (%lu bytes)\n", ( uint32 ) psFreeHole + ( uint32 ) sizeof( sMMFreeRegion_t ), ( uint32 ) psFreeHole + ( uint32 ) psFreeHole->m_nSize + ( uint32 ) sizeof( sMMFreeRegion_t ), psFreeHole->m_nSize );
        psFreeHole = psFreeHole->m_psNext;
    }
}

void MemoryManager_AllocInit( sMMAllocator_t *psAllocator, void *pAddress, uint32 nPages ) {

    // Allocate pages as asked for
    psAllocator->m_pHeap = pAddress;
    psAllocator->m_nPages = nPages;
    psAllocator->m_nFreesSinceCoalesce = 0;
    MemoryManager_Page_MapZeroFill( ( uint32 ) pAddress, nPages, MM_FLAGS_KERNEL | MM_FLAGS_READWRITE );

    // Create first empty malloc entry, this is start of linked list
    sMMAlloc_t *psAlloc = psAllocator->m_psAllocHead = ( sMMAlloc_t * ) pAddress;
    psAlloc->m_nSize = 0;
    psAlloc->m_psNext = NULL;

    // Create first heap free map entry, this is start of linked list
    // Allowing space for first free heap entry and first heap allocated entry
    sMMFreeRegion_t *psHeapFreeEntry = psAllocator->m_psFreeHead = ( sMMFreeRegion_t * ) ( ( uint32 ) pAddress + ( uint32 ) sizeof( sMMAlloc_t ) );
    psHeapFreeEntry->m_nSize = ( nPages << MM_PAGESIZESHIFT )
                               - ( uint32 ) sizeof( sMMFreeRegion_t )
                               - ( uint32 ) sizeof( sMMAlloc_t );
    psHeapFreeEntry->m_psNext = NULL;
}

void *MemoryManager_KAlloc ( uint32 nSize ) {
    return MemoryManager_Alloc( nSize, &g_sKernel.m_psAllocator );
}

void *MemoryManager_Alloc( uint32 nSize, sMMAllocator_t *psAllocator ) {

    // How much space do we need? (word boundary)
    uint32 nSizeNeeded = ( ( nSize + sizeof( sMMAlloc_t ) + 3 ) >> 2 ) << 2;

    // Start at beginning of linked list
    sMMFreeRegion_t *psFreeEntry = psAllocator->m_psFreeHead;
    sMMFreeRegion_t *psPrevious = NULL;

    // Loop through linked list until we find a first fit
    while ( psFreeEntry != NULL ) {

        // See if this entry is big enough
        if ( psFreeEntry->m_nSize >= nSizeNeeded ) {

            // Move the free space structure forward ahead of this allocation
            sMMFreeRegion_t * psNewFreeEntry = ( sMMFreeRegion_t * ) ( ( uint32 ) psFreeEntry
                                               + nSizeNeeded );
            psNewFreeEntry->m_nSize = ( uint32 ) psFreeEntry->m_nSize
                                      - ( uint32 ) nSizeNeeded;

            // Update pointers to point to this structure
            if ( psAllocator->m_psFreeHead == psFreeEntry ) {
                psAllocator->m_psFreeHead = psNewFreeEntry;
            } else {
                psPrevious->m_psNext = psNewFreeEntry;
            }
            psNewFreeEntry->m_psNext = psFreeEntry->m_psNext;

            // Convert the original free entry into an allocation and update
            sMMAlloc_t * psAlloc = ( sMMAlloc_t * ) psFreeEntry;
            psAlloc->m_nSize = nSizeNeeded;
            psAlloc->m_psNext = psAllocator->m_psAllocHead;

            // Update allocation struct to point to end of list (i.e. this new alloc)
            psAllocator->m_psAllocHead = psAlloc;

            // Return
            return ( void * ) ( ( uint32 ) psAlloc + ( uint32 ) sizeof( sMMAlloc_t ) );
        }
        // Move onto next free entry (if there is one)
        psPrevious = psFreeEntry;
        psFreeEntry = psFreeEntry->m_psNext;
    }

    KPrint( "MMU", "FATAL: Unable to allocate memory (%lu bytes)- Halting\n", nSizeNeeded );
    halt();
    return 0;
}

void MemoryManager_Coalesce( sMMAllocator_t *psAllocator ) {

    sMMFreeRegion_t * psFree = psAllocator->m_psFreeHead;
    sMMFreeRegion_t *psNextFree = psFree->m_psNext;
    sMMFreeRegion_t *psPreviousFree = NULL;
    while ( psNextFree != NULL ) {
        // Get end of new free space
        sMMFreeRegion_t * psNextFreeEnd = ( sMMFreeRegion_t * ) ( ( uint32 ) psNextFree + ( uint32 ) psNextFree->m_nSize );

        // See if the next one is next to it
        if ( psFree == psNextFreeEnd ) {
            psNextFree->m_nSize += psFree->m_nSize;

            // Is this the first?
            if ( psFree == psAllocator->m_psFreeHead ) {
                psAllocator->m_psFreeHead = psNextFree;
            }

            // Point previous to this new larger one
            if ( psPreviousFree != NULL ) {
                psPreviousFree->m_psNext = psNextFree;
            }

            psFree = psNextFree;
            psNextFree = psFree->m_psNext;
        } else {
            psPreviousFree = psFree;
            psFree = psFree->m_psNext;
            psNextFree = psFree->m_psNext;
        }
    }
}

void MemoryManager_KFree ( void *pAllocation ) {
    MemoryManager_Free( pAllocation, &g_sKernel.m_psAllocator );
}

void MemoryManager_Free( void *pAllocation, sMMAllocator_t *psAllocator ) {

    // Find the linked list entry for this allocation
    sMMAlloc_t * psAllocToFind = ( sMMAlloc_t * ) ( ( uint32 ) pAllocation - ( uint32 ) sizeof( sMMAlloc_t ) );
    sMMAlloc_t *psAlloc = psAllocator->m_psAllocHead;
    sMMAlloc_t *psPrevious = NULL;
    uint32 nDepth = 0;
    while ( psAlloc != psAllocToFind ) {
        if ( psAlloc->m_psNext == 0 )
            break;
        psPrevious = psAlloc;
        psAlloc = psAlloc->m_psNext;
        nDepth++;
    }

    // Did we find an allocation? if not error, return
    if ( psAlloc->m_psNext == NULL ) {
        KPrint( "MMU", "FATAL: Invalid free request for allocation at 0x%X\n", pAllocation );
        halt();
        return ;
    }

    // Now remove allocation
    sMMAlloc_t *psNext = psAlloc->m_psNext;
    if ( psPrevious == NULL ) {
        psAllocator->m_psAllocHead = psNext;
    } else {
        psPrevious->m_psNext = psNext;
    }

    // Convert this allocation into a free entry, making sure the free spaces are kept in the right order
    // So we can do coalescing of free holes
    sMMFreeRegion_t *psNewFree = ( sMMFreeRegion_t * ) psAlloc;
    sMMFreeRegion_t *psFree = psAllocator->m_psFreeHead;
    sMMFreeRegion_t *psPreviousFree = NULL;
    while ( psFree > psNewFree ) {
        psPreviousFree = psFree;
        psFree = psFree->m_psNext;
    }

    // Are we at beginning?
    if ( psFree == NULL ) {
        psNewFree->m_psNext = NULL;
        psPreviousFree->m_psNext = psNewFree;
    } else {
        psNewFree->m_psNext = psPreviousFree->m_psNext;
        psPreviousFree->m_psNext = psNewFree;
    }

    // See if we need to coalesce
    psAllocator->m_nFreesSinceCoalesce++;
    if ( psAllocator->m_nFreesSinceCoalesce > MM_FREESBETWEENCOALESCING ) {
        psAllocator->m_nFreesSinceCoalesce = 0;
        MemoryManager_Coalesce( psAllocator );
    }
}

void *MemoryManager_KExpand ( void *pAllocation, uint32 nAdditionalSize ) {
    return MemoryManager_Expand( pAllocation, nAdditionalSize, &g_sKernel.m_psAllocator );
}

void *MemoryManager_Expand ( void *pAllocation, uint32 nAdditionalSize, sMMAllocator_t *psAllocator ) {
    // This will increase the size of the current allocation
    // It works by creating a new allocation, copying the bytes over and then freeing the
    // old allocation, simple and effiective

    // Find current allocation
    sMMAlloc_t * psAllocToFind = ( sMMAlloc_t * ) ( ( uint32 ) pAllocation - ( uint32 ) sizeof( sMMAlloc_t ) );
    sMMAlloc_t *psAlloc = psAllocator->m_psAllocHead;
    sMMAlloc_t *psPrevious = NULL;
    uint32 nDepth = 0;
    while ( psAlloc != psAllocToFind ) {
        if ( psAlloc->m_psNext == 0 )
            break;
        psPrevious = psAlloc;
        psAlloc = psAlloc->m_psNext;
        nDepth++;
    }

    // Did we find an allocation? if not error, return
    if ( psAlloc->m_psNext == NULL ) {
        KPrint( "MMU", "FATAL: Invalid free request for allocation at 0x%X\n", pAllocation );
        halt();
        return NULL;
    }

    // Now create a new allocation
    uint32 nNewSize = psAlloc->m_nSize + nAdditionalSize;
    void *pCurPtr = ( void * ) ( ( uint32 ) psAlloc + ( uint32 ) sizeof( sMMAlloc_t ) );
    void *pNewPtr = MemoryManager_Alloc( nNewSize, psAllocator );

    // Copy the contents
    memcpy( pNewPtr, pCurPtr, psAlloc->m_nSize );

    // And remove the old allocation
    sMMAlloc_t *psNext = psAlloc->m_psNext;
    if ( psPrevious == NULL ) {
        psAllocator->m_psAllocHead = psNext;
    } else {
        psPrevious->m_psNext = psNext;
    }

    // Convert this allocation into a free entry, making sure the free spaces are kept in the right order
    // So we can do coalescing of free holes
    sMMFreeRegion_t *psNewFree = ( sMMFreeRegion_t * ) psAlloc;
    sMMFreeRegion_t *psFree = psAllocator->m_psFreeHead;
    sMMFreeRegion_t *psPreviousFree = NULL;
    while ( psFree > psNewFree ) {
        psPreviousFree = psFree;
        psFree = psFree->m_psNext;
    }

    // Are we at beginning?
    if ( psFree == NULL ) {
        psNewFree->m_psNext = NULL;
        psPreviousFree->m_psNext = psNewFree;
    } else {
        psNewFree->m_psNext = psPreviousFree->m_psNext;
        psPreviousFree->m_psNext = psNewFree;
    }

    // See if we need to coalesce
    psAllocator->m_nFreesSinceCoalesce++;
    if ( psAllocator->m_nFreesSinceCoalesce > MM_FREESBETWEENCOALESCING ) {
        psAllocator->m_nFreesSinceCoalesce = 0;
        MemoryManager_Coalesce( psAllocator );
    }

    // And return new ptr
    return pNewPtr;
}

void MemoryManager_AllocCall( sCallStack_t *psStack ) {

    // Get parameters
    sCallStack_t * psCallStack = psStack;
    size_t nBytes = ( size_t ) psCallStack->eax;

    // Get allocator struct for current thread & process
    sObject_t *psProcessObject = g_sKernel.m_psRunningProcess;
    sProcess_t * psProcess = ( sProcess_t * ) psProcessObject->m_pData;
    sMMAllocator_t *psAllocator = psProcess->m_psAllocator;

    // Allocate memory
    psCallStack->eax = ( uint32 ) MemoryManager_Alloc( nBytes, psAllocator );
#ifdef VERBOSEDEBUG

    KPrint( "MMU", "Allocation requested %d bytes for allocator 0x%X at 0x%X\n", nBytes, psAllocator, psCallStack->eax );
#endif
}

void MemoryManager_FreeCall( sCallStack_t *psStack ) {

    // Get parameters
    sCallStack_t * psCallStack = psStack;
    void *pAddress = ( void * ) psCallStack->eax;

    // Get allocator struct for current thread & process
    sObject_t *psProcessObject = g_sKernel.m_psRunningProcess;
    sProcess_t * psProcess = ( sProcess_t * ) psProcessObject->m_pData;
    sMMAllocator_t *psAllocator = psProcess->m_psAllocator;

    // Free memory
    MemoryManager_Free( pAddress, psAllocator );
    psCallStack->eax = NULL;
#ifdef VERBOSEDEBUG

    KPrint( "MMU", "Free requested for address 0x%X\n", ( uint32 ) pAddress );
#endif
}

