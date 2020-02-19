#include <OSCalls.h>
#include <x86.h>
#include <Core.h>
#include <CI-FS.h>

// ELF Magic
uchar K_ELF_MAGIC[ 4 ] = { 0x75, 0x45, 0x4C, 0x46 };

// Prototypes
uint32 FS_Handler( uint32 nCall, void *pData );

// Globals
char *Kg_pszVolume;
char *Kg_pszPath;
char *Kg_pszFilename;

enum {
    REGISTERFS,
    MOUNT,
    OPEN
};

void FS_Init() {

    // Set kernel variables
    Kg_sKernel.m_nFileHandleIndex = 0;

    // Add to module list
    ModuleManager_CreateModule( "FS", FS_Handler );
    ModuleManager_CreateModuleCall( "FS", "RegisterFilesystem", REGISTERFS );
    ModuleManager_CreateModuleCall( "FS", "Mount", MOUNT );
    ModuleManager_CreateModuleCall( "FS", "Open", OPEN );

    // Create temp strings for volume etc
    Kg_pszVolume = ( char * ) MemoryManager_KAlloc( KFS_MAXIMUMFULLPATHSIZE );
    Kg_pszPath = ( char * ) MemoryManager_KAlloc( KFS_MAXIMUMFULLPATHSIZE );
    Kg_pszFilename = ( char * ) MemoryManager_KAlloc( KFS_MAXIMUMFULLPATHSIZE );

    KPrint( KDEBUG, "FS", "File system initialised\n" );
}

uint32 FS_RegisterFilesystem( char *pszName, FilesystemHandler *pHandler ) {

    // Create object
    ObjectManager_Lock();
    K_sObject_t * psObject = ObjectManager_CreateObject( KOBJECT_OBJ_FILESYSTEM, sizeof( K_sFilesystem_t ), pszName );
    K_sFilesystem_t *psFilesystem = ( K_sFilesystem_t * ) psObject->m_pData;
    psFilesystem->m_pHandler = pHandler;
    ObjectManager_Unlock();

    KPrint( KVERBOSE, "FS", "Filesystem [%s] registered\n", pszName );

    return NULL;
}

uint32 FS_RegisterFilesystemCall( KFS_sRegisterFilesystem_t *psData ) {
    return FS_RegisterFilesystem( psData->m_pszName, psData->m_pHandler );
}

uint32 FS_Mount( char *pszName, char *pszDevice, char *pszFileSystem, char *pszData ) {

    // Search for block I/O device
    ObjectManager_Lock();
    K_sObject_t *psIODeviceObject = ObjectManager_SearchNameInClass( NULL, KOBJECT_OBJ_IODEVICE, pszDevice );
    if ( psIODeviceObject == NULL ) {
        ObjectManager_Unlock();
        KPrint( KVERBOSE, "FS", "Can't create volume [%s] because I/O device [%s] non-existant\n", pszName, pszDevice );
        return KIO_INVALIDBLOCKIODEVICE;
    }
    K_sIODevice_t *psIODevice = ( K_sIODevice_t * ) psIODeviceObject->m_pData;

    // Search for filesystem
    K_sObject_t *psFileSystemObject = ObjectManager_SearchNameInClass( NULL, KOBJECT_OBJ_FILESYSTEM, pszFileSystem );
    if ( psFileSystemObject == NULL ) {
        ObjectManager_Unlock();
        KPrint( KVERBOSE, "FS", "Can't create volume [%s] because filesysten [%s] non-existant\n", pszName, pszFileSystem );
        return KIO_INVALIDBLOCKIODEVICE;
    }
    K_sFilesystem_t *psFilesystem = ( K_sFilesystem_t * ) psFileSystemObject->m_pData;

    // Create object
    K_sObject_t * psObject = ObjectManager_CreateObject( KOBJECT_OBJ_VOLUME, sizeof( K_sVolume_t ), pszName );
    K_sVolume_t *psVolume = ( K_sVolume_t * ) psObject->m_pData;
    psVolume->m_psIODeviceObject = psIODeviceObject;
    psVolume->m_psFilesystemObject = psFileSystemObject;
    psVolume->m_psIODevice = psIODevice;
    psVolume->m_psFilesystem = psFilesystem;

    // Increase reference counts of block/filesystem objects so they can't be deleted first
    psIODeviceObject->m_nReferenceCount++;
    psFileSystemObject->m_nReferenceCount++;

    // Call the device driver mount call
    KIO_sDDKMount_t sData;
    sData.m_pszData = pszData;
    sData.m_psIODevice = psIODevice;
    uint32 nRet = psIODevice->m_pHandler( KIO_MOUNT, &sData );
    if ( nRet != NULL ) {
        ObjectManager_Unlock();
        KPrint( KVERBOSE, "FS", "Device [%s] failed mount\n", ( char * ) & psIODeviceObject->m_szName );
        return KFS_ERRORMOUNTING;
    }

    KPrint( KVERBOSE, "FS", "Created volume [%s][%s][%s]\n", pszName, pszDevice, pszFileSystem );
    ObjectManager_Unlock();
    return NULL;
}

uint32 FS_MountCall( KFS_sMount_t *psData ) {
    return FS_Mount( psData->m_pszName, psData->m_pszDevice, psData->m_pszFileSystem, psData->m_pszData );
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
            if ( nType == K_FS_CHECKVOLUME )
                continue;
            else
                return false;
        case '/':
            if ( nType == K_FS_CHECKPATH )
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

uint32 FS_Parse( char * pszFullPath, char * pszVolume, char * pszPath, char * pszFilename ) {

    // Clear strings
    pszVolume[ 0 ]
    = '\0';
    pszPath[ 0 ] = '\0';
    pszFilename[ 0 ] = '\0';

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
        strncpy( pszVolume, pszFullPath, i );
        strncpy( pszPath , pszFullPath + i, nLength - i );
    } else {
        strncpy( pszPath , pszFullPath, nLength );
    }

    // See if there is a final "/" specifier, this should enable us to extract the path and filename
    nLength = strlen( pszPath );
    for ( i = nLength ; i >= 0; --i ) {
        if ( pszPath[ i ] == '/' ) {
            break;
        }
    }
    if ( i != -1 ) {
        strncpy( pszFilename, pszPath + i + 1, nLength - i - 1 );
        pszPath[ i + 1 ] = '\0';
    }

    // We now have the volume/path/filename, we now do a check to make sure only
    // valid characters have been used in them
    if ( FS_CheckFilename( K_FS_CHECKVOLUME, pszVolume ) != true ) {
        return KFS_INVALIDVOLUME;
    }
    if ( FS_CheckFilename( K_FS_CHECKPATH, pszPath ) != true ) {
        return KFS_INVALIDPATH;
    }
    if ( FS_CheckFilename( K_FS_CHECKFILENAME, pszFilename ) != true ) {
        return KFS_INVALIDPATH;
    }

    // All ok
    return NULL;
}

uint32 FS_Open( char * pszFullPath, uint32 nFlags, uint32 * nHandle ) {

    // Check path is not too long
    if ( strnlen( pszFullPath, KFS_MAXIMUMFULLPATHSIZE ) >= KFS_MAXIMUMFULLPATHSIZE )
        return KFS_PATHTOOLONG;

    // We need to parse the filename string to extract the volume/path and file
    if ( FS_Parse( pszFullPath, Kg_pszVolume, Kg_pszPath, Kg_pszPath ) != NULL ) {
        KPrint( KVERBOSE, "FS", "Path [%s] is not valid\n", pszFullPath );
        return KFS_INVALIDFULLPATH;
    }

    // Check the volume exists and is valid
    ObjectManager_Lock();
    K_sObject_t * psVolumeObject = ObjectManager_SearchNameInClass( NULL, KOBJECT_OBJ_VOLUME, Kg_pszVolume );
    if ( psVolumeObject == NULL ) {
        ObjectManager_Unlock();
        KPrint( KVERBOSE, "FS", "Volume [%s] not found\n", Kg_pszVolume );
        return KFS_VOLUMENOTFOUND;
    }
    K_sVolume_t *psVolume = ( K_sVolume_t * ) psVolumeObject->m_pData;

    // Create a file handle (we will delete this if the file can not be opened)
    K_sObject_t * psFileHandleObject = ObjectManager_CreateObject( KOBJECT_OBJ_FILEHANDLE, sizeof( K_sFileHandle_t ), "" );
    psFileHandleObject->m_nReferenceCount++;
    psFileHandleObject->m_nTypeIndex = Kg_sKernel.m_nFileHandleIndex++;
    K_sFileHandle_t *psFileHandle = ( K_sFileHandle_t * ) psFileHandleObject->m_pData;
    psFileHandle->m_psVolume = psVolume;
    psFileHandle->m_nPosition = 0;
    ObjectManager_Unlock();

    // Build open struct and call the individual file system open call
    KFS_sOpen_t sOpen;
    sOpen.m_psVolume = psVolume;
    sOpen.m_pszVolume = Kg_pszVolume;
    sOpen.m_pszPath = Kg_pszPath;
    sOpen.m_pszFilename = Kg_pszFilename;
    sOpen.m_psFileHandle = psFileHandle;
    K_sFilesystem_t *psFilesystem = psVolume->m_psFilesystem;
    uint32 nRet = psFilesystem->m_pHandler( KFS_OPEN, &sOpen );
    if ( nRet != NULL ) {
        KPrint( KVERBOSE, "FS", "Open failed on file [%s]\n", pszFullPath );
        ObjectManager_Lock();
        ObjectManager_DeleteObject( psFileHandleObject );
        ObjectManager_Unlock();
        return KFS_ERROROPENINGFILE;
    }

    *nHandle = psFileHandleObject->m_nTypeIndex;
    return NULL;
}

uint32 FS_Read( uint32 nHandle, void *pBuffer, uint32 nBytes, uint32 *nBytesRead ) {

    // Clear bytes read
    *nBytesRead = 0;

    // First off, lets find the object relating to this handle, I know this will end up being
    // **really** slow, but it will do for now until I can be bothered to optimise it
    ObjectManager_Lock();
    K_sObject_t *psObject = ObjectManager_SearchInClassTypeIndex( NULL, KOBJECT_OBJ_FILEHANDLE, nHandle );
    ObjectManager_Unlock();
    if ( psObject == NULL ) {
        return KFS_INVALIDHANDLE;
    }

    // Get associated volume
    K_sFileHandle_t *psFileHandle = ( K_sFileHandle_t * ) psObject->m_pData;
    K_sVolume_t *psVolume = psFileHandle->m_psVolume;

    // Build read struct and call the individual file system read call
    KFS_sRead_t sRead;
    sRead.m_pBuffer = pBuffer;
    sRead.m_nBytesNeeded = nBytes;
    sRead.m_nBytesRead = nBytesRead;
    sRead.m_psHandle = psFileHandle;
    K_sFilesystem_t *psFilesystem = psVolume->m_psFilesystem;
    return psFilesystem->m_pHandler( KFS_READ, &sRead );
}

uint32 FS_LoadElf( char *pszFilename ) {

    // Open the file
    uint32 nHandle;
    if ( FS_Open( pszFilename, KFS_READONLY, &nHandle ) != NULL ) {
        KPrint( KVERBOSE, "FS", "Error opening file [%s]\n", pszFilename );
        return KFS_ERROROPENINGFILE;
    }

    // Read in header
    K_sElfHeader_t sHeader;
    uint32 nBytesRead;
    if ( FS_Read( nHandle, &sHeader, sizeof( K_sElfHeader_t ), &nBytesRead ) ) {
        KPrint( KVERBOSE, "FS", "Error reading from file [%s]\n", pszFilename );
        return KFS_ERRORREADINGFROMFILE;
    }

    // Do some checks on the ELF header
    if ( strncmp( ( char * ) & sHeader.m_szIdent, (char *)&K_ELF_MAGIC, 4 ) != 0 ) {
        KPrint( KVERBOSE, "FS", "[%s] is not a valid ELF file\n", pszFilename );
        return KFS_INVALIDELFFILE;
    }
    if (sHeader.m_nType != K_ELF_TYPE_RELATIVE) {
        KPrint( KVERBOSE, "FS", "[%s] is not a valid ELF file\n", pszFilename );
        return KFS_INVALIDELFFILE;
        }
    //  if (h->e_machine != EM_386) err=ER_BADMACHINE;
    //  if (h->e_version != EV_CURRENT) err=ER_VERSION;

    KPrint( KVERBOSE, "FS", "[%u]\n", sHeader.m_nType );
    KPrint( KVERBOSE, "FS", "[%u]\n", sHeader.m_nMachine );

    return NULL;
}

uint32 FS_Handler( uint32 nCall, void * pData ) {
    switch ( nCall ) {
    case REGISTERFS:
        return FS_RegisterFilesystemCall( ( KFS_sRegisterFilesystem_t * ) pData );
    case MOUNT:
        return FS_MountCall( ( KFS_sMount_t * ) pData );
    }

    return KMODULE_INVALIDCALL;
}

