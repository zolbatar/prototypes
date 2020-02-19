#include <API/Valeo-API.h>

using namespace os;

ProcessManager::ProcessManager() {
    m_nCreateThread = MM_GetCallID( "ProcessManager", "CreateThread" );
    m_nRunThread = MM_GetCallID( "ProcessManager", "RunThread" );
    m_nAwakenThread = MM_GetCallID( "ProcessManager", "AwakenThread" );
    m_nSleep = MM_GetCallID( "ProcessManager", "Sleep" );
    m_nRelinquish = MM_GetCallID( "ProcessManager", "Relinquish" );
}

ProcessManager::~ProcessManager() {}

KStatus ProcessManager::CreateThread( void *nEIP, uint32 *nTID ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterVOIDPTR( &sPackage, nEIP );
    MM_AddParameterUINT32PTR( &sPackage, nTID );
    return MM_Call( m_nCreateThread, &sPackage );
}

KStatus ProcessManager::RunThread( uint32 nTID ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterUINT32( &sPackage, nTID );
    return MM_Call( m_nRunThread, &sPackage );
}

KStatus ProcessManager::AwakenThread( uint32 nTID ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterUINT32( &sPackage, nTID );
    return MM_Call( m_nAwakenThread, &sPackage );
}

KStatus ProcessManager::Sleep( uint32 nTime ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterUINT32( &sPackage, nTime );
    return MM_Call( m_nSleep, &sPackage );
}

KStatus ProcessManager::Relinquish( ) {
    return MM_Call( m_nRelinquish, NULL );
}

