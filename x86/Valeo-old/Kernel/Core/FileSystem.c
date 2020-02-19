#include <Kernel.h>

// Globals
char *g_pszVolume;
char *g_pszPath;
char *g_pszFilename;

// Lock
sLock_t sFSLock;

void FS_LockInit() {
    Lock_Init( "FILESYSTEM", &sFSLock );
}

void FS_Lock() {
    Lock_Lock( &sFSLock );
}

void FS_Unlock() {
    Lock_Unlock( &sFSLock );
}

void FS_Init() {

    // Init locking
    FS_LockInit();

    // Set kernel variables
    g_sKernel.m_nFileHandleIndex = 0;

    // Space for path portions
    g_pszVolume = ( char * ) MemoryManager_KAlloc( FS_MAXIMUMFULLPATHSIZE );
    g_pszPath = ( char * ) MemoryManager_KAlloc( FS_MAXIMUMFULLPATHSIZE );
    g_pszFilename = ( char * ) MemoryManager_KAlloc( FS_MAXIMUMFULLPATHSIZE );

#ifdef DEBUG

    KPrint( "FS", "File system initialised\n" );
#endif
}

KStatus FS_RegisterFilesystem( char *pszName, FSRegisterCallBack *pCallback ) {

    // Construct object path and key
    ObjectManager_Lock();
    ObjectManager_ConstructPath( "/System/FilesystemManager/Filesystems/" );
    ObjectManager_ConstructKey( pszName );

    // Create object
    sObject_t * psObject = ObjectManager_CreateObject( OM_FILESYSTEM, sizeof( sFilesystem_t ) );
    sFilesystem_t *psFilesystem = ( sFilesystem_t * ) psObject->m_pData;
    psFilesystem->m_pOpenCall = NULL;
    psFilesystem->m_pReadCall = NULL;

    // Call callback function for filesystem to initialise calls etc.
    pCallback( psFilesystem );
    ObjectManager_Unlock();

#ifdef DEBUG

    KPrint( "FS", "Filesystem [%s] registered\n", pszName );
#endif

    return NULL;
}

KStatus FS_Mount( char *pszName, char *pszDevice, char *pszFileSystem, char *pszData ) {

    // Search for block I/O device
    ObjectManager_Lock();
    ObjectManager_ConstructPath( "/System/IOManager/Devices/" );
    ObjectManager_ConstructKey( pszDevice );
    sObject_t *psIODeviceObject = ObjectManager_SearchNameInClass( NULL, OM_IODEVICE );
    if ( psIODeviceObject == NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "FS", "Can't create volume [%s] because I/O device [%s] non-existant\n", pszName, pszDevice );
#endif

        return FS_INVALIDIODEVICE;
    }
    sIODevice_t *psIODevice = ( sIODevice_t * ) psIODeviceObject->m_pData;

    // Search for filesystem
    ObjectManager_ConstructPath( "/System/FilesystemManager/Filesystems//" );
    ObjectManager_ConstructKey( pszFileSystem );
    sObject_t *psFileSystemObject = ObjectManager_SearchNameInClass( NULL, OM_FILESYSTEM );
    if ( psFileSystemObject == NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "FS", "Can't create volume [%s] because filesystem [%s] non-existant\n", pszName, pszFileSystem );
#endif

        return FS_INVALIDFILESYSTEM;
    }
    sFilesystem_t *psFilesystem = ( sFilesystem_t * ) psFileSystemObject->m_pData;

    // Construct object path and key
    ObjectManager_ConstructPath( "/System/FilesystemManager/Volumes/" );
    ObjectManager_ConstructKey( pszName );

    // Create object
    sObject_t * psObject = ObjectManager_CreateObject( OM_VOLUME, sizeof( sVolume_t ) );
    sVolume_t *psVolume = ( sVolume_t * ) psObject->m_pData;
    psVolume->m_psIODevice = psIODevice;
    psVolume->m_psFilesystem = psFilesystem;

    // Increase reference counts of block/filesystem objects so they can't be deleted first
    psIODeviceObject->m_nReferenceCount++;
    psFileSystemObject->m_nReferenceCount++;

    // Call the device driver mount call
    IOMountCall *pMountFunction = ( IOMountCall * ) psIODevice->m_pMountCall;
    KStatus nRet = pMountFunction( psIODevice, pszData );
    if ( nRet != NULL ) {
#ifdef DEBUG
        KPrint( "FS", "Device [%s] failed mount\n", ( char * ) & psIODeviceObject->m_szName );
#endif

        return FS_ERRORMOUNTING;
    }

    // Recalculate
    IOManager_RecalculateDevice( psIODevice );

    ObjectManager_Unlock();
#ifdef VERBOSEDEBUG

    KPrint( "FS", "Successfully mounted volume [%s][%s][%s]\n", pszName, pszDevice, pszFileSystem );
#endif

    return NULL;
}

KStatus FS_Unmount( char *pszName ) {

    // Search for volume
    ObjectManager_Lock();
    ObjectManager_ConstructPath( "/System/FilesystemManager/Volumes/" );
    ObjectManager_ConstructKey( pszName );
    sObject_t *psVolumeObject = ObjectManager_SearchNameInClass( NULL, OM_VOLUME );
    if ( psVolumeObject == NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "FS", "Can't find volume [%s] to unmount\n", pszName );
#endif

        return FS_INVALIDVOLUME;
    }
    sVolume_t *psVolume = ( sVolume_t * ) psVolumeObject->m_pData;
    sIODevice_t *psIODevice = psVolume->m_psIODevice;

    // Do we have any references to this volume?
    if ( psVolumeObject->m_nReferenceCount > 0 ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "FS", "Volume [%s] has %u reference(s)\n", pszName, psVolumeObject->m_nReferenceCount );
#endif

        return FS_HASREFERENCES;
    }
    ObjectManager_Unlock();

    // Call the device driver dismount call
    IODismountCall *pDismountFunction = ( IODismountCall * ) psIODevice->m_pDismountCall;
    KStatus nRet = pDismountFunction( psIODevice );
    if ( nRet != NULL ) {
        ObjectManager_Unlock();
        sObject_t *psIODeviceObject = ObjectManager_GetObjectContainingData( psIODevice );
#ifdef DEBUG

        KPrint( "FS", "Device [%s] failed dismount\n", ( char * ) & psIODeviceObject->m_szName );
#endif

        return FS_ERRORDISMOUNTING;
    }

    // And delete volume
    ObjectManager_Lock();
    ObjectManager_DeleteObject( psVolumeObject );
    ObjectManager_Unlock();

    // And return
#ifdef VERBOSEDEBUG

    KPrint( "FS", "Successfully dismounted volume [%s]\n", pszName );
#endif

    return NULL;
}

bool FS_CheckFilename( uint32 nType, char *pszElement ) {

    uint32 i;
    for ( i = 0;i < strlen( pszElement ); i++ ) {
        uchar c = pszElement[ i ];

        // Handle simple letters/numbers
        if ( c >= 'A' && c <= 'Z' ) {
            continue;
        }
        if ( c >= 'a' && c <= 'z' ) {
            continue;
        }
        if ( c >= '0' && c <= '9' ) {
            continue;
        }

        // Its a symbol, differences between volume/path/filename
        switch ( c ) {
        case '-':
            continue;
        case ':':
            if ( nType == FS_CHECKVOLUME )
                continue;
            else
                return false;
        case '/':
            if ( nType == FS_CHECKPATH )
                continue;
            else
                return false;
        }

        // Not valid
        return false;
    }

    // Valid
    return true;
}

KStatus FS_Parse( char * pszFullPath ) {

    // Clear strings
    g_pszVolume[ 0 ] = '\0';
    g_pszPath[ 0 ] = '\0';
    g_pszFilename[ 0 ] = '\0';

    // Get length of path specificed
    uint32 nLength = strlen( pszFullPath );

    // See if we have a volume specifier
    int32 i;
    for ( i = 0; i < nLength; i++ ) {
        if ( pszFullPath[ i ] == ':' ) {
            break;
        }
    }
    if ( i < nLength ) {
        i++;
        strncpy( g_pszVolume, pszFullPath, i );
        strncpy( g_pszPath , pszFullPath + i, nLength - i );
    } else {
        strncpy( g_pszPath , pszFullPath, nLength );
    }

    // See if there is a final "/" specifier, this should enable us to extract the path and filename
    nLength = strlen( g_pszPath );
    for ( i = nLength ; i >= 0; --i ) {
        if ( g_pszPath[ i ] == '/' ) {
            break;
        }
    }
    if ( i != -1 ) {
        strncpy( g_pszFilename, g_pszPath + i + 1, nLength - i - 1 );
        g_pszPath[ i + 1 ] = '\0';
    }

    // We now have the volume/path/filename, we now do a check to make sure only
    // valid characters have been used in them
    if ( FS_CheckFilename( FS_CHECKVOLUME, g_pszVolume ) != true ) {
        return FS_INVALIDVOLUME;
    }
    if ( FS_CheckFilename( FS_CHECKPATH, g_pszPath ) != true ) {
        return FS_INVALIDPATH;
    }
    if ( FS_CheckFilename( FS_CHECKFILENAME, g_pszFilename ) != true ) {
        return FS_INVALIDPATH;
    }

    // All ok
    return NULL;
}

KStatus FS_Open( char * pszFullPath, uint32 nFlags, uint32 * nHandle ) {

    // We lock, to protect the global string structures
    FS_Lock();

    // Check path is not too long
    if ( strnlen( pszFullPath, FS_MAXIMUMFULLPATHSIZE ) >= FS_MAXIMUMFULLPATHSIZE ) {
        FS_Unlock();
#ifdef DEBUG

        KPrint( "FS", "Path [%s] is too long\n", pszFullPath );
#endif

        return FS_PATHTOOLONG;
    }

    // We need to parse the filename string to extract the volume/path and file
    if ( FS_Parse( pszFullPath ) != NULL ) {
        FS_Unlock();
#ifdef DEBUG

        KPrint( "FS", "Path [%s] is not valid\n", pszFullPath );
#endif

        return FS_INVALIDFULLPATH;
    }

    // Check the volume exists and is valid
    ObjectManager_Lock();
    ObjectManager_ConstructPath( "/System/FilesystemManager/Volumes/" );
    ObjectManager_ConstructKey( g_pszVolume );
    sObject_t * psVolumeObject = ObjectManager_SearchNameInClass( NULL, OM_VOLUME );
    if ( psVolumeObject == NULL ) {
        FS_Unlock();
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "FS", "Volume [%s] not found\n", g_pszVolume );
#endif

        return FS_INVALIDVOLUME;
    }
    sVolume_t *psVolume = ( sVolume_t * ) psVolumeObject->m_pData;

    // Increase reference count on volume
    psVolumeObject->m_nReferenceCount++;

    // Construct object path and key
    ObjectManager_ConstructPath( "/System/FilesystemManager/Handles" );
    char szHandle[ 256 ] = "";
    snprintf( ( char * ) szHandle, 256, "Handle %u", g_sKernel.m_nFileHandleIndex );
    ObjectManager_ConstructKey( ( char * ) & szHandle );

    // Create a file handle (we will delete this if the file can not be opened)
    sObject_t * psFileHandleObject = ObjectManager_CreateObject( OM_FILEHANDLE, sizeof( sFileHandle_t ) );
    psFileHandleObject->m_nTypeIndex = g_sKernel.m_nFileHandleIndex++;
    sFileHandle_t *psFileHandle = ( sFileHandle_t * ) psFileHandleObject->m_pData;
    psFileHandle->m_psVolume = psVolume;
    psFileHandle->m_nPosition = 0;
    ObjectManager_Unlock();

    // Call the file system open call
    sFilesystem_t *psFilesystem = psVolume->m_psFilesystem;
    FSOpenCall *pOpenFunction = ( FSOpenCall * ) psFilesystem->m_pOpenCall;
    KStatus nRet = pOpenFunction( psVolume, g_pszVolume, g_pszPath, g_pszFilename, psFileHandle );
    if ( nRet != NULL ) {
        FS_Unlock();
        ObjectManager_Lock();
        ObjectManager_DeleteObject( psFileHandleObject );
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "FS", "Open failed on file [%s]\n", pszFullPath );
#endif

        return FS_ERROROPENINGFILE;
    }

    // Return handle
    FS_Unlock();
    *nHandle = psFileHandleObject->m_nTypeIndex;
    return NULL;
}

KStatus FS_Close( uint32 nHandle ) {

    // Check the volume exists and is valid
    ObjectManager_Lock();
    sObject_t * psFileHandleObject = ObjectManager_SearchInClassTypeIndex( NULL, OM_FILEHANDLE, nHandle );
    if ( psFileHandleObject == NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "FS", "Handle [%u] not found\n", nHandle );
#endif

        return FS_INVALIDHANDLE;
    }
    sFileHandle_t *psHandle = ( sFileHandle_t * ) psFileHandleObject->m_pData;

    // Get volume struct and reduce reference count
    sObject_t *psVolumeObject = ObjectManager_GetObjectContainingData( psHandle->m_psVolume );
    psVolumeObject->m_nReferenceCount--;

    // Now delete handle
    ObjectManager_DeleteObject( psFileHandleObject );
    ObjectManager_Unlock();

    return NULL;
}

KStatus FS_Read( uint32 nHandle, void *pBuffer, uint32 nBytes, uint32 *nBytesRead ) {

    // Clear bytes read
    *nBytesRead = 0;

    // First off, lets find the object relating to this handle, I know this will end up being
    // **really** slow, but it will do for now until I can be bothered to optimise it
    ObjectManager_Lock();
    sObject_t *psObject = ObjectManager_SearchInClassTypeIndex( NULL, OM_FILEHANDLE, nHandle );
    ObjectManager_Unlock();
    if ( psObject == NULL ) {
        return FS_INVALIDHANDLE;
    }

    // Get associated volume
    sFileHandle_t *psFileHandle = ( sFileHandle_t * ) psObject->m_pData;
    sVolume_t *psVolume = psFileHandle->m_psVolume;
    sFilesystem_t *psFilesystem = psVolume->m_psFilesystem;

    // Call the file system read call
    FSReadCall *pReadFunction = ( FSReadCall * ) psFilesystem->m_pReadCall;
    return pReadFunction( psFileHandle, pBuffer, nBytes, nBytesRead );
}

KStatus FS_Seek( uint32 nHandle, uint32 nPosition ) {

    // First off, lets find the object relating to this handle, I know this will end up being
    // **really** slow, but it will do for now until I can be bothered to optimise it
    ObjectManager_Lock();
    sObject_t *psObject = ObjectManager_SearchInClassTypeIndex( NULL, OM_FILEHANDLE, nHandle );
    ObjectManager_Unlock();
    if ( psObject == NULL ) {
        return FS_INVALIDHANDLE;
    }
    sFileHandle_t *psFileHandle = ( sFileHandle_t * ) psObject->m_pData;
    psFileHandle->m_nPosition = nPosition;

    return NULL;
}


