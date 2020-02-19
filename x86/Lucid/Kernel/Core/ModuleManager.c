#include <OSCalls.h>
#include <x86.h>
#include <Core.h>

// Prototypes
extern void ModuleManagerGetHandle();
extern void ModuleManagerReleaseHandle();
extern void ModuleManagerGetCallID();
extern void ModuleManagerCall();
extern void ModuleManagerCreateModule();
extern void ModuleManagerCreateModuleCall();

void ModuleManager_Init() {

    // Set that no modules are initialised
    Kg_sKernel.m_nModuleIndex = 0;

    // Attach module handler to interrupts
    Descriptor_SetInterruptGate( 0x80, &ModuleManagerGetHandle );
    Descriptor_SetInterruptGate( 0x81, &ModuleManagerReleaseHandle );
    Descriptor_SetInterruptGate( 0x82, &ModuleManagerGetCallID );
    Descriptor_SetInterruptGate( 0x83, &ModuleManagerCall );
    Descriptor_SetInterruptGate( 0x84, &ModuleManagerCreateModule );
    Descriptor_SetInterruptGate( 0x85, &ModuleManagerCreateModuleCall );

    KPrint( KDEBUG, "MODULES", "Module manager initialised\n" );
}

uint32 ModuleManager_CreateModule( char *pszName, void *psHandler ) {

    // Create object
    ObjectManager_Lock();
    K_sObject_t * psObject = ObjectManager_CreateObject( KOBJECT_OBJ_MODULE, sizeof( K_sModule_t ), pszName );
    psObject->m_nTypeIndex = Kg_sKernel.m_nModuleIndex++;
    K_sModule_t * psModule = ( K_sModule_t * ) psObject->m_pData;
    psModule->m_pHandler = psHandler;
    ObjectManager_Unlock();

    KPrint( KVERBOSE, "MODULES", "Module [%s] [%u] created\n", pszName, psObject->m_nTypeIndex );
    return NULL;
}

void ModuleManager_CreateModuleInt( char *pszName, void *psHandler ) {
    Kg_sKernel.m_psCallStack->eax = ModuleManager_CreateModule( pszName, psHandler );
}

uint32 ModuleManager_CreateModuleCall( char *pszModuleName, char *pszCallName, uint32 nCode ) {

    // Lock object manager
    ObjectManager_Lock();

    // Search for module
    K_sObject_t * psObjectParent = ObjectManager_SearchNameInClass( NULL, KOBJECT_OBJ_MODULE, pszModuleName );

    // See if we found a module
    if ( psObjectParent == NULL ) {
        ObjectManager_Unlock();
        KPrint( KVERBOSE, "MODULES", "[%s] Module not found\n", pszModuleName );
        return KMODULE_MODULENOTFOUND;
    }

    // Add object
    K_sObject_t *psObject = ObjectManager_CreateObject( KOBJECT_OBJ_MODULECALL, 0, pszCallName );
    psObject->m_nTypeIndex = psObjectParent->m_nTypeIndex;
    psObject->m_nTypeSubIndex = nCode;

    // Unlock object manager
    ObjectManager_Unlock();

    KPrint( KVERBOSE, "MODULES", "Module call [%s] [%u-%u] created\n", pszCallName, psObject->m_nTypeIndex, nCode );
    return NULL;
}

void ModuleManager_CreateModuleCallInt( char *pszModuleName, char *pszCallName, uint32 nCode ) {
    Kg_sKernel.m_psCallStack->eax = ModuleManager_CreateModuleCall( pszModuleName, pszCallName, nCode );
}

static inline uint32 ModuleManager_GetHandle( char *pszModule ) {

    // Lock object manager
    ObjectManager_Lock();

    // Search for module
    K_sObject_t * psObjectParent = ObjectManager_SearchNameInClass( NULL, KOBJECT_OBJ_MODULE, pszModule );

    // See if we found a module
    if ( psObjectParent == NULL ) {
        KPrint( KVERBOSE, "MODULES", "[%s] Module not found\n", pszModule );
        return KMODULE_MODULENOTFOUND;
    }
    // We have a match, return code and increment reference count
    psObjectParent->m_nReferenceCount++;

    // Unlock object manager
    ObjectManager_Unlock();

    return psObjectParent->m_nTypeIndex;
}

void ModuleManager_GetHandleInt( char *pszModule ) {
    Kg_sKernel.m_psCallStack->eax = ModuleManager_GetHandle( pszModule );
}

static inline uint32 ModuleManager_ReleaseHandle( uint32 nHandle ) {

    // Lock object manager
    ObjectManager_Lock();

    // Search for module
    K_sObject_t * psObjectParent = ObjectManager_SearchInClassTypeIndex( NULL, KOBJECT_OBJ_MODULE, nHandle );

    // See if we found a module
    if ( psObjectParent == NULL ) {
        KPrint( KVERBOSE, "MODULES", "[%d] Invalid handle\n", nHandle );
        return KMODULE_INVALIDHANDLE;
    }

    // We have a match, decrement reference count and return success
    psObjectParent->m_nReferenceCount--;

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

void ModuleManager_ReleaseHandleInt( uint32 nHandle ) {
    Kg_sKernel.m_psCallStack->eax = ModuleManager_ReleaseHandle( nHandle );
}

static inline uint32 ModuleManager_GetCallID( uint32 nHandle, char *pszCall ) {

    // Lock object manager
    ObjectManager_Lock();

    // Search for module
    K_sObject_t * psObjectParent = ObjectManager_SearchInClassTypeIndex( NULL, KOBJECT_OBJ_MODULE, nHandle );

    // See if we found a module
    if ( psObjectParent == NULL ) {
        KPrint( KVERBOSE, "MODULES", "[%d] Invalid handle\n", nHandle );
        return KMODULE_INVALIDHANDLE;
    }

    // Search for module call
    psObjectParent = ObjectManager_SearchNameInClassTypeIndex( NULL, KOBJECT_OBJ_MODULECALL, pszCall, psObjectParent->m_nTypeIndex );

    // See if we found a module call
    if ( psObjectParent == NULL ) {
        KPrint( KVERBOSE, "MODULES", "[%d]-[%s] Call not found\n", nHandle, pszCall );
        return KMODULE_CALLNOTFOUND;
    }

    // Unlock object manager
    ObjectManager_Unlock();

    return psObjectParent->m_nTypeSubIndex;
}

void ModuleManager_GetCallIDInt( uint32 nHandle, char *pszCall ) {
    Kg_sKernel.m_psCallStack->eax = ModuleManager_GetCallID( nHandle, pszCall );
}

static inline uint32 ModuleManager_Call( uint32 nHandle, uint32 nCode, void *pData ) {

    // Lock object manager
    ObjectManager_Lock();

    // Search for module
    K_sObject_t * psObjectParent = ObjectManager_SearchInClassTypeIndex( NULL, KOBJECT_OBJ_MODULE, nHandle );

    // See if we found a module
    if ( psObjectParent == NULL ) {
        KPrint( KVERBOSE, "MODULES", "[%d] Invalid handle\n", nHandle );
        return KMODULE_INVALIDHANDLE;
    }

    K_sModule_t * psModule = ( K_sModule_t * ) psObjectParent->m_pData;
    ModuleHandler *psModuleHandler = psModule->m_pHandler;

    // Unlock object manager
    ObjectManager_Unlock();

    return psModuleHandler( nCode, pData );
}

void ModuleManager_CallInt( uint32 nHandle, uint32 nCode, void *pData ) {
    Kg_sKernel.m_psCallStack->eax = ModuleManager_Call( nHandle, nCode, pData );
}

uint32 ModuleManager_Load( char *pszFilename ) {

    // Nice simple function, just return the result from the elf loader
    return FS_LoadElf ( pszFilename );
}

