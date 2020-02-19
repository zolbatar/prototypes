#include <API/Valeo-API.h>

using namespace os;

DeviceManager::DeviceManager() {
    m_nRegisterDevice = MM_GetCallID( "DeviceManager", "RegisterDevice" );
    m_nAttachResource = MM_GetCallID( "DeviceManager", "AttachResource" );
}

DeviceManager::~DeviceManager() {}

KStatus DeviceManager::RegisterDevice( char *pszName ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterSTRING( &sPackage, pszName );
    return MM_Call( m_nRegisterDevice, &sPackage );
}

KStatus DeviceManager::AttachResource( char *pszName, uint32 nType, uint32 nValue ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterSTRING( &sPackage, pszName );
    MM_AddParameterUINT32( &sPackage, nType );
    MM_AddParameterUINT32( &sPackage, nValue );
    return MM_Call( m_nAttachResource, &sPackage );
}


