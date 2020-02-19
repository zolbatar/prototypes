#include <OSCalls.h>
#include <x86.h>
#include <Core.h>
#include <CI-Object.h>

// Prototypes
uint32 ObjectManager_Handler( uint32 nCall, void * pData );

// Entity types
enum {
    ENTITY_WORD,
    ENTITY_STRING
};

// Calls
enum {
    GETKEYWORD,
    GETKEYSTRINGLENGTH,
    GETKEYSTRING,
    CREATEKEYWORD,
    CREATEKEYSTRING
};

// Lock
K_sLock_t sObjectLock;

void ObjectManager_LockInit() {
    Lock_Init( &sObjectLock );
}

void ObjectManager_Lock() {
    Lock_Lock( &sObjectLock );
}

void ObjectManager_Unlock() {
    Lock_Unlock( &sObjectLock );
}

void ObjectManager_Init() {

    // Set object count
    Kg_sKernel.m_psTailObject = NULL;
    Kg_sKernel.m_psHeadObject = NULL;
    Kg_sKernel.m_nObjectIndex = 0;

    // Initialise locking
    ObjectManager_LockInit( );

    // Add object manager to module list
    ModuleManager_CreateModule( "ObjectManager", ObjectManager_Handler );
    ModuleManager_CreateModuleCall( "ObjectManager", "GetKeyWord", GETKEYWORD );
    ModuleManager_CreateModuleCall( "ObjectManager", "GetKeyStringLength", GETKEYSTRINGLENGTH );
    ModuleManager_CreateModuleCall( "ObjectManager", "GetKeyString", GETKEYSTRING );
    ModuleManager_CreateModuleCall( "ObjectManager", "CreateKeyWord", CREATEKEYWORD );
    ModuleManager_CreateModuleCall( "ObjectManager", "CreateKeyString", CREATEKEYSTRING );

    // Set system stat objects
    ObjectManager_CreateEntityWord( "Kernel/Version(Major)", K_VERSION_MAJOR );
    ObjectManager_CreateEntityWord( "Kernel/Version(Minor)", K_VERSION_MINOR );
    ObjectManager_CreateEntityWord( "Kernel/Version(Revision)", K_VERSION_REVISION );
    ObjectManager_CreateEntityString( "Kernel/Version(Codename)", K_VERSION_CODENAME );

    KPrint( KDEBUG, "OBJECTS", "Object manager initialised\n" );
}

K_sObject_t *ObjectManager_CreateObject( uint32 nClass, uint32 nSize, char *pszName ) {

    // Allocate memory
    MemoryManager_Lock();
    K_sObject_t * psObject = MemoryManager_KAlloc( sizeof( K_sObject_t ) );
    if ( nSize > 0 ) {
        void * pData = MemoryManager_KAlloc( nSize );
        psObject->m_pData = pData;
    } else {
        psObject->m_pData = NULL;
    }
    MemoryManager_Unlock();

    // Add to linked list
    if ( Kg_sKernel.m_psTailObject == NULL ) {
        psObject->m_psPrevious = NULL;
        Kg_sKernel.m_psTailObject = psObject;
    } else {
        K_sObject_t *psPrevious = Kg_sKernel.m_psHeadObject;
        psPrevious->m_psNext = psObject;
        psObject->m_psPrevious = psPrevious;
    }
    psObject->m_psNext = NULL;
    Kg_sKernel.m_psHeadObject = psObject;

    // Set Name
    strncpy ( ( char * ) & psObject->m_szName, pszName, KOBJECT_NAMELENGTH );

    // Default settings
    psObject->m_nObjectIndex = Kg_sKernel.m_nObjectIndex++;
    psObject->m_nProcessID = Kg_sKernel.m_psRunningProcessID;
    psObject->m_nThreadID = Kg_sKernel.m_psRunningThreadID;
    psObject->m_nReferenceCount = 0;
    psObject->m_nClass = nClass;
    psObject->m_nTypeIndex = 0;
    psObject->m_nTypeSubIndex = 0;

    // Return object pointer
    return psObject;
}

K_sObject_t *ObjectManager_GetStart( K_sObject_t *psStart ) {
    if ( psStart == NULL ) {
        return Kg_sKernel.m_psTailObject;
    } else {
        return psStart->m_psNext;
    }
}

void ObjectManager_DeleteObject( K_sObject_t *psObject ) {

    // Is it being references
    if ( psObject->m_nReferenceCount > 0 ) {
        KPrint( KVERBOSE, "OBJECTS", "Object [%s] can not be deleted because its being referenced\n", ( char * ) & psObject->m_szName );
        return ;
    }

    // Attached data to object?
    if ( psObject->m_pData != NULL )
        MemoryManager_KFree( psObject->m_pData );

    // Drop item from linked list
    if ( psObject->m_psNext == NULL ) {
        Kg_sKernel.m_psHeadObject = psObject->m_psPrevious;
        K_sObject_t *psPrevious = psObject->m_psPrevious;
        psPrevious->m_psNext = NULL;
    } else {
        K_sObject_t *psNext = psObject->m_psNext;
        psNext->m_psPrevious = psObject->m_psPrevious;
        K_sObject_t *psPrevious = psObject->m_psPrevious;
        psPrevious->m_psNext = psObject->m_psNext;
    }

    // Free memory for object
    MemoryManager_KFree( psObject );
}

K_sObject_t *ObjectManager_SearchNameInClass( K_sObject_t *psStart, uint32 m_nClass, char *pszSearchString ) {

    // Loop through list
    K_sObject_t * psObject = ObjectManager_GetStart( psStart );
    while ( psObject != NULL ) {

        if ( psObject->m_nClass == m_nClass ) {
            if ( strncmp( pszSearchString, ( char * ) & psObject->m_szName, KOBJECT_NAMELENGTH ) == 0 )
                break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
        return NULL;
    }

    return psObject;
}

K_sObject_t *ObjectManager_SearchNameInClassTypeIndex( K_sObject_t * psStart, uint32 m_nClass, char * pszSearchString, uint32 nTypeIndex ) {

    // Loop through list
    K_sObject_t * psObject = ObjectManager_GetStart( psStart );
    while ( psObject != NULL ) {
        if ( ( psObject->m_nClass == m_nClass ) && ( psObject->m_nTypeIndex == nTypeIndex ) ) {
            if ( strncmp( pszSearchString, ( char * ) & psObject->m_szName, KOBJECT_NAMELENGTH ) == 0 )
                break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
        return NULL;
    }

    return psObject;
}

K_sObject_t *ObjectManager_SearchInClass( K_sObject_t * psStart, uint32 m_nClass ) {

    // Loop through list
    K_sObject_t * psObject = ObjectManager_GetStart( psStart );
    while ( psObject != NULL ) {
        if ( psObject->m_nClass == m_nClass ) {
            break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
        return NULL;
    }

    return psObject;
}

K_sObject_t *ObjectManager_SearchInClassTypeIndex( K_sObject_t * psStart, uint32 m_nClass, uint32 nTypeIndex ) {

    // Loop through list
    K_sObject_t * psObject = ObjectManager_GetStart( psStart );
    while ( psObject != NULL ) {
        if ( ( psObject->m_nClass == m_nClass ) && ( psObject->m_nTypeIndex == nTypeIndex ) ) {
            break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
        return NULL;
    }

    return psObject;
}

uint32 ObjectManager_CreateEntityWord( char *pszName, uint32 nValue ) {

    // Create object
    ObjectManager_Lock();
    K_sObject_t * psObject = ObjectManager_CreateObject( KOBJECT_OBJ_ENTITY, sizeof( K_sObjectEntity_t ), "Entity Word" );
    K_sObjectEntity_t *psEntity = ( K_sObjectEntity_t * ) psObject->m_pData;
    strncpy( ( char * ) & psEntity->m_szName, pszName, KOBJECT_ENTITYLENGTH );
    psEntity->m_nValueType = ENTITY_WORD;
    psEntity->m_nValue = nValue;
    ObjectManager_Unlock();

    return NULL;
}

uint32 ObjectManager_CreateEntityWordCall( KObject_sGetSetEntityWord_t *psData ) {
    return ObjectManager_CreateEntityWord( psData->m_pszName, psData->m_nValue );
}

uint32 ObjectManager_CreateEntityString( char *pszName, char *pszValue ) {

    // Create object
    ObjectManager_Lock();
    K_sObject_t * psObject = ObjectManager_CreateObject( KOBJECT_OBJ_ENTITY, sizeof( K_sObjectEntity_t ), "Entity String" );
    K_sObjectEntity_t *psEntity = ( K_sObjectEntity_t * ) psObject->m_pData;
    strncpy( ( char * ) & psEntity->m_szName, pszName, KOBJECT_ENTITYLENGTH );
    psEntity->m_nValueType = ENTITY_STRING;
    MemoryManager_Lock();
    psEntity->m_pData = MemoryManager_KAlloc( strlen( pszValue ) );
    MemoryManager_Unlock();
    strcpy( psEntity->m_pData, pszValue );
    ObjectManager_Unlock();

    return NULL;
}

uint32 ObjectManager_CreateEntityStringCall( KObject_sGetSetEntityString_t *psData ) {
    return ObjectManager_CreateEntityString( psData->m_pszName, psData->m_pszValue );
}

uint32 ObjectManager_GetEntityWord( KObject_sGetSetEntityWord_t *psData ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Set start and loop
    K_sObject_t * psObject = Kg_sKernel.m_psTailObject;
    K_sObjectEntity_t *psEntity = NULL;
    while ( psObject != NULL ) {
        if ( psObject->m_nClass == KOBJECT_OBJ_ENTITY ) {
            psEntity = ( K_sObjectEntity_t * ) psObject->m_pData;
            if ( psEntity->m_nValueType == ENTITY_WORD && ( strncmp( ( char * ) & psEntity->m_szName, psData->m_pszName, KOBJECT_ENTITYLENGTH ) == 0 ) )
                break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
        KPrint( KVERBOSE, "OBJECTS", "Entity [%s] not found\n", ( char * ) & psEntity->m_szName );
        ObjectManager_Unlock();
        return KOBJECT_OBJECTNOTFOUND;
    }

    // Return data
    psData->m_nValue = psEntity->m_nValue;

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

uint32 ObjectManager_GetEntityStringLength( KObject_sGetSetEntityWord_t *psData ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Set start and loop
    K_sObject_t * psObject = Kg_sKernel.m_psTailObject;
    K_sObjectEntity_t *psEntity = NULL;
    while ( psObject != NULL ) {
        if ( psObject->m_nClass == KOBJECT_OBJ_ENTITY ) {
            psEntity = ( K_sObjectEntity_t * ) psObject->m_pData;
            if ( psEntity->m_nValueType == ENTITY_STRING && ( strncmp( ( char * ) & psEntity->m_szName, psData->m_pszName, KOBJECT_ENTITYLENGTH ) == 0 ) )
                break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
        KPrint( KVERBOSE, "OBJECTS", "Entity [%s] not found\n", ( char * ) & psEntity->m_szName );
        ObjectManager_Unlock();
        return KOBJECT_OBJECTNOTFOUND;
    }

    // Return data
    psData->m_nValue = strlen( psEntity->m_szName );

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

uint32 ObjectManager_GetEntityString( KObject_sGetSetEntityString_t *psData ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Set start and loop
    K_sObject_t * psObject = Kg_sKernel.m_psTailObject;
    K_sObjectEntity_t *psEntity = NULL;
    while ( psObject != NULL ) {
        if ( psObject->m_nClass == KOBJECT_OBJ_ENTITY ) {
            psEntity = ( K_sObjectEntity_t * ) psObject->m_pData;
            if ( psEntity->m_nValueType == ENTITY_STRING && ( strncmp( ( char * ) & psEntity->m_szName, psData->m_pszName, KOBJECT_ENTITYLENGTH ) == 0 ) )
                break;
        }
        psObject = psObject->m_psNext;
    }

    // See if we found an object
    if ( psObject == NULL ) {
        KPrint( KVERBOSE, "OBJECTS", "Entity [%s] not found\n", ( char * ) & psEntity->m_szName );
        ObjectManager_Unlock();
        return KOBJECT_OBJECTNOTFOUND;
    }

    // Return data
    strcpy( psData->m_pszValue, ( char * ) & psEntity->m_szName );

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

uint32 ObjectManager_Handler( uint32 nCall, void * pData ) {
    switch ( nCall ) {
    case GETKEYWORD:
        return ObjectManager_GetEntityWord( ( KObject_sGetSetEntityWord_t * ) pData );
    case GETKEYSTRINGLENGTH:
        return ObjectManager_GetEntityStringLength( ( KObject_sGetSetEntityWord_t * ) pData );
    case GETKEYSTRING:
        return ObjectManager_GetEntityString( ( KObject_sGetSetEntityString_t * ) pData );
    case CREATEKEYWORD:
        return ObjectManager_CreateEntityWordCall( ( KObject_sGetSetEntityWord_t * ) pData );
    case CREATEKEYSTRING:
        return ObjectManager_CreateEntityStringCall( ( KObject_sGetSetEntityString_t * ) pData );
    }
    return KMODULE_INVALIDCALL;
}

