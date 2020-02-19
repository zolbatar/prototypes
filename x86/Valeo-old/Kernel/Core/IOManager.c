#include <Kernel.h>

// Lock
sLock_t sIOLock;

void IOManager_LockInit() {
    Lock_Init( "IOMANAGER", &sIOLock );
}

void IOManager_Lock() {
    Lock_Lock( &sIOLock );
}

void IOManager_Unlock() {
    Lock_Unlock( &sIOLock );
}

void IOManager_Init() {

    // Initialise locking
    IOManager_LockInit();

    // Calculate no. of pages of memory to use (upto half of memory or 768MB whichever is lower)
    uint32 nPagesToUse = MM_IOBUFFERPAGES;
    if ( nPagesToUse > ( g_sKernel.m_nMemorySize / 2 ) )
        nPagesToUse = g_sKernel.m_nMemorySize / 2;

    // Calculate no. of entries etc
    g_sKernel.m_nCacheEntries = nPagesToUse / IOM_PAGESPERENTRY;

    // Map as Zero fill memory the cache area
    MemoryManager_Page_MapZeroFill( ( uint32 ) MM_IOBUFFERAREA, nPagesToUse, MM_FLAGS_KERNEL | MM_FLAGS_READWRITE );

    // Allocate some memory on the heap for our cache entry table
    uint32 nEntriesSize = ( g_sKernel.m_nCacheEntries * sizeof( sIOCache_t ) );
    g_sKernel.m_psCacheEntries = MemoryManager_KAlloc( nEntriesSize );

    // And clear all entries
    uint32 i;
    for ( i = 0;i < g_sKernel.m_nCacheEntries; i++ ) {
        sIOCache_t *psEntry = &g_sKernel.m_psCacheEntries[ i ];
        psEntry->m_nFlags = NULL;
    }

    // Debug prompts
    KPrint( "IOCACHE", "Cache entry size [%u Kb] \n", IOM_ENTRYSIZE );
    KPrint( "IOCACHE", "[%u Kb] Space needed for entries\n", ( g_sKernel.m_nCacheEntries * sizeof( sIOCache_t ) ) >> 10 );
    KPrint( "IOCACHE", "I/O Cache initialised with [%u entries] [%u Kb]\n", g_sKernel.m_nCacheEntries, ( g_sKernel.m_nCacheEntries * IOM_ENTRYSIZE ) >> 10 );
    KPrint( "IOMANAGER", "I/O Manager initialised\n" );
}

KStatus IOManager_RegisterIODevice( char *pszName, IORegisterCallBack *pCallback ) {

    // Construct object path and key
    ObjectManager_Lock();
    ObjectManager_ConstructPath( "/System/IOManager/Devices/" );
    ObjectManager_ConstructKey( pszName );

    // Create object
    IOManager_Lock();
    sObject_t * psObject = ObjectManager_CreateObject( OM_IODEVICE, sizeof( sIODevice_t ) );
    sIODevice_t *psDevice = ( sIODevice_t * ) psObject->m_pData;
    psDevice->m_bRemoveable = false;
    psDevice->m_nBlock = 0;
    psDevice->m_pMountCall = NULL;

    // Call callback function for I/O device to initialise calls etc.
    pCallback( psDevice );

    IOManager_Unlock();
    ObjectManager_Unlock();
#ifdef DEBUG

    KPrint( "IOMANAGER", "I/O Device [%s] registered\n", pszName );
#endif

    return NULL;
}

KStatus IOManager_RecalculateDevice( sIODevice_t *psDevice ) {

    // Setup parameters
    IOManager_Lock();
    psDevice->m_nBlock = 0;
    psDevice->m_nBlocksPerCacheEntry = IOM_ENTRYSIZE / psDevice->m_nBlockSize;
    IOManager_Unlock();

    return NULL;
}

KStatus IOManager_ReadFromBlock( sIODevice_t *psIODevice, uint32 nBlock, uint32 nOffset, uint32 nBytesNeeded, void *pBuffer ) {

    // Round block to cache size
    uint32 nStartBlockNeeded = nBlock / psIODevice->m_nBlocksPerCacheEntry;

    // See if this block is in the cache
    uint32 i;
    for ( i = 0;i < g_sKernel.m_nCacheEntries; i++ ) {
        sIOCache_t *psEntry = &g_sKernel.m_psCacheEntries[ i ];

        // Is this the block we are looking for?
        if ( psEntry->m_psIODevice == psIODevice && psEntry->m_nStartBlock == nStartBlockNeeded ) {

            // Calculate I/O cache entry virtual address
            uint32 nVirtualAddr = MM_IOBUFFERAREA + ( i << MM_PAGESIZESHIFT );
            nVirtualAddr += ( nBlock % psIODevice->m_nBlocksPerCacheEntry ) * psIODevice->m_nBlockSize;
            nVirtualAddr += nOffset;

            // We have found a cache entry, so now copy the data
            memcpy( pBuffer, ( void * ) nVirtualAddr, nBytesNeeded );

            // Set entry as used
            psEntry->m_nFlags &= ~IOM_IOCACHE_WAITINGFORUSE;

            // And return success
            return NULL;

        }
    }

    // Block not in cache, we need to an I/O request to drag it into the cache
    KPrint( "IOCACHE", "Block not in cache [%u]\n", nStartBlockNeeded );
    halt();

    // Call device specific read function
    /*    KIO_sRead_t sRead;
        sRead->m_psVolume = psVolume;
        sRead->m_pBuffer = pBuffer;
        sRead->m_nBytesNeeded = nBytesNeeded;
        sRead->m_nBytesRead = nBytesRead;
        sIODevice_t *psDevice = psVolume->sIODevice_t;
        return psDevice->m_pHandler( KIO_READ, &sRead );*/

    return IOM_ERRORREADINGBLOCK;
}

KStatus IOManager_Read( sFileHandle_t *psHandle, void *pBuffer, uint32 nBytesNeeded, uint32 *nBytesRead ) {

    IOManager_Lock();

    sVolume_t * psVolume = psHandle->m_psVolume;
    sIODevice_t *psDevice = psVolume->m_psIODevice;

    // Set start of destination buffer
    void *pDestBuffer = pBuffer;

    // Loop through reading all bytes in
    uint32 nBytesLeft = nBytesNeeded;
    while ( nBytesLeft != 0 ) {

        // Calculate block start
        uint32 nBlock = psHandle->m_nPosition / psDevice->m_nBlockSize;
        uint32 nOffset = psHandle->m_nPosition % psDevice->m_nBlockSize;

        // Get the length of this block needed
        uint32 nBytesInBlock = psDevice->m_nBlockSize - nOffset;
        if ( nBytesInBlock > nBytesLeft ) {
            nBytesInBlock = nBytesLeft;
        }

        // Check to see if currently needed block is in cache
        if ( IOManager_ReadFromBlock( psDevice, nBlock, nOffset, nBytesInBlock, pDestBuffer ) != NULL ) {
            IOManager_Unlock();
            return IOM_ERRORREADINGBLOCK;
        }

        // Reduce byte count remaining and move file handle pointer along
        nBytesLeft -= nBytesInBlock;
        pDestBuffer += nBytesInBlock;
        *nBytesRead += nBytesInBlock;
        psHandle->m_nPosition += nBytesInBlock;
    }

    IOManager_Unlock();
    return NULL;
}

KStatus IOManager_MapCacheDirectPage( sIODevice_t *psIODevice, uint32 nPhysicalAddr, uint32 nPage ) {

    // Find an empty unmapped page first
    IOManager_Lock();
    uint32 i;
    for ( i = 0;i < g_sKernel.m_nCacheEntries; i++ ) {
        sIOCache_t *psEntry = &g_sKernel.m_psCacheEntries[ i ];

        // If entry unused, check if page table entry present
        if ( ( psEntry->m_nFlags & IOM_IOCACHE_INUSE ) == NULL ) {

            // Calculate I/O buffer virtual address
            uint32 nVirtualAddr = MM_IOBUFFERAREA + ( i << MM_PAGESIZESHIFT );

            // Check if present, if not we can use it
            uint32 nFlags = MemoryManager_GetPTValue( nVirtualAddr );
            if ( ( nFlags & MM_PTEFLAGS_PRESENT ) == NULL ) {

                // Allocate now
                MemoryManager_Page_Map( nPhysicalAddr, nVirtualAddr, 1, MM_FLAGS_KERNEL | MM_FLAGS_READWRITE );

                // Set flags
                psEntry->m_psIODevice = psIODevice;
                psEntry->m_nStartBlock = nPage;
                psEntry->m_nAge = 0;
                psEntry->m_nFlags = IOM_IOCACHE_INUSE | IOM_IOCACHE_LOCKED | IOM_IOCACHE_DIRECTMAPPED;

                // And return
                IOManager_Unlock();
                return nVirtualAddr;
            }
        }
    }

    // Can't map
    IOManager_Unlock();
    KPrint( "IOCACHE", "Can't direct map page [0x%X] into I/O Cache\n", nPhysicalAddr );
    return NULL;
}

KStatus IOManager_UnmapCacheDirectPage( sIODevice_t *psIODevice, uint32 nPage ) {

    // Search all entries for this page
    IOManager_Lock();
    uint32 i;
    for ( i = 0;i < g_sKernel.m_nCacheEntries; i++ ) {
        sIOCache_t *psEntry = &g_sKernel.m_psCacheEntries[ i ];

        // If entry used, check if for our device
        if ( ( psEntry->m_psIODevice == psIODevice && psEntry->m_nStartBlock == nPage ) ) {

            // Calculate I/O buffer virtual address for this page
            uint32 nVirtualAddr = MM_IOBUFFERAREA + ( i << MM_PAGESIZESHIFT );

            // Unmap page
            MemoryManager_Page_Unmap( nVirtualAddr, 1 );

            // Clear flags
            psEntry->m_psIODevice = NULL;
            psEntry->m_nFlags = NULL;

            // And return
            IOManager_Unlock();
            return nVirtualAddr;
        }
    }

    // Can't find to unmap
    IOManager_Unlock();
    KPrint( "IOCACHE", "Can't unmap page [0x%X] from I/O Cache\n", nPage );
    return NULL;
}

