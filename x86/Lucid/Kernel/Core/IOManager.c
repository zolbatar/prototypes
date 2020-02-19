#include <OSCalls.h>
#include <x86.h>
#include <Core.h>
#include <CI-IO.h>
#include <String.h>

// Prototypes
uint32 IOManager_Handler( uint32 nCall, void *pData );

enum {
    REGISTERIODEVICE
};

void IOManager_Init() {

    // Add volume manager to module list
    ModuleManager_CreateModule( "IOManager", IOManager_Handler );
    ModuleManager_CreateModuleCall( "IOManager", "RegisterIODevice", REGISTERIODEVICE );

    // Calculate no. of pages of memory to use
    uint32 nPagesToUse = K_MM_IOBUFFERPAGES;
    if ( nPagesToUse > Kg_sKernel.m_nMemorySize )
        nPagesToUse = Kg_sKernel.m_nMemorySize;
    if ( nPagesToUse > K_MM_IOBUFFERPAGES )
        nPagesToUse = K_MM_IOBUFFERPAGES;

    // Calculate no. of entries etc
    Kg_sKernel.m_nCacheEntries = nPagesToUse / K_IOC_PAGESPERENTRY;

    // Map as Zero fill memory the cache area
    MemoryManager_Page_MapZeroFill( ( uint32 ) K_MM_IOBUFFERAREA, nPagesToUse, K_MM_FLAGS_KERNEL | K_MM_FLAGS_READWRITE );

    // Allocate some memory on the heap for our cache entry table
    uint32 nEntriesSize = ( Kg_sKernel.m_nCacheEntries * sizeof( K_sIOCache_t ) );
    Kg_sKernel.m_psCacheEntries = MemoryManager_KAlloc( nEntriesSize );

    // And clear all entries
    uint32 i;
    for ( i = 0;i < Kg_sKernel.m_nCacheEntries; i++ ) {
        K_sIOCache_t *psEntry = &Kg_sKernel.m_psCacheEntries[ i ];
        psEntry->m_nFlags = NULL;
    }

    // Debug prompts
    KPrint( KVERBOSE, "IOCACHE", "Cache entry size [%u Kb] \n", K_IOC_ENTRYSIZE );
    KPrint( KVERBOSE, "IOCACHE", "[%u Kb] Space needed for entries\n", ( Kg_sKernel.m_nCacheEntries * sizeof( K_sIOCache_t ) ) >> 10 );
    KPrint( KDEBUG, "IOCACHE", "I/O Cache initialised with [%u entries] [%u Kb]\n", Kg_sKernel.m_nCacheEntries, ( Kg_sKernel.m_nCacheEntries * K_IOC_ENTRYSIZE ) >> 10 );
    KPrint( KDEBUG, "IOMANAGER", "I/O Manager initialised\n" );
}

uint32 IOManager_RegisterIODevice( char *pszName, IOHandler *pHandler ) {

    // Create object
    ObjectManager_Lock();
    K_sObject_t * psObject = ObjectManager_CreateObject( KOBJECT_OBJ_IODEVICE, sizeof( K_sIODevice_t ), pszName );
    K_sIODevice_t *psDevice = ( K_sIODevice_t * ) psObject->m_pData;
    psDevice->m_bRemoveable = false;
    psDevice->m_nBlock = 0;
    psDevice->m_pHandler = pHandler;
    ObjectManager_Unlock();

    KPrint( KVERBOSE, "IOMANAGER", "I/O Device [%s] registered\n", pszName );

    return NULL;
}

uint32 IOManager_RegisterIODeviceCall( KIO_sRegisterIODevice_t *psData ) {
    return IOManager_RegisterIODevice( psData->m_pszName, psData->m_pHandler );
}

uint32 IOManager_RecalculateDevice( K_sIODevice_t *psDevice ) {

    // Reset
    psDevice->m_nBlock = 0;

    // Recalculate block sizes etc.
    psDevice->m_nBlocksPerCacheEntry = K_IOC_ENTRYSIZE / psDevice->m_nBlockSize;

    return NULL;
}

uint32 IOManager_Read( KIO_sRead_t *psData ) {

    K_sFileHandle_t * psHandle = psData->m_psHandle;
    K_sVolume_t *psVolume = psHandle->m_psVolume;
    K_sIODevice_t *psDevice = psVolume->m_psIODevice;

    // Calculate block start
    uint32 nBlock = psHandle->m_nPosition / psDevice->m_nBlockSize;
    uint32 nOffset = psHandle->m_nPosition % psDevice->m_nBlockSize;

    // Loop through reading all bytes in
    uint32 nBytesLeft = psData->m_nBytesNeeded;
    while ( nBytesLeft != 0 ) {

        // Get the length of this block needed
        uint32 nBytesInBlock = psDevice->m_nBlockSize - nOffset;
        if ( nBytesInBlock > nBytesLeft ) {
            nBytesInBlock = nBytesLeft;
        }

        // Check to see if currently needed block is in cache
        if ( IOManager_ReadFromBlock( psDevice, nBlock, nOffset, nBytesInBlock, psData->m_pBuffer ) != NULL ) {
            return KIO_ERRORREADINGBLOCK;
        }

        // Is this a partial block?
        if ( nBytesInBlock != psDevice->m_nBlockSize ) {
            nOffset = 0;
        }

        // Reduce byte count remaining and move file handle pointer along
        nBytesLeft -= nBytesInBlock;
        psHandle->m_nPosition += nBytesInBlock;
    }

    return NULL;
}

uint32 IOManager_Handler( uint32 nCall, void *pData ) {
    switch ( nCall ) {
    case REGISTERIODEVICE:
        return IOManager_RegisterIODeviceCall( ( KIO_sRegisterIODevice_t * ) pData );
    }

    return KMODULE_INVALIDCALL;
}

uint32 IOManager_MapCacheDirectPage( K_sIODevice_t *psIODevice, uint32 nPhysicalAddr, uint32 nPage ) {

    // Find an empty unmapped page first
    uint32 i;
    for ( i = 0;i < Kg_sKernel.m_nCacheEntries; i++ ) {
        K_sIOCache_t *psEntry = &Kg_sKernel.m_psCacheEntries[ i ];

        // If entry unused, check if page table entry present
        if ( ( psEntry->m_nFlags & K_IOCACHE_INUSE ) == NULL ) {

            // Calculate I/O buffer virtual address
            uint32 nVirtualAddr = K_MM_IOBUFFERAREA + ( i << K_MM_PAGESIZESHIFT );

            // Check if present, if not we can use it
            uint32 nFlags = MemoryManager_GetPTValue( nVirtualAddr );
            if ( ( nFlags & K_MM_PTEFLAGS_PRESENT ) == NULL ) {

                // Allocate now
                MemoryManager_Page_Map( nPhysicalAddr, nVirtualAddr, 1, K_MM_FLAGS_KERNEL | K_MM_FLAGS_READWRITE );

                // Set flags
                psEntry->m_psIODevice = psIODevice;
                psEntry->m_nStartBlock = nPage;
                psEntry->m_nAge = 0;
                psEntry->m_nFlags = K_IOCACHE_INUSE | K_IOCACHE_LOCKED | K_IOCACHE_DIRECTMAPPED;

                // And return
                return nVirtualAddr;
            }
        }
    }

    // Can't allocate
    KPrint( KSEVERE, "IOCACHE", "Can't direct map page [0x%X] into I/O Cache\n", nPhysicalAddr );
    return NULL;
}

uint32 IOManager_ReadFromBlock( K_sIODevice_t *psIODevice, uint32 nBlock, uint32 nOffset, uint32 nBytesNeeded, void *pBuffer ) {

    // Round block to cache size
    uint32 nStartBlockNeeded = nBlock / psIODevice->m_nBlocksPerCacheEntry;

    // See if this block is in the cache
    uint32 i;
    for ( i = 0;i < Kg_sKernel.m_nCacheEntries; i++ ) {
        K_sIOCache_t *psEntry = &Kg_sKernel.m_psCacheEntries[ i ];

        // Is this the block we are looking for?
        if ( psEntry->m_psIODevice == psIODevice && psEntry->m_nStartBlock == nStartBlockNeeded ) {

            // Calculate I/O cache entry virtual address
            uint32 nVirtualAddr = K_MM_IOBUFFERAREA + ( i << K_MM_PAGESIZESHIFT );
            nVirtualAddr += ( nBlock % psIODevice->m_nBlocksPerCacheEntry ) * psIODevice->m_nBlockSize;
            nVirtualAddr += nOffset;

            // We have found a cache entry, so now copy the data
            memcpy( pBuffer, ( void * ) nVirtualAddr, nBytesNeeded );

            // Set entry as used
            psEntry->m_nFlags &= ~K_IOCACHE_WAITINGFORUSE;

            // And return success
            return NULL;

        }
    }

    // Block not in cache, we need to an I/O request to drag it into the cache
    KPrint( KSEVERE, "IOCACHE", "Block not in cache [%u]\n", nStartBlockNeeded );
    halt();

    // Call device specific read function
    /*    KIO_sRead_t sRead;
        sRead->m_psVolume = psVolume;
        sRead->m_pBuffer = pBuffer;
        sRead->m_nBytesNeeded = nBytesNeeded;
        sRead->m_nBytesRead = nBytesRead;
        K_sIODevice_t *psDevice = psVolume->K_sIODevice_t;
        return psDevice->m_pHandler( KIO_READ, &sRead );*/

    return KIO_ERRORREADINGBLOCK;
}

