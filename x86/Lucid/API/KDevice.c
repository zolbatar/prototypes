#include <OSCalls.h>
#include <CI-Device.h>

uint32 Device_nHandle;
uint32 Device_nRegisterDevice;
uint32 Device_nAttachResource;

void KDevice_Init() {

    // Get handle
    Device_nHandle = KModule_GetHandle( "DeviceManager" );

    // Get call codes
    Device_nRegisterDevice = KModule_GetCallID( Device_nHandle, "RegisterDevice" );
    Device_nAttachResource = KModule_GetCallID( Device_nHandle, "AttachResource" );
}

void KDevice_RegisterDevice( char *pszName ) {

    // Check if initialised
    if ( Device_nHandle == NULL )
        KDevice_Init();

    KModule_Call( Device_nHandle, Device_nRegisterDevice, pszName );
}

void KDevice_AttachResource( char *pszName, uint32 m_nType, uint32 m_nValue ) {

    // Check if initialised
    if ( Device_nHandle == NULL )
        KDevice_Init();

    KDevice_sAttachResource_t sData;
    sData.m_pszName = pszName;
    sData.m_nType = m_nType;
    sData.m_nValue = m_nValue;
    KModule_Call( Device_nHandle, Device_nAttachResource, &sData );
}

