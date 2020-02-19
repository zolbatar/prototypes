#include <Kernel.h>

// DMM is direct memory map file I/O, using for loading GRUB modules
// works by accessing pages of memory as if they were files, simple but effective
void DMMFileIO_Init() {

    // Register this as a block I/O device
    IOManager_RegisterIODevice( "DMMBlockIO", &DMMFileIO_RegisterIOCallback );

    // Register this as a filesystem as well (because this code handles both)
    FS_RegisterFilesystem( "DMMFS", &DMMFileIO_RegisterFilesystemCallback );

    KPrint( "DMM I/O", "DMM I/O initialised\n" );
}

KStatus DMMFileIO_RegisterIOCallback( sIODevice_t *psIODevice ) {

    // Set block dimension
    psIODevice->m_nBlockSize = 4096;

    // Set calls
    psIODevice->m_pMountCall = &DMMFileIO_Mount;
    psIODevice->m_pDismountCall = &DMMFileIO_Dismount;

    return NULL;
}

KStatus DMMFileIO_RegisterFilesystemCallback( sFilesystem_t *psFilesystem ) {

    // Set calls
    psFilesystem->m_pOpenCall = &DMMFileIO_Open;
    psFilesystem->m_pReadCall = &DMMFileIO_Read;

    return NULL;
}

KStatus DMMFileIO_Mount( sIODevice_t *psIODevice, char *pszData ) {

    // Get address and page count
    uint32 nAddress, nPageCount;
    sscanf( pszData, "%X/%X", &nAddress, &nPageCount );

    // Direct map pages into I/O cache
    uint32 i;
    for ( i = 0;i < nPageCount; i++ ) {
        IOManager_MapCacheDirectPage( psIODevice, nAddress, i );
        nAddress += MM_PAGESIZE;
    }
    psIODevice->m_nTotalBlocks = nPageCount;

    return NULL;
}

KStatus DMMFileIO_Dismount( sIODevice_t *psIODevice ) {

    // Unmap pages into I/O cache
    uint32 i;
    for ( i = 0;i < psIODevice->m_nTotalBlocks; i++ ) {
        IOManager_UnmapCacheDirectPage( psIODevice, i );
    }

    return NULL;
}

KStatus DMMFileIO_Open( sVolume_t *psVolume, char *pszVolume, char *pszPath, char *pszFilename, sFileHandle_t *psFileHandle ) {

    // In the DMMFS, it doesnt matter what the filename is because all the work is done
    // through mounting physical memory pages into the I/O cache
    return NULL;
}

KStatus DMMFileIO_Read( sFileHandle_t *psHandle, void *pBuffer, uint32 nBytesNeeded, uint32 *nBytesRead ) {

    // Put a call into the I/O manager to request bytes
    // We don't need anything more complex as this because there is no
    // file structure as such
    return IOManager_Read( psHandle, pBuffer, nBytesNeeded, nBytesRead );
}



