#include <Kernel.h>

void DeviceManager_Init() {

    // Initialise module calls
    DeviceManager_CreateModuleInterface();

    KPrint( "DEVICE", "Device manager initialised\n" );

}

KStatus DeviceManager_RegisterDevice( char *pszName ) {

    // Construct object path and key
    ObjectManager_Lock();
    ObjectManager_ConstructPath( "/System/DeviceManager/Devices/" );
    ObjectManager_ConstructPathAppend( "/" );
    ObjectManager_ConstructPathAppend( pszName );
    ObjectManager_ConstructKey( "" );

    // Create object
    ObjectManager_CreateObject( OM_DEVICE, 0 );
    ObjectManager_Unlock();

#ifdef VERBOSEDEBUG

    KPrint( "DEVICE", "Device [%s] added\n", pszName );
#endif

    return NULL;
}

KStatus DeviceManager_AttachResource( char *pszName, uint32 nType, uint32 nValue ) {

    // Search for Device device
    ObjectManager_Lock();
    ObjectManager_ConstructPath( "/System/DeviceManager/Devices/" );
    ObjectManager_ConstructKey( pszName );
    sObject_t * psObjectParent = ObjectManager_SearchNameInClass( NULL, OM_DEVICE );

    // See if we found a Device device
    if ( psObjectParent == NULL ) {
        ObjectManager_Unlock();
#ifdef VERBOSEDEBUG

        KPrint( "DEVICE", "[%s] Device device not found\n", pszName );
#endif

        return DM_INVALIDDEVICE;
    }

    // Create resource string
    char szResource[ 32 ];
    switch ( nType ) {
    case DM_PORT:
        snprintf( ( char * ) & szResource, OM_NAMELENGTH, "PORT 0x%X", ( unsigned int ) nValue );
        break;
    case DM_IRQ:
        snprintf( ( char * ) & szResource, OM_NAMELENGTH, "IRQ 0x%X", ( unsigned int ) nValue );
        break;
    case DM_DMA:
        snprintf( ( char * ) & szResource, OM_NAMELENGTH, "DMA 0x%X", ( unsigned int ) nValue );
        break;
    }

    // Construct object path and key
    ObjectManager_ConstructPath( "/System/DeviceManager/Devices/" );
    ObjectManager_ConstructPathAppend( "/" );
    ObjectManager_ConstructPathAppend( pszName );
    ObjectManager_ConstructKey( ( char * ) & szResource );

    // Create object
    sObject_t *psObject = ObjectManager_CreateObject( OM_DEVICERESOURCE , sizeof( sResource_t ) );
    sResource_t *psDevice = ( sResource_t * ) psObject->m_pData;
    psDevice->m_nResourceType = nType;
    psDevice->m_nValue = nValue;
    ObjectManager_Unlock();

#ifdef VERBOSEDEBUG

    KPrint( "DEVICE", "Device [%s] attached resource [%s]\n", pszName, ( char * ) & szResource );
#endif

    return NULL;
}

KStatus DeviceManager_Call_RegisterDevice( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    char * pszName = MM_GetParameterSTRING( pParameters );
    return DeviceManager_RegisterDevice( pszName );
}

KStatus DeviceManager_Call_AttachResource( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    char * pszName = MM_GetParameterSTRING( pParameters );
    uint32 nType = MM_GetParameterUINT32( pParameters );
    uint32 nValue = MM_GetParameterUINT32( pParameters );
    return DeviceManager_AttachResource( pszName, nType, nValue );
}

void DeviceManager_CreateModuleInterface() {

    // Create module calls
    ModuleManager_CreateModule( "DeviceManager" );
    ModuleManager_CreateModuleCall( "DeviceManager", "RegisterDevice", &DeviceManager_Call_RegisterDevice );
    ModuleManager_CreateModuleCall( "DeviceManager", "AttachResource", &DeviceManager_Call_AttachResource );
}
