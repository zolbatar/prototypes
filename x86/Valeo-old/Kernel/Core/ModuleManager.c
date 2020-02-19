#include <Kernel.h>

// Prototypes
extern void ModuleManagerGetHandle();
extern void ModuleManagerReleaseHandle();
extern void ModuleManagerGetCallID();
extern void ModuleManagerCall();
extern void ModuleManagerCreateModule();
extern void ModuleManagerCreateModuleCall();

// Lock
sLock_t sModuleLock;

void ModuleManager_LockInit() {
    Lock_Init( "MODULES", &sModuleLock );
}

void ModuleManager_Lock() {
    Lock_Lock( &sModuleLock );
}

void ModuleManager_Unlock() {
    Lock_Unlock( &sModuleLock );
}

void ModuleManager_Init() {

    // Init locking
    ModuleManager_LockInit();

    // Set that no modules are initialised
    g_sKernel.m_nModuleIndex = 0;
    g_sKernel.m_nModuleCallIndex = 0;

    // Attach module handler to interrupts
    Descriptor_SetInterruptGate( 0x80, &ModuleManagerGetCallID );
    Descriptor_SetInterruptGate( 0x81, &ModuleManagerCall );

    // Set module memory to zero fill
    MemoryManager_Page_MapZeroFill( ( uint32 ) g_sKernel.m_pModuleAreaEnd, MM_MODULEAREAPAGES, MM_FLAGS_KERNEL | MM_FLAGS_READWRITE );

    KPrint( "MODULES", "Module manager initialised\n" );
}

KStatus ModuleManager_CreateModule( char *pszModule ) {

    // Construct object path and key
    ObjectManager_Lock();
    ModuleManager_Lock();
    ObjectManager_ConstructPath( "/System/ModuleManager/" );
    ObjectManager_ConstructKey( pszModule );

    // Create object
    sObject_t * psObject = ObjectManager_CreateObject( OM_MODULE, 0 );
    psObject->m_nTypeIndex = g_sKernel.m_nModuleIndex++;
    ObjectManager_Unlock();
    ModuleManager_Unlock();

#ifdef VERBOSEDEBUG

    KPrint( "MODULES", "Module [%s] [%u] created\n", pszModule, psObject->m_nTypeIndex );
#endif

    return NULL;
}

KStatus ModuleManager_CreateModuleCall( char *pszModule, char *pszCallName, ModuleCall *pHandler ) {

    // Search for module
    ObjectManager_Lock();
    ModuleManager_Lock();
    ObjectManager_ConstructPath( "/System/ModuleManager/" );
    ObjectManager_ConstructKey( pszModule );

    sObject_t * psObjectParent = ObjectManager_SearchNameInClass( NULL, OM_MODULE );
    if ( psObjectParent == NULL ) {
        ObjectManager_Unlock();
        ModuleManager_Unlock();
#ifdef VERBOSEDEBUG

        KPrint( "MODULES", "[%s] Module not found\n", pszModule );
#endif

        return MM_INVALIDMODULE;
    }

    // Construct path and key and create object
    ObjectManager_ConstructPath( "/System/ModuleManager/" );
    ObjectManager_ConstructPathAppend( pszModule );
    ObjectManager_ConstructPathAppend( "/" );
    ObjectManager_ConstructKey( pszCallName );
    sObject_t *psObject = ObjectManager_CreateObject( OM_MODULECALL, sizeof( sModuleCall_t ) );
    psObject->m_nTypeIndex = psObjectParent->m_nTypeIndex;
    psObject->m_nTypeSubIndex = g_sKernel.m_nModuleCallIndex++;
    sModuleCall_t * psModuleCall = ( sModuleCall_t * ) psObject->m_pData;
    psModuleCall->m_pHandler = pHandler;
    ObjectManager_Unlock();
    ModuleManager_Unlock();

#ifdef VERBOSEDEBUG

    KPrint( "MODULES", "Module call [%s] [%u-%u] created\n", pszCallName, psObject->m_nTypeIndex, psObject->m_nTypeSubIndex );
#endif

    return NULL;
}

void ModuleManager_GetCallID( sCallStack_t *psStack ) {

    // Get parameters
    ObjectManager_Lock();
    ModuleManager_Lock();
    char *pszModule = ( char * ) psStack->eax;
    char *pszCall = ( char * ) psStack->ebx;

    // Construct path and key and search
    ObjectManager_ConstructPath( "/System/ModuleManager/" );
    ObjectManager_ConstructPathAppend( pszModule );
    ObjectManager_ConstructPathAppend( "/" );
    ObjectManager_ConstructKey( pszCall );
    sObject_t * psObject = ObjectManager_SearchNameInClass( NULL, OM_MODULECALL );
    if ( psObject == NULL ) {
        ModuleManager_Unlock();
        ObjectManager_Unlock();
#ifdef VERBOSEDEBUG

        KPrint( "MODULES", "[%s]-[%s] Call not found\n", pszModule, pszCall );
#endif

        psStack->eax = MM_INVALIDCALLID;
        return ;
    }
    psStack->eax = psObject->m_nTypeSubIndex;
    ModuleManager_Unlock();
    ObjectManager_Unlock();

#ifdef VERBOSEDEBUG

    KPrint( "MODULES", "[%s]-[%s] Call found = 0x%X\n", pszModule, pszCall, psStack->eax );
#endif
}

void ModuleManager_Call( sCallStack_t *psStack ) {

    // Get parameters
    ObjectManager_Lock();
    ModuleManager_Lock();
    uint32 nCode = ( uint32 ) psStack->eax;
    sParameterPackage_t *psParameters = ( sParameterPackage_t * ) psStack->ebx;

    // Set parameter values
    psParameters->m_nCallingProcessID = g_sKernel.m_psRunningProcessID;
    psParameters->m_nCallingThreadID = g_sKernel.m_psRunningThreadID;
    psParameters->m_nCurrentParameter = 0;

    // Search for module call
    sObject_t * psObject = ObjectManager_SearchInClassTypeSubIndex( NULL, OM_MODULECALL, nCode );
    if ( psObject == NULL ) {
        ModuleManager_Unlock();
        ObjectManager_Unlock();
#ifdef VERBOSEDEBUG

        KPrint( "MODULES", "[0x%X] Invalid call ID\n", nCode );
#endif

        psStack->eax = MM_INVALIDCALLID;
        return ;
    }
    sModuleCall_t * psModule = ( sModuleCall_t * ) psObject->m_pData;
    ModuleCall *pCall = psModule->m_pHandler;
    ModuleManager_Unlock();
    ObjectManager_Unlock();
    psStack->eax = pCall( psStack, psParameters );
}

KStatus ModuleManager_Load( char *pszFilename ) {

    // Get current module area position
    void * pStart = g_sKernel.m_pModuleAreaEnd;

    // Load the module into memory
    ModuleEntry * pEntry;
    KStatus nRet = FS_LoadElf ( pszFilename, &g_sKernel.m_pModuleAreaEnd, ( void * ) & pEntry );
    if ( nRet != NULL ) {
#ifdef VERBOSEDEBUG
        KPrint( "FS", "Error loading module [%s]\n", pszFilename );
#endif

        return nRet;
    }

    // Execute entry routine for module
#ifdef VERBOSEDEBUG
    KPrint( "FS", "Module [%s] loaded at 0x%X - 0x%X (Entry 0x%X)\n", pszFilename, pStart, g_sKernel.m_pModuleAreaEnd, pEntry );
#endif

    KStatus nReturn = pEntry();
#ifdef VERBOSEDEBUG

    KPrint( "FS", "Module [%s] init returned = %u\n", pszFilename, nReturn );
#endif

    return NULL;
}

KStatus ModuleManager_Call_CreateModule( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    char * pszModule = MM_GetParameterSTRING( pParameters );
    return ModuleManager_CreateModule( pszModule );
}

KStatus ModuleManager_Call_CreateModuleCall( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    char * pszModule = MM_GetParameterSTRING( pParameters );
    char * pszModuleCall = MM_GetParameterSTRING( pParameters );
    void *pHandler = MM_GetParameterVOIDPTR( pParameters );
    return ModuleManager_CreateModuleCall( pszModule, pszModuleCall, pHandler );
}

void ModuleManager_CreateModuleInterface() {

    // Create module calls
    ModuleManager_CreateModule( "ModuleManager" );
    ModuleManager_CreateModuleCall( "ModuleManager", "CreateModule", &ModuleManager_Call_CreateModule );
    ModuleManager_CreateModuleCall( "ModuleManager", "CreateModuleCall", &ModuleManager_Call_CreateModuleCall );
}

