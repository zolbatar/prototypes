#include <Kernel.h>

#define OM_PATHSIZELENGTH 8192

// Entity types
enum {
    ENTITY_WORD,
    ENTITY_STRING
};

// Lock
sLock_t sObjectLock;

// Globals
char *g_pszPath = NULL;
char *g_pszKey = NULL;

void ObjectManager_LockInit() {
    Lock_Init( "OBJECTS", &sObjectLock );
}

void ObjectManager_Lock() {
    Lock_Lock( &sObjectLock );
}

void ObjectManager_Unlock() {
    Lock_Unlock( &sObjectLock );
}

void ObjectManager_Init() {

    // Set object count
    g_sKernel.m_psTailObject = NULL;
    g_sKernel.m_psHeadObject = NULL;
    g_sKernel.m_nObjectIndex = 0;

    // Initialise locking
    ObjectManager_LockInit( );

    // Space for path portions
    g_pszPath = ( char * ) MemoryManager_KAlloc( OM_PATHSIZELENGTH );
    g_pszKey = ( char * ) MemoryManager_KAlloc( OM_NAMELENGTH );

    // Set system stat objects
    ObjectManager_ConstructPath( "/Kernel/" );
    ObjectManager_ConstructKey( "Version(Major)" );
    ObjectManager_CreateEntityWord( VERSION_MAJOR );
    ObjectManager_ConstructKey( "Version(Minor)" );
    ObjectManager_CreateEntityWord( VERSION_MINOR );
    ObjectManager_ConstructKey( "Version(Codename)" );
    ObjectManager_CreateEntityString( VERSION_CODENAME );

    KPrint( "OBJECTS", "Object manager initialised\n" );
}

void ObjectManager_ConstructPath( char *pszPathComponent ) {

    // Check not too long (this is a serious fault currently and halts, this may change)
    if ( strnlen( pszPathComponent, OM_PATHSIZELENGTH ) >= OM_PATHSIZELENGTH ) {
        KPrint( "OBJECTS", "Path [%s] too long\n", pszPathComponent );
        halt();
    }

    // Set value
    strcpy( g_pszPath, pszPathComponent );
}

void ObjectManager_ConstructPathAppend( char *pszPathComponent ) {

    // Check not too long
    if ( ( strnlen( g_pszPath, OM_PATHSIZELENGTH ) + strnlen( pszPathComponent, OM_PATHSIZELENGTH ) ) >= OM_PATHSIZELENGTH ) {
        KPrint( "OBJECTS", "Path component [%s] too long\n", pszPathComponent );
        halt();
    }

    // Append value
    strcat( g_pszPath, pszPathComponent );
}

void ObjectManager_ConstructKey( char *pszKeyComponent ) {

    // Check not too long
    if ( strnlen( pszKeyComponent, OM_NAMELENGTH ) >= OM_NAMELENGTH ) {
        KPrint( "OBJECTS", "Key [%s] too long\n", pszKeyComponent );
        halt();
    }

    // Set value
    strcpy( g_pszKey, pszKeyComponent );
}

void ObjectManager_ConstructKeyAppend( char *pszKeyComponent ) {

    // Check not too long
    if ( ( strnlen( g_pszKey, OM_NAMELENGTH ) + strnlen( pszKeyComponent, OM_NAMELENGTH ) ) >= OM_NAMELENGTH ) {
        KPrint( "OBJECTS", "Key component [%s] too long\n", pszKeyComponent );
        halt();
    }
    // Append value
    strcat( g_pszKey, pszKeyComponent );
}

KStatus ObjectManager_Parse( ) {
    return NULL;
}

sObject_t *ObjectManager_CreateObject( uint32 nClass, uint32 nSize ) {

    // Allocate memory
    MemoryManager_Lock();
    sObject_t * psObject = MemoryManager_KAlloc( sizeof( sObject_t ) );
    if ( nSize > 0 ) {
        void * pData = MemoryManager_KAlloc( nSize );
        psObject->m_pData = pData;
    } else {
        psObject->m_pData = NULL;
    }
    MemoryManager_Unlock();

    // Add to linked list
    if ( g_sKernel.m_psTailObject == NULL ) {
        psObject->m_psPrevious = NULL;
        g_sKernel.m_psTailObject = psObject;
    } else {
        sObject_t *psPrevious = g_sKernel.m_psHeadObject;
        psPrevious->m_psNext = psObject;
        psObject->m_psPrevious = psPrevious;
    }
    psObject->m_psNext = NULL;
    g_sKernel.m_psHeadObject = psObject;

    // Set Name
    strncpy ( ( char * ) & psObject->m_szName, g_pszKey, OM_NAMELENGTH );

    // Default values
    psObject->m_nObjectIndex = g_sKernel.m_nObjectIndex++;
    psObject->m_nProcessID = g_sKernel.m_psRunningProcessID;
    psObject->m_nThreadID = g_sKernel.m_psRunningThreadID;
    psObject->m_nReferenceCount = 0;
    psObject->m_nClass = nClass;
    psObject->m_nTypeIndex = 0;
    psObject->m_nTypeSubIndex = 0;

    // Return object pointer
    return psObject;
}

sObject_t *ObjectManager_GetStart( sObject_t *psStart ) {
    if ( psStart == NULL ) {
        return g_sKernel.m_psTailObject;
    } else {
        return psStart->m_psNext;
    }
}

void ObjectManager_DeleteObject( sObject_t *psObject ) {

    // Is it being referenced?
    if ( psObject->m_nReferenceCount > 0 ) {
#ifdef DEBUG
        KPrint( "OBJECTS", "Object [%s] can not be deleted because its being referenced\n", ( char * ) & psObject->m_szName );
#endif

        return ;
    }

    // Attached data to object?
    if ( psObject->m_pData != NULL )
        MemoryManager_KFree( psObject->m_pData );

    // Drop item from linked list
    if ( psObject->m_psNext == NULL ) {
        g_sKernel.m_psHeadObject = psObject->m_psPrevious;
        sObject_t *psPrevious = psObject->m_psPrevious;
        psPrevious->m_psNext = NULL;
    } else {
        sObject_t *psNext = psObject->m_psNext;
        psNext->m_psPrevious = psObject->m_psPrevious;
        sObject_t *psPrevious = psObject->m_psPrevious;
        psPrevious->m_psNext = psObject->m_psNext;
    }

    // Free memory for object
    MemoryManager_KFree( psObject );
}

sObject_t *ObjectManager_SearchNameInClass( sObject_t *psStart, uint32 m_nClass ) {

    // Parse path
    ObjectManager_Parse( );

    // Loop through list
    sObject_t * psObject = ObjectManager_GetStart( psStart );
    while ( psObject != NULL ) {

        if ( psObject->m_nClass == m_nClass ) {
            if ( strncmp( g_pszKey, ( char * ) & psObject->m_szName, OM_NAMELENGTH ) == 0 )
                break;
        }
        psObject = psObject->m_psNext;
    }
    return psObject;
}

sObject_t *ObjectManager_SearchNameInClassTypeIndex( sObject_t * psStart, uint32 m_nClass, uint32 nTypeIndex ) {

    // Parse path
    ObjectManager_Parse( );

    // Loop through list
    sObject_t * psObject = ObjectManager_GetStart( psStart );
    while ( psObject != NULL ) {
        if ( ( psObject->m_nClass == m_nClass ) && ( psObject->m_nTypeIndex == nTypeIndex ) ) {
            if ( strncmp( g_pszKey, ( char * ) & psObject->m_szName, OM_NAMELENGTH ) == 0 )
                break;
        }
        psObject = psObject->m_psNext;
    }
    return psObject;
}

sObject_t *ObjectManager_SearchInClass( sObject_t * psStart, uint32 m_nClass ) {

    // Loop through list
    sObject_t * psObject = ObjectManager_GetStart( psStart );
    while ( psObject != NULL ) {
        if ( psObject->m_nClass == m_nClass ) {
            break;
        }
        psObject = psObject->m_psNext;
    }
    return psObject;
}

sObject_t *ObjectManager_SearchInClassTypeIndex( sObject_t * psStart, uint32 m_nClass, uint32 nTypeIndex ) {

    // Loop through list
    sObject_t * psObject = ObjectManager_GetStart( psStart );
    while ( psObject != NULL ) {
        if ( ( psObject->m_nClass == m_nClass ) && ( psObject->m_nTypeIndex == nTypeIndex ) ) {
            break;
        }
        psObject = psObject->m_psNext;
    }
    return psObject;
}

sObject_t *ObjectManager_SearchInClassTypeSubIndex( sObject_t * psStart, uint32 m_nClass, uint32 nTypeSubIndex ) {

    // Loop through list
    sObject_t * psObject = ObjectManager_GetStart( psStart );
    while ( psObject != NULL ) {
        if ( ( psObject->m_nClass == m_nClass ) && ( psObject->m_nTypeSubIndex == nTypeSubIndex ) ) {
            break;
        }
        psObject = psObject->m_psNext;
    }
    return psObject;
}

sObject_t *ObjectManager_GetObjectContainingData( void *pData ) {

    // Loop through list
    sObject_t * psObject = ObjectManager_GetStart( NULL );
    while ( psObject != NULL ) {
        if ( psObject->m_pData == pData ) {
            break;
        }
        psObject = psObject->m_psNext;
    }
    return psObject;
}

KStatus ObjectManager_CreateEntityWord( uint32 nValue ) {

    // Create object
    ObjectManager_Lock();
    sObject_t * psObject = ObjectManager_CreateObject( OM_ENTITY, 0 );
    psObject->m_nClass = ENTITY_WORD;
    psObject->m_pData = ( void * ) nValue;
    ObjectManager_Unlock();

    return NULL;
}

KStatus ObjectManager_CreateEntityString( char *pszValue ) {

    // Create object
    ObjectManager_Lock();
    sObject_t * psObject = ObjectManager_CreateObject( OM_ENTITY, 0 );
    psObject->m_nClass = ENTITY_WORD;
    MemoryManager_Lock();
    psObject->m_pData = MemoryManager_KAlloc( strlen( pszValue ) );
    MemoryManager_Unlock();
    strcpy( psObject->m_pData, pszValue );
    ObjectManager_Unlock();

    return NULL;
}

KStatus ObjectManager_GetEntityWord( uint32 *pnValue ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Parse path
    ObjectManager_Parse( );

    // Set start and loop
    sObject_t * psObject = g_sKernel.m_psTailObject;
    while ( psObject != NULL ) {
        if ( psObject->m_nClass == OM_ENTITY && psObject->m_nClass == ENTITY_WORD
                && ( strncmp( ( char * ) & psObject->m_szName, g_pszKey, OM_NAMELENGTH ) == 0 ) ) {
            break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
#ifdef DEBUG
        KPrint( "OBJECTS", "Entity [%s] [%s] not found\n", g_pszPath, g_pszKey );
#endif

        ObjectManager_Unlock();
        return OM_OBJECTNOTFOUND;
    }

    // Return data
    *pnValue = ( uint32 ) psObject->m_pData;

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

KStatus ObjectManager_GetEntityStringLength( uint32 *pnValue ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Set start and loop
    sObject_t * psObject = g_sKernel.m_psTailObject;
    while ( psObject != NULL ) {
        if ( psObject->m_nClass == OM_ENTITY && psObject->m_nClass == ENTITY_WORD
                && ( strncmp( ( char * ) & psObject->m_szName, g_pszKey, OM_NAMELENGTH ) == 0 ) ) {
            break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
#ifdef DEBUG
        KPrint( "OBJECTS", "Entity [%s] [%s] not found\n", g_pszPath, g_pszKey );
#endif

        ObjectManager_Unlock();
        return OM_OBJECTNOTFOUND;
    }

    // Return data
    *pnValue = strlen( ( char * ) psObject->m_pData );

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

KStatus ObjectManager_GetEntityString( char *pszValue ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Set start and loop
    sObject_t * psObject = g_sKernel.m_psTailObject;
    while ( psObject != NULL ) {
        if ( psObject->m_nClass == OM_ENTITY && psObject->m_nClass == ENTITY_WORD
                && ( strncmp( ( char * ) & psObject->m_szName, g_pszKey, OM_NAMELENGTH ) == 0 ) ) {
            break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
#ifdef DEBUG
        KPrint( "OBJECTS", "Entity [%s] [%s] not found\n", g_pszPath, g_pszKey );
#endif

        ObjectManager_Unlock();
        return OM_OBJECTNOTFOUND;
    }

    // Return data
    strcpy( pszValue, ( char * ) psObject->m_pData );

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

