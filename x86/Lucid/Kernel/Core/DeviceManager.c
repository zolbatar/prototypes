#include <OSCalls.h>
#include <x86.h>
#include <Core.h>
#include <CI-Device.h>

// Prototypes
uint32 DeviceManager_Handler( uint32 nCall, void *pData );

// Calls
enum {
    REGISTERDEVICE,
    ATTACHRESOURCE
};

void DeviceManager_Init() {

    // Add Device manager to module list
    ModuleManager_CreateModule( "DeviceManager", DeviceManager_Handler );
    ModuleManager_CreateModuleCall( "DeviceManager", "RegisterDevice", REGISTERDEVICE );
    ModuleManager_CreateModuleCall( "DeviceManager", "AttachResource", ATTACHRESOURCE );

    KPrint( KDEBUG, "DEVICE", "Device manager initialised\n" );
}

uint32 DeviceManager_RegisterDevice( char *pszName ) {

    // Create object
    ObjectManager_Lock();
    ObjectManager_CreateObject( KOBJECT_OBJ_DEVICE, 0, pszName );
    ObjectManager_Unlock();

    KPrint( KVERBOSE, "DEVICE", "Device [%s] added\n", pszName );

    return NULL;
}

uint32 DeviceManager_AttachResource( char *pszName, uint32 nType, uint32 nValue ) {

    // Search for Device device
    ObjectManager_Lock();
    K_sObject_t * psObjectParent = ObjectManager_SearchNameInClass( NULL, KOBJECT_OBJ_DEVICE , pszName );

    // See if we found a Device device
    if ( psObjectParent == NULL ) {
        KPrint( KVERBOSE, "DEVICE", "[%s] Device device not found\n", pszName );
        ObjectManager_Unlock();
        return KDEVICE_INVALIDDEVICE;
    }

    // Add object
    K_sObject_t *psObject = ObjectManager_CreateObject( KOBJECT_OBJ_DEVICERESOURCE , sizeof( K_sResource_t ), "" );
    switch ( nType ) {
    case KDEVICE_RES_PORT:
        snprintf( ( char * ) & psObject->m_szName, KOBJECT_NAMELENGTH, "PORT 0x%X", ( unsigned int ) nValue );
        break;
    case KDEVICE_RES_IRQ:
        snprintf( ( char * ) & psObject->m_szName, KOBJECT_NAMELENGTH, "IRQ 0x%X", ( unsigned int ) nValue );
        break;
    case KDEVICE_RES_DMA:
        snprintf( ( char * ) & psObject->m_szName, KOBJECT_NAMELENGTH, "DMA 0x%X", ( unsigned int ) nValue );
        break;
    }

    // Create Device struct
    K_sResource_t *psDevice = ( K_sResource_t * ) psObject->m_pData;
    psDevice->m_nResourceType = nType;
    psDevice->m_nValue = nValue;

    ObjectManager_Unlock();
    return NULL;
}

uint32 DeviceManager_AttachResourceCall( KDevice_sAttachResource_t *psData ) {
    return DeviceManager_AttachResource( psData->m_pszName, psData->m_nType, psData->m_nValue );
}

uint32 DeviceManager_Handler( uint32 nCall, void *pData ) {
    switch ( nCall ) {
    case REGISTERDEVICE:
        return DeviceManager_RegisterDevice( ( char * ) pData );
    case ATTACHRESOURCE:
        return DeviceManager_AttachResourceCall( ( KDevice_sAttachResource_t * ) pData );
    }

    return KMODULE_INVALIDCALL;
}
