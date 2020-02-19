#include <Kernel.h>

extern uint32 *CorePageTable;
extern uint32 *ZeroPageTable;

// Initial kernel process page struct
sProcessPages_t g_sKernelProcessPageStruct;
uint32 g_nKernelPTEs[ MM_KERNELPTEs ];

/* Note: Memory Structure
0x80000000 = Kernel
           > Page Directory
           > Page Table for Page Table Mapping
           > Free page stack
           = Module area (Upto 0x8FBFFFFF)
0x8FC00000 = Page Table Mapping
0x90000000 = Kernel Data Area (Upto 0xEFFFFFFF)
0xF0000000 = Physical memory map area (for drivers) (Upto 0xFFFFFFFF)
	     Also used as a temporary scratch area during module load
*/

// Lock
sLock_t l_sMemoryLock;

void MM_LockInit() {
    Lock_Init( &l_sMemoryLock );
}

void MM_Lock() {
    Lock_Lock( &l_sMemoryLock );
}

void MM_Unlock() {
    Lock_Unlock( &l_sMemoryLock );
}

void MM_Init( sMBInfo_t *psMBInfo ) {

    // See if there is a multiboot structure, if not error
    if ( !( ( psMBInfo->m_nFlags ) & ( 1 << 6 ) ) ) {
        Syslog_Lock();
        Syslog_Entry( "MM", "FATAL: No multiboot memory map information available - Halting\n" );
        Syslog_Unlock();
        halt();
    }

    // Initialise locking
    MM_LockInit();

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

            // Get RAM region
            uint32 nAddr = ( sMMap->m_nBaseAddrHigh * 256 ) + sMMap->m_nBaseAddrLow;
            nAddr = MM_PAGEALIGN( nAddr + ( MM_PAGESIZE - 1 ) );
            uint32 nLen = ( ( sMMap->m_nLengthHigh * 256 ) + sMMap->m_nLengthLow ) >> MM_PAGESIZESHIFT;
            nPages += nLen;
            Syslog_Lock();
            Syslog_Entry( "MM", "RAM at 0x%X, %lu Pages\n", nAddr, nLen );
            Syslog_Unlock();

        }
        sMMap = ( sMBMemoryMap_t * ) ( ( uint32 ) sMMap + ( sMMap->m_nSize + ( uint32 ) sizeof ( sMMap->m_nSize ) ) );
    }
    g_sKernel.m_nMemorySizePages = nPages;
    g_sKernel.m_nMemorySizeKB = nPages << 2;
    Syslog_Lock();
    Syslog_Entry( "MM", "Size of memory is %lu Kbytes, %lu Pages\n", g_sKernel.m_nMemorySizeKB, g_sKernel.m_nMemorySizePages );
    Syslog_Unlock();

    // Align free page stack to page boundary
    nPages = ( ( nPages * sizeof( sFreePageStack_t ) ) + ( MM_PAGESIZE - 1 ) ) >> MM_PAGESIZESHIFT;
    Syslog_Lock();
    Syslog_Entry( "MM", "Size of free page stack is %lu Pages\n", nPages );
    Syslog_Unlock();

    // Allocate space for free space table, put it straight after kernel
    g_sKernel.m_psFreePageStack = ( sFreePageStack_t * ) g_sKernel.m_nKernelEnd;
    uint32 nFreePageStackPhysical = 0x200000 + ( ( MM_KERNELSTACK + 2 ) << MM_PAGESIZESHIFT );
    uint32 nFreePageStackPhysicalEnd = nFreePageStackPhysical + ( nPages << MM_PAGESIZESHIFT );
    MM_Lock();
    MM_Page_Map( nFreePageStackPhysical, ( uint32 ) g_sKernel.m_psFreePageStack, nPages, MM_FLAGS_KERNEL | MM_FLAGS_READWRITE );
    MM_Unlock();
    g_sKernel.m_nKernelEnd += nPages << MM_PAGESIZESHIFT;

    // Now actually store address of each free page in the free page stack
    g_sKernel.m_nFreePageStackIndex = 0;
    sMMap = ( sMBMemoryMap_t * ) psMBInfo->m_nMMAPAddr;
    for ( i = 0; i < nNumsMMapEntries; i++ ) {

        // Make sure its a type 0x1, i.e. RAM
        if ( sMMap->m_nType == ( uint32 ) 0x1 ) {

            // Get address and length of RAM region (length is rounded to pages)
            uint32 nAddr = ( sMMap->m_nBaseAddrHigh * 256 ) + sMMap->m_nBaseAddrLow;
            nAddr = MM_PAGEALIGN( nAddr + ( MM_PAGESIZE - 1 ) );
            uint32 nLen = ( ( sMMap->m_nLengthHigh * 256 ) + sMMap->m_nLengthLow ) >> MM_PAGESIZESHIFT;

            // Add these pages to the stack
            uint32 j;
            for ( j = 0; j < nLen; j++ ) {

                if ( ( nAddr >= 0x100000 ) && ( nAddr < ( 0x100000 + ( g_sKernel.m_nKernelSize << MM_PAGESIZESHIFT ) ) ) ) {
                    // Kernel space, ignore
                } else if ( ( nAddr >= ( uint32 ) g_sKernel.m_pBootModuleStart ) && ( nAddr < ( uint32 ) g_sKernel.m_pBootModuleEnd ) ) {
                    // Boot module space, ignore
                } else if ( ( nAddr >= 0x200000 ) && ( nAddr < nFreePageStackPhysicalEnd ) ) {
                    // Stack space and page table/page directory, ignore
                } else {
                    sFreePageStack_t * psFreePageEntry = &g_sKernel.m_psFreePageStack[ g_sKernel.m_nFreePageStackIndex++ ];
                    psFreePageEntry->m_nPhysicalAddr = nAddr;
                }

                // Move to next page
                nAddr += MM_PAGESIZE;
            }
        }
        sMMap = ( sMBMemoryMap_t * ) ( ( unsigned long ) sMMap + ( sMMap->m_nSize + sizeof ( sMMap->m_nSize ) ) );
    }

    // Drop down to point to first free entry
    g_sKernel.m_nFreePageStackIndex--;

    // Set this as the current process page struct and initialise
    g_sKernel.m_psKernelProcessPages = &g_sKernelProcessPageStruct;
    MM_ZeroPageStruct( g_sKernel.m_psKernelProcessPages );

    // Create kernel PTEs space
    g_sKernel.m_pnKernelPTEs = ( uint32 * ) & g_nKernelPTEs;
    for ( i = 0 ; i < MM_KERNELPTEs; i++ ) {
        g_sKernel.m_pnKernelPTEs[ i ] = MM_NOPTEENTRY;
    }

    // Add kernel onto kernel process pages
    for ( i = 0; i < g_sKernel.m_nKernelSize ; i++ ) {
        MM_AddPage( MM_KERNELADDRPAGED + ( i << MM_PAGESIZESHIFT ), 0x100000 + ( i << MM_PAGESIZESHIFT ) );
    }
    uint32 nPagesSoFar = g_sKernel.m_nKernelSize;

    // Add page directory
    MM_AddPage( MM_KERNELADDRPAGED + ( g_sKernel.m_nKernelSize << MM_PAGESIZESHIFT ), 0x200000 );

    // Add 0x80000000 PTE
    MM_AddPage( MM_PAGETABLES + ( 0x80000000 >> 10 ), 0x201000 );

    // Add kernel stack
    for ( i = 0; i < MM_KERNELSTACK ; i++ ) {
        MM_AddPage( ( uint32 ) g_sKernel.m_psFreePageStack + ( i << MM_PAGESIZESHIFT ), 0x203000 + ( i << MM_PAGESIZESHIFT ) );
    }
    nPagesSoFar += MM_KERNELSTACK;

    // Add free page stack pages themselves
    for ( i = 0; i < nPages ; i++ ) {
        MM_AddPage( MM_KERNELADDRPAGED + ( ( 1 + i + g_sKernel.m_nKernelSize ) << MM_PAGESIZESHIFT ), 0x200000 + ( ( MM_KERNELSTACK + 3 + i ) << MM_PAGESIZESHIFT ) );
    }
    nPagesSoFar += nPages;

    // Add in boot module space used
    uint32 nBootModulePages = ( g_sKernel.m_pBootModuleEnd - g_sKernel.m_pBootModuleStart ) >> MM_PAGESIZESHIFT;
    for ( i = 0; i < nBootModulePages ; i++ ) {
        MM_AddPage( MM_PAGENOTMAPPED, ( uint32 ) g_sKernel.m_pBootModuleStart + ( i << MM_PAGESIZESHIFT ) );
    }
    nPagesSoFar += nBootModulePages;

    // Setup memory allocator
    g_sKernel.m_nDataAreaPages = MM_KERNELDATAPAGES;
    MM_Lock();
    MM_AllocInit( &g_sKernel.m_psAllocator, ( void * ) MM_KERNELDATA, g_sKernel.m_nDataAreaPages );
    MM_Unlock();
    Syslog_Lock();
    Syslog_Entry( "MM", "Kernel data area of %lu KBytes created at 0x%X\n", ( g_sKernel.m_nDataAreaPages << MM_PAGESIZESHIFT ) / 1024, MM_KERNELDATA );
    Syslog_Unlock();

    // Set start of module area (used for boot modules also) and map as zero-fill
    g_sKernel.m_pModuleArea = g_sKernel.m_nKernelEnd;
    uint32 nModuleAreaPagesMax = ( ( uint32 ) MM_MODULEAREATOP - ( uint32 ) g_sKernel.m_pModuleArea ) >> MM_PAGESIZESHIFT;
    uint32 nModuleAreaPages = nModuleAreaPagesMax;
    Syslog_Lock();
    Syslog_Entry( "MM", "Module area of %lu KBytes created at 0x%X\n", ( nModuleAreaPages << MM_PAGESIZESHIFT ) / 1024, g_sKernel.m_pModuleArea );
    Syslog_Unlock();

    // Set start of physical memory map area (for drivers etc)
    g_sKernel.m_pPhysicalMemMapArea = ( void * ) MM_PHYSICALMEMMAPAREA;
    Syslog_Lock();
    Syslog_Entry( "MM", "Memory map area of %lu KBytes created at 0x%X\n", ( MM_PHYSICALMEMMAPPAGES << MM_PAGESIZESHIFT ) / 1024 , g_sKernel.m_pPhysicalMemMapArea );
    Syslog_Unlock();

    // Do we need to do any post-mm video setup (i.e. remapping logical/physical memory?)
    TextModeVideo_PostMMInit();

    // Unmap identity-mapped lower 4MB of memory
    MM_Page_Unmap( 0, 1024 );

    // Free up zero PTE (we don't need it any more)
    g_sKernel.m_pnPageDirectory[ 0 ] = 0;

    // And finally reload CR3, to make sure it's all tidy and clean.
    ReloadCR3();
}

void MM_CreateObjects() {

    Object_Lock();

    // Create memory manager object path
    g_sKernel.m_psSystemMemoryManager = Object_CreateDirectory( g_sKernel.m_psSystemRoot, "Memory Manager" );

    // And create objects
    Object_CreateObjectWord( g_sKernel.m_psSystemMemoryManager, "Memory Size (Pages)", &g_sKernel.m_nMemorySizePages );
    Object_CreateObjectWord( g_sKernel.m_psSystemMemoryManager, "Memory Size (KB)", &g_sKernel.m_nMemorySizeKB );

    Object_Unlock();
}

void MM_ZeroPageStruct( sProcessPages_t *psProcessPages ) {

    // Zero used map
    psProcessPages->m_nMap = 0;

    // Zero all entries
    memset ( ( void * ) & psProcessPages->m_nPhysicalAddr, 0, sizeof( psProcessPages->m_nPhysicalAddr ) );
    memset ( ( void * ) & psProcessPages->m_nVirtualAddr, 0, sizeof( psProcessPages->m_nVirtualAddr ) );
}

void MM_AddPageToPageStruct( sProcessPages_t *psProcessPages, uint32 nVirtualAddr, uint32 nPhysicalAddr ) {

    // Find an empty struct
    bool bFound = false;
    while ( !bFound ) {

        // If full, create another one
        if ( psProcessPages->m_nMap == MM_PROCESSPAGESTRUCTFULL ) {

            // Is this valid? If not, create another one, otherwise move to next
            if ( psProcessPages->m_psNext == NULL ) {
                sProcessPages_t * psProcessPagesNew = MM_KAlloc( sizeof( sProcessPages_t ) );
                MM_ZeroPageStruct( psProcessPagesNew );
                psProcessPages->m_psNext = psProcessPagesNew;
            }

            // Move to next
            psProcessPages = psProcessPages->m_psNext;

        } else {
            bFound = true;
        }
    }

    // Now find an empty slot
    uint32 i;
    for ( i = 0; i < MM_ENTRIESPERPROCESSPAGESTRUCT; i++ ) {
        if ( ( psProcessPages->m_nMap & ( 1 << i ) ) == 0 ) {
            psProcessPages->m_nMap ^= ( 1 << i );
            psProcessPages->m_nVirtualAddr[ i ] = nVirtualAddr;
            psProcessPages->m_nPhysicalAddr[ i ] = nPhysicalAddr;
            break;
        }
    }
}

void MM_AddPage( uint32 nVirtualAddr, uint32 nPhysicalAddr ) {

    // What list to process page list add it on
    if ( nVirtualAddr == MM_PAGENOTMAPPED ) {

        // Not mapped into memory
        MM_AddPageToPageStruct( g_sKernel.m_psKernelProcessPages, nVirtualAddr, nPhysicalAddr );

    } else if ( nVirtualAddr >= MM_KERNELADDRPAGED ) {

        if ( nVirtualAddr >= MM_PAGETABLES && nVirtualAddr < MM_PAGETABLESEND ) {

            // Get index of page
            uint32 nIndex = ( nVirtualAddr - MM_PAGETABLES ) >> MM_PAGESIZESHIFT;

            if ( nIndex >= MM_USERPTEs ) {

                // Add to kernel PTEs
                g_sKernel.m_pnKernelPTEs[ nIndex - MM_USERPTEs ] = nPhysicalAddr;

            } else {

                // Add to user-space process PTEs
                Syslog_Entry( "MM", "User PTE @ 0x%X (0x%X) %lu. Halting.\n", nVirtualAddr, nPhysicalAddr, nIndex );
                halt();

            }

        } else {
            MM_AddPageToPageStruct( g_sKernel.m_psKernelProcessPages, nVirtualAddr, nPhysicalAddr );
        }
    } else {
        Syslog_Entry( "MM", "User address space @ 0x%X (0x%X). Halting.\n", nVirtualAddr, nPhysicalAddr );
        halt();
    }
}

#ifdef DEBUG
void MM_DumpProcessPages( sProcessPages_t *psProcessPages ) {

    Object_Lock();
    Syslog_Lock();

    // Loop through and dump all allocated pages to the system log
    do {

        // Loop through all entries
        uint32 i;
        for ( i = 0 ; i < MM_ENTRIESPERPROCESSPAGESTRUCT; i++ ) {
            if ( psProcessPages->m_nMap & ( 1 << i ) ) {
                Syslog_Entry( "MM", "Allocated: 0x%X (0x%X) @ %lu\n", psProcessPages->m_nVirtualAddr[ i ], psProcessPages->m_nPhysicalAddr[ i ], i );
            }

        }

        // Move to next struct
        psProcessPages = psProcessPages->m_psNext;

    } while ( psProcessPages != NULL );

    Syslog_Unlock();
    Object_Unlock();
}

void MM_DumpKernelPTEs() {

    // Loop through all entries
    uint32 i;
    for ( i = 0 ; i < MM_KERNELPTEs; i++ ) {
        if ( g_sKernel.m_pnKernelPTEs[ i ] != MM_NOPTEENTRY ) {

            // Calculate address and display
            uint32 nAddress = MM_KERNELADDRPAGED + ( i << 22 );
            uint32 nPTEAddress = MM_PAGETABLES + ( ( i + MM_USERPTEs ) << 12 );
            Syslog_Entry( "MM", "PTE: 0x%X (0x%X) = 0x%X\n", nAddress, nPTEAddress, g_sKernel.m_pnKernelPTEs[ i ] );

        }
    }
}

#endif

static inline uint32 MM_Page_GetFree( uint32 nVirtualAddr ) {

    if ( g_sKernel.m_nFreePageStackIndex == 0xFFFFFFFF ) {  // 0xFFFFFFFF == -1
        Syslog_Lock();
        Syslog_Entry( "MM", "FATAL: No memory available - Halting\n" );
        Syslog_Unlock();
        halt();
    }

    //  Get physical address of next page of free page stack and return it,
    // updating logical and process id in the process
    sFreePageStack_t *psFreePageEntry = &g_sKernel.m_psFreePageStack[ g_sKernel.m_nFreePageStackIndex-- ];

    // Add to appropriate process page struct
    MM_AddPage( nVirtualAddr, psFreePageEntry->m_nPhysicalAddr );

    return psFreePageEntry->m_nPhysicalAddr;
}

void MM_Page_AddFree( uint32 nPhysicalAddr ) {

    // Add page to free page stack
    sFreePageStack_t * psFreePageEntry = &g_sKernel.m_psFreePageStack[ ++g_sKernel.m_nFreePageStackIndex ];
    psFreePageEntry->m_nPhysicalAddr = nPhysicalAddr;
}

uint32 MM_GetPTValue( uint32 nVirtualAddr ) {

    // Get page table address
    uint32 nPT = MM_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;
    return g_sKernel.m_pnPageTables[ nPT + nPTOffset ];
}

uint32 MM_GetPTAddress( uint32 nVirtualAddr ) {

    // Calculate PDE entry
    uint32 nPDE = nVirtualAddr >> 22;

    // Get page table entry address
    uint32 nPT = g_sKernel.m_pnPageDirectory[ nPDE ];

    // See if we need to create a new page table (2 == supervisor/not present)
    if ( nPT == 2 ) {

        // We need to get a free page to allocate for the page table
        uint32 nPTA = MM_PAGETABLES + ( nVirtualAddr >> 10 );
        uint32 nRealAddr = MM_Page_GetFree( nPTA );

        // And add to page directory
        g_sKernel.m_pnPageDirectory[ nPDE ] = nRealAddr | ( MM_PTEFLAGS_PRESENT | MM_PTEFLAGS_SYSTEM );

        // Zero page table
        memset( ( void * ) ( &g_sKernel.m_pnPageTables[ nPDE << 10 ] ), 0, 4096 );
    }

    return ( nPDE << 22 );
}

void MM_Page_Map( uint32 nPhysicalAddr, uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags ) {

    // Get page table address and offset
    uint32 nPT = MM_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;

    // Loop through and map all pages
    uint32 i;
    for ( i = 0;i < nPageCount; i++ ) {

        // Check we haven't moved to a new page table entry
        if ( nPTOffset == 1024 ) {
            nPT = MM_GetPTAddress ( nVirtualAddr ) >> MM_PAGESIZESHIFT;
            nPTOffset = 0;
        }

        // Set page table entry
        g_sKernel.m_pnPageTables[ nPT + nPTOffset ] = nPhysicalAddr | ( MM_PTEFLAGS_PRESENT | MM_PTEFLAGS_SYSTEM );

        // Move to next page
        nPTOffset++;
        nVirtualAddr += 4096;
        nPhysicalAddr += 4096;

    }

    // Reload CR3
    ReloadCR3( );
}

void MM_Page_Unmap( uint32 nVirtualAddr, uint32 nPageCount ) {

    // Get page table address and offset
    uint32 nPT = MM_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;

    // Loop through and unmap all pages
    uint32 i;
    for ( i = 0;i < nPageCount; i++ ) {

        // Check we haven't moved to a new page table entry
        if ( nPTOffset == 1024 ) {
            nPT = MM_GetPTAddress ( nVirtualAddr ) >> MM_PAGESIZESHIFT;
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

void MM_Page_MapZeroFill( uint32 nVirtualAddr, uint32 nPageCount, uint32 nFlags ) {

    // Get page table address and offset
    uint32 nPT = MM_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;

    // Loop through and zero map all pages
    uint32 i;
    for ( i = 0;i < nPageCount; i++ ) {

        // Check we haven't moved to a new page table entry
        if ( nPTOffset == 1024 ) {
            nPT = MM_GetPTAddress ( nVirtualAddr ) >> MM_PAGESIZESHIFT;
            nPTOffset = 0;
        }

        // Set page table entry
        g_sKernel.m_pnPageTables[ nPT + nPTOffset ] = MM_PAGETYPE_ZEROFILL | MM_PTEFLAGS_SYSTEM;

        // Move to next page
        nPTOffset++;
        nVirtualAddr += 4096;
    }

    // Reload CR3
    ReloadCR3( );
}

void MM_Page_Allocate( uint32 nVirtualAddr, bool bZeroFill ) {

    // Get page table address and offset
    uint32 nPT = MM_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;

    // Set page table entry to point to free physical page
    g_sKernel.m_pnPageTables[ nPT + nPTOffset ] = MM_Page_GetFree( nVirtualAddr ) | ( MM_PTEFLAGS_PRESENT | MM_PTEFLAGS_SYSTEM );

    // Do we need to zero fill?
    if ( bZeroFill == true ) {
        memset( ( void * ) ( nVirtualAddr ) , 0, 4096 );
    }

    // Invalidate TLB entry
    InvalidatePage( ( void * ) ( nVirtualAddr ) );
}

void MM_Page_Free( uint32 nVirtualAddr, uint32 nPageCount ) {

    // Get page table address and offset
    uint32 nPT = MM_GetPTAddress ( nVirtualAddr );
    uint32 nPTOffset = ( nVirtualAddr - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;

    // Loop through and free all zero map pages
    uint32 i;
    for ( i = 0;i < nPageCount; i++ ) {

        // Check we haven't moved to a new page table entry
        if ( nPTOffset == 1024 ) {
            nPT = MM_GetPTAddress ( nVirtualAddr ) >> MM_PAGESIZESHIFT;
            nPTOffset = 0;
        }

        // Is page present? (if not we are not interested)
        if ( g_sKernel.m_pnPageTables[ nPT + nPTOffset ] & MM_PTEFLAGS_PRESENT ) {

            // Add page to free page stack
            uint32 nPhysicalPage = ( g_sKernel.m_pnPageTables[ nPT + nPTOffset ] >> MM_PAGESIZESHIFT ) << MM_PAGESIZESHIFT;
            MM_Page_AddFree( nPhysicalPage );

            // Set page table entry
            g_sKernel.m_pnPageTables[ nPT + nPTOffset ] ^= MM_PTEFLAGS_PRESENT;

        }

        // Move to next page
        nPTOffset++;
        nVirtualAddr += 4096;
    }

    // Reload CR3
    ReloadCR3( );
}

#ifdef DEBUG
void MM_DumpAllocation( sMMAllocator_t *psAllocator ) {

    Syslog_Lock();
    Syslog_Entry( "MM", "Kernel heap - Allocation map\n" );
    sMMAlloc_t * psAlloc = psAllocator->m_psAllocHead;
    while ( psAlloc != NULL ) {
        Syslog_Entry( "MM", "Alloc: 0x%X-0x%X (%lu bytes)\n", ( uint32 ) psAlloc + ( uint32 ) sizeof( sMMAlloc_t ), ( uint32 ) psAlloc + ( uint32 ) psAlloc->m_nSize + ( uint32 ) sizeof( sMMAlloc_t ), psAlloc->m_nSize, psAlloc->m_psNext );
        psAlloc = psAlloc->m_psNext;
    }
    Syslog_Unlock();
}

void MM_KDumpAlloction() {
    MM_DumpAllocation( &g_sKernel.m_psAllocator );
}

void MM_DumpFreeMap( sMMAllocator_t *psAllocator ) {

    Syslog_Lock();
    Syslog_Entry( "MM", "Kernel heap - Free space map\n" );
    sMMFreeRegion_t * psFreeHole = psAllocator->m_psFreeHead;
    while ( psFreeHole != NULL ) {
        Syslog_Entry( "MM", "Free: 0x%X-0x%X (%lu bytes)\n", ( uint32 ) psFreeHole + ( uint32 ) sizeof( sMMFreeRegion_t ), ( uint32 ) psFreeHole + ( uint32 ) psFreeHole->m_nSize + ( uint32 ) sizeof( sMMFreeRegion_t ), psFreeHole->m_nSize );
        psFreeHole = psFreeHole->m_psNext;
    }
    Syslog_Unlock();
}

void MM_KDumpFreeMap( ) {
    MM_DumpFreeMap( &g_sKernel.m_psAllocator );
}
#endif

void MM_AllocInit( sMMAllocator_t *psAllocator, void *pAddress, uint32 nPages ) {

    // Allocate pages as asked for
    psAllocator->m_pHeap = pAddress;
    psAllocator->m_nPages = nPages;
    psAllocator->m_nFreesSinceCoalesce = 0;

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

void *MM_Alloc( uint32 nSize, sMMAllocator_t *psAllocator ) {

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

    Syslog_Lock();
    Syslog_Entry( "MM", "FATAL: Unable to allocate memory (%lu/%lu bytes)- Halting\n", nSize, nSizeNeeded );
    Syslog_Unlock();
    halt();
    return NULL;
}

void *MM_KAlloc ( uint32 nSize ) {
    return MM_Alloc( nSize, &g_sKernel.m_psAllocator );
}

void MM_Coalesce( sMMAllocator_t *psAllocator ) {

    sMMFreeRegion_t * psFree = psAllocator->m_psFreeHead;
    sMMFreeRegion_t *pcNextFree = psFree->m_psNext;
    sMMFreeRegion_t *psPreviousFree = NULL;
    while ( pcNextFree != NULL ) {
        // Get end of new free space
        sMMFreeRegion_t * pcNextFreeEnd = ( sMMFreeRegion_t * ) ( ( uint32 ) pcNextFree + ( uint32 ) pcNextFree->m_nSize );

        // See if the next one is next to it
        if ( psFree == pcNextFreeEnd ) {
            pcNextFree->m_nSize += psFree->m_nSize;

            // Is this the first?
            if ( psFree == psAllocator->m_psFreeHead ) {
                psAllocator->m_psFreeHead = pcNextFree;
            }

            // Point previous to this new larger one
            if ( psPreviousFree != NULL ) {
                psPreviousFree->m_psNext = pcNextFree;
            }

            psFree = pcNextFree;
            pcNextFree = psFree->m_psNext;
        } else {
            psPreviousFree = psFree;
            psFree = psFree->m_psNext;
            pcNextFree = psFree->m_psNext;
        }
    }
}

void MM_KFree ( void *pAllocation ) {
    MM_Free( pAllocation, &g_sKernel.m_psAllocator );
}

void MM_Free( void *pAllocation, sMMAllocator_t *psAllocator ) {

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
        Syslog_Lock();
        Syslog_Entry( "MM", "FATAL: Invalid free request for allocation at 0x%X\n", pAllocation );
        Syslog_Unlock();
        halt();
        return ;
    }

    // Now remove allocation
    sMMAlloc_t *pcNext = psAlloc->m_psNext;
    if ( psPrevious == NULL ) {
        psAllocator->m_psAllocHead = pcNext;
    } else {
        psPrevious->m_psNext = pcNext;
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
        MM_Coalesce( psAllocator );
    }
}

void *MM_KExpand ( void *pAllocation, uint32 nAdditionalSize ) {
    return MM_Expand( pAllocation, nAdditionalSize, &g_sKernel.m_psAllocator );
}

void *MM_Expand ( void *pAllocation, uint32 nAdditionalSize, sMMAllocator_t *psAllocator ) {
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
        Syslog_Lock();
        Syslog_Entry( "MM", "FATAL: Invalid free request for allocation at 0x%X\n", pAllocation );
        Syslog_Unlock();
        halt();
        return NULL;
    }

    // Now create a new allocation
    uint32 nNewSize = psAlloc->m_nSize + nAdditionalSize;
    void *pCurPtr = ( void * ) ( ( uint32 ) psAlloc + ( uint32 ) sizeof( sMMAlloc_t ) );
    void *pNewPtr = MM_Alloc( nNewSize, psAllocator );

    // Copy the contents
    memcpy( pNewPtr, pCurPtr, psAlloc->m_nSize );

    // And remove the old allocation
    sMMAlloc_t *pcNext = psAlloc->m_psNext;
    if ( psPrevious == NULL ) {
        psAllocator->m_psAllocHead = pcNext;
    } else {
        psPrevious->m_psNext = pcNext;
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
        MM_Coalesce( psAllocator );
    }

    // And return new ptr
    return pNewPtr;
}

uint32 MM_GetDataAreaSize_Call( sCallStack_t *psStack ) {
    return g_sKernel.m_nDataAreaPages;
}
