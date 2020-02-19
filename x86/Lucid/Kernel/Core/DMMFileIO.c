#include <Scanf.h>
#include <OSCalls.h>
#include <x86.h>
#include <Core.h>
#include <CI-FS.h>

// Prototypes
uint32 DMMBlockIO_Handler( uint32 nCall, void *pData );
void DMMBlockIO_Worker();
uint32 DMMFileIO_Handler( uint32 nCall, void *pData );

// DMM is direct memory map file I/O, using for loading GRUB modules
// works by accessing pages of memory as if they were files, simple but effective
void DMMFileIO_Init() {

    // Register this as a block I/O device
    IOManager_RegisterIODevice( "DMMBlockIO", DMMBlockIO_Handler );

    // Create I/O worker thread
    ProcessManager_CreateThread( Kg_sKernel.m_psRunningProcess, ( uint32 ) & DMMBlockIO_Worker );

    // Register this as a filesystem as well (because this code handles both)
    FS_RegisterFilesystem( "DMMFS", DMMFileIO_Handler );

    KPrint( KDEBUG, "DMM I/O", "DMM I/O initialised\n" );
}

uint32 DMMFileIO_Mount( KIO_sDDKMount_t *psData ) {

    // Get address and page count
    uint32 nAddress, nPageCount;
    sscanf( psData->m_pszData, "%X/%X", &nAddress, &nPageCount );

    // Direct map pages into I/O cache
    uint32 i;
    for ( i = 0;i < nPageCount; i++ ) {
        IOManager_MapCacheDirectPage( psData->m_psIODevice, nAddress, i );
        nAddress += K_MM_PAGESIZE;
    }

    // Update block I/O
    psData->m_psIODevice->m_nBlockSize = 4096;
    psData->m_psIODevice->m_nTotalBlocks = nPageCount;
    IOManager_RecalculateDevice( psData->m_psIODevice );

    return NULL;
}

uint32 DMMFileIO_OpenCall( KFS_sOpen_t *psData ) {

    // In the DMMFS, it doesnt matter what the filename is because all the work is done
    // through mounting physical memory pages into the I/O cache

    return NULL;
}

uint32 DMMFileIO_Read( K_sFileHandle_t *psHandle, void *pBuffer, uint32 nBytesNeeded, uint32 *nBytesRead ) {

    // Put a call into the I/O manager to request bytes
    // We don't need anything more complex as this because there is no
    // file structure as such
    KIO_sRead_t sRead;
    sRead.m_psHandle = psHandle;
    sRead.m_pBuffer = pBuffer;
    sRead.m_nBytesNeeded = nBytesNeeded;
    sRead.m_nBytesRead = nBytesRead;
    return IOManager_Read( &sRead );
}

uint32 DMMFileIO_ReadCall( KFS_sRead_t *psData ) {
    return DMMFileIO_Read( psData->m_psHandle, psData->m_pBuffer, psData->m_nBytesNeeded, psData->m_nBytesRead );
}

uint32 DMMBlockIO_Handler( uint32 nCall, void *pData ) {
    switch ( nCall ) {
    case KIO_MOUNT:
        return DMMFileIO_Mount( ( KIO_sDDKMount_t * ) pData );
    }
    return KMODULE_INVALIDCALL;
}

uint32 DMMFileIO_Handler( uint32 nCall, void *pData ) {
    switch ( nCall ) {
    case KFS_OPEN:
        return DMMFileIO_OpenCall( ( KFS_sOpen_t * ) pData );
    case KFS_READ:
        return DMMFileIO_ReadCall( ( KFS_sRead_t * ) pData );
    }
    return KMODULE_INVALIDCALL;
}

void DMMBlockIO_Worker() {
    while ( 1 ) {
        asm volatile ( "nop;" );
        //        KProcess_Relinquish();
    }
}


