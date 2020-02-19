#include <Kernel.h>

// Lock
sLock_t l_sObjectLock;

void Object_LockInit() {
    Lock_Init( &l_sObjectLock );
}

void Object_Lock() {
    Lock_Lock( &l_sObjectLock );
}

void Object_Unlock() {
    Lock_Unlock( &l_sObjectLock );
}

void Object_Init() {

    // Initialise locking
    Object_LockInit();

    // Create the root directory
    MM_Lock();
    g_sKernel.m_psRootPath = MM_KAlloc( sizeof( sObjectDirectory_t ) );
    MM_Unlock();

    // Init types
    g_sKernel.m_nType = 0;

    // Fill in details
    sObjectDirectory_t *psRoot = g_sKernel.m_psRootPath;
    psRoot->m_psObjectHead = NULL;
    psRoot->m_psObjectTail = NULL;

    // Create basic types
    g_sKernel.m_nTypeDirectory = Object_CreateType( "Directory" );
    g_sKernel.m_nTypeWordValue = Object_CreateType( "Word" );

    // Now create system directory
    g_sKernel.m_psSystemRoot = Object_CreateDirectory( g_sKernel.m_psRootPath, "System" );
}

uint32 Object_CreateType( char *pszName ) {

    // Create the object type structure
    MM_Lock();
    sObjectType_t *psType = MM_KAlloc( sizeof( sObjectType_t ) );
    MM_Unlock();

    // Fill in details
    strncpy( ( char * ) & psType->m_szName, pszName, OBJECT_NAMELENGTH );
    psType->m_nPID = g_sKernel.m_psRunningProcessID;
    psType->m_nType = g_sKernel.m_nType++;

    // And return type number
    return psType->m_nType;
}

sObject_t *Object_CreateObject( sObjectDirectory_t *psDirectory, uint32 nType, char *pszName, uint32 nSizeOfData ) {

    // Create the object
    MM_Lock();
    sObject_t *psObject = MM_KAlloc( sizeof( sObject_t ) );
    MM_Unlock();

    // Fill in details
    strncpy( ( char * ) & psObject->m_szName, pszName, OBJECT_NAMELENGTH );
    psObject->m_nPID = g_sKernel.m_psRunningProcessID;
    psObject->m_nType = nType;
    MM_Lock();
    psObject->m_pData = MM_KAlloc( nSizeOfData );
    MM_Unlock();

    // And add to the specified directory
    sObject_t *psPrevious = psDirectory->m_psObjectHead;
    if ( psPrevious == NULL ) { // First object in directory
        psObject->m_psPrevious = psPrevious;
        psDirectory->m_psObjectHead = psObject;
        psDirectory->m_psObjectTail = psObject;
    } else {
        psPrevious->m_psNext = psObject;
        psObject->m_psPrevious = psPrevious;
        psDirectory->m_psObjectHead = psObject;
    }


    // Return new object
    return psObject;
}

sObjectWord_t *Object_CreateObjectWord( sObjectDirectory_t *psDirectory, char *pszName, uint32 *nValuePtr ) {

    // Create the object
    MM_Lock();
    sObjectWord_t *psObject = MM_KAlloc( sizeof( sObjectWord_t ) );
    MM_Unlock();

    // Fill in details
    strncpy( ( char * ) & psObject->m_szName, pszName, OBJECT_NAMELENGTH );
    psObject->m_nPID = g_sKernel.m_psRunningProcessID;
    psObject->m_nType = g_sKernel.m_nTypeWordValue;
    psObject->m_pWord = nValuePtr;

    // And add to the specified directory
    sObject_t * psPrevious = psDirectory->m_psObjectHead;
    if ( psPrevious == NULL ) { // First object in directory
        psObject->m_psPrevious = psPrevious;
        psDirectory->m_psObjectHead = ( sObject_t * ) psObject;
        psDirectory->m_psObjectTail = ( sObject_t * ) psObject;
    } else {
        psPrevious->m_psNext = ( sObject_t * ) psObject;
        psObject->m_psPrevious = psPrevious;
        psDirectory->m_psObjectHead = ( sObject_t * ) psObject;
    }


    // Return new object
    return psObject;
}

sObjectDirectory_t *Object_CreateDirectory( sObjectDirectory_t *psDirectory, char *pszName ) {

    // Call create object, but set it as a directory
    sObject_t * psObject = Object_CreateObject( psDirectory, g_sKernel.m_nTypeDirectory, pszName, sizeof( sObjectDirectory_t ) );

    // Fill in directory details
    sObjectDirectory_t *psNewDirectory = ( sObjectDirectory_t * ) psObject->m_pData;
    psNewDirectory->m_nPID = g_sKernel.m_psRunningProcessID;
    psNewDirectory->m_psObjectHead = NULL;
    psNewDirectory->m_psObjectTail = NULL;

    // And return new directory
    return psNewDirectory;
}

sObjectDirectory_t *Object_GetObjectPath( sObjectDirectory_t * psPath, char *pszObjectPath, uint32 nPathLength, uint32 nIndex ) {

    // Get next path entry
    uint32 i;
    for ( i = nIndex; i < nPathLength; i++ ) {
        if ( pszObjectPath[ i ] == '/' )
            break;
    }

    // If we got to end then this is the last path so return it
    if ( i >= nPathLength ) {
        return psPath;
    }

    // Get path
    char szPath[ OBJECT_NAMELENGTH ];
    uint32 nLen = i - nIndex;
    if ( nLen >= ( OBJECT_NAMELENGTH - 1 ) )
        nLen = ( OBJECT_NAMELENGTH - 1 );
    strncpy( ( char * ) & szPath, pszObjectPath + nIndex, nLen );
    szPath[ nLen ] = '\0';

    // If not, we need to scan this directory for the path
    sObject_t *psObject = psPath->m_psObjectTail;
    while ( psObject != NULL ) {
                               	
        // If this object is a directory, is it a match? (if so recurse)
        if ( psObject->m_nType == g_sKernel.m_nTypeDirectory ) {
            if ( strncmp( ( char * ) & szPath, ( char * ) & psObject->m_szName, OBJECT_NAMELENGTH ) == 0 ) {
                return Object_GetObjectPath( ( sObjectDirectory_t * ) psObject->m_pData, pszObjectPath, nPathLength, i + 1 );
            }
        }

        // Next object
        psObject = psObject->m_psNext;
    }

    // Not found, return null
    return NULL;
}

sObject_t *Object_GetObject( char *pszObjectPath, char *pszObjectName, uint32 nType ) {

    // First, get object path
    sObjectDirectory_t * psPath = Object_GetObjectPath( g_sKernel.m_psRootPath, pszObjectPath, strlen( pszObjectPath ), 0 );

    // Did we find the path?
    if ( psPath == NULL ) {
        Syslog_Entry( "OBJECT", "Path %s not found\n", pszObjectPath );
        return NULL;
    }

    // Now scan this path for the object
    sObject_t *psObject = psPath->m_psObjectTail;
    while ( psObject != NULL ) {

        // If this object is a directory, is it a match? (if so recurse)
        if ( psObject->m_nType == nType ) {
            if ( strncmp( pszObjectName, ( char * ) & psObject->m_szName, OBJECT_NAMELENGTH ) == 0 ) {
                return psObject;
            }
        }

        // Next object
        psObject = psObject->m_psNext;
    }

    // No match
    return NULL;
}

void *Object_GetObjectData( char *pszObjectPath, char *pszObjectName, uint32 nType ) {
     return Object_GetObject( pszObjectPath, pszObjectName, nType )->m_pData;
}

KStatus Object_Delete( sObjectDirectory_t *psDirectory, sObject_t *psObject ) {

    // Collate some data
    sObject_t * psPrevious = psObject->m_psPrevious;
    sObject_t *psNext = psObject->m_psNext;

    // Point previous object to next
    if ( psPrevious != NULL ) {
        psPrevious->m_psNext = psNext;
    }

    // Point next object to this
    if ( psNext != NULL ) {
        psNext->m_psPrevious = psPrevious;
    }

    // See if directory tail needs changing
    if ( psDirectory->m_psObjectTail == psObject ) {
        psDirectory->m_psObjectTail = psNext;
    }

    // See if directory head needs changing
    if ( psDirectory->m_psObjectHead == psObject ) {
        psDirectory->m_psObjectHead = psPrevious;
    }

    // Now free memory
    MM_KFree( psObject );

    return NULL;
}

#ifdef DEBUG
void Object_DumpTreeDirectory( sObjectDirectory_t *psDirectory, uint32 nLevel ) {

    // Start parsing through all objects in the directory
    sObject_t * psObject = psDirectory->m_psObjectTail;
    sObject_t *psPrevious = NULL;
    while ( psObject != NULL ) {

        // Create some padding
        char szSpace[ 32 ];
        uint32 i;
        for ( i = 0;i < nLevel; i++ ) {
            szSpace[ i ] = ' ';
        }
        szSpace[ i ] = '\0';

        // Dump the object to the log
        if ( psObject->m_nType == g_sKernel.m_nTypeDirectory ) {
            Syslog_Lock();
            Syslog_Entry( "OBJECT", "%s[%s]\n", ( char * ) & szSpace, ( char * ) & psObject->m_szName );
            Syslog_Unlock();

            // If it's a directory object, then recurse
            sObjectDirectory_t * psNewDirectory = ( sObjectDirectory_t * ) psObject->m_pData;
            Object_DumpTreeDirectory( psNewDirectory, nLevel + 1 );
        } else {
            Syslog_Lock();
            Syslog_Entry( "OBJECT", "%s%s\n", ( char * ) & szSpace, ( char * ) & psObject->m_szName );
            Syslog_Unlock();
        }

        // Next object
        psPrevious = psObject;
        psObject = psObject->m_psNext;
    }

    // Sanity check on head set correct
    if ( psPrevious != psDirectory->m_psObjectHead ) {
        Syslog_Lock();
        Syslog_Entry( "OBJECT", "Incorrect head on object path\n" );
        Syslog_Unlock();
    }
}

void Object_DumpTree() {

    // Start at the object directory root
    Object_DumpTreeDirectory( g_sKernel.m_psRootPath, 0 );
}
#endif

