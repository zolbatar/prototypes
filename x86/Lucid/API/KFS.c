#include <OSCalls.h>
#include <CI-FS.h>

uint32 KFS_nHandle;
uint32 KFS_nRegisterFilesystem;
uint32 KFS_nMount;
uint32 KFS_nOpen;

void KFS_Init() {

    // Get handle
    KFS_nHandle = KModule_GetHandle( "FS" );

    // Get call codes
    KFS_nRegisterFilesystem = KModule_GetCallID( KFS_nHandle, "RegisterFilesystem" );
    KFS_nMount = KModule_GetCallID( KFS_nHandle, "Mount" );
    KFS_nOpen = KModule_GetCallID( KFS_nHandle, "Open" );
}

uint32 KFS_RegisterFilesystem( char *pszName, FilesystemHandler *pHandler ) {

    // Check if initialised
    if ( KFS_nHandle == NULL )
        KFS_Init();

    KFS_sRegisterFilesystem_t sData;
    sData.m_pszName = pszName;
    sData.m_pHandler = pHandler;
    return KModule_Call( KFS_nHandle, KFS_nRegisterFilesystem, &sData );
}

uint32 KFS_Mount( char *pszName, char *pszDevice, char *pszFileSystem, char *pszAddress, char *pszData ) {

    // Check if initialised
    if ( KFS_nHandle == NULL )
        KFS_Init();

    KFS_sMount_t sData;
    sData.m_pszName = pszName;
    sData.m_pszDevice = pszDevice;
    sData.m_pszFileSystem = pszFileSystem;
    sData.m_pszAddress = pszAddress;
    sData.m_pszData = pszData;
    return KModule_Call( KFS_nHandle, KFS_nMount, &sData );
}

uint32 KFS_Open( char *pszFullPath, uint32 nFlags, uint32 *nHandle ) {

    // Check if initialised
    if ( KFS_nHandle == NULL )
        KFS_Init();

    return KModule_Call( KFS_nHandle, KFS_nOpen, &sData );
}


