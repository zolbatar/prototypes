#include <API/Valeo-API.h>

using namespace os;

InterruptManager::InterruptManager() {
    m_nEnableInterrupt = MM_GetCallID( "InterruptManager", "EnableInterrupt" );
    m_nAttachHandler = MM_GetCallID( "InterruptManager", "AttachHandler" );
}

InterruptManager::~InterruptManager() {}

KStatus InterruptManager::AttachHandler( char *pszName, uint32 nInterrupt, IRQHandler *pHandler ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterSTRING( &sPackage, pszName );
    MM_AddParameterUINT32( &sPackage, nInterrupt );
    MM_AddParameterVOIDPTR( &sPackage, ( void * ) pHandler );
    return MM_Call( m_nAttachHandler, &sPackage );
}

KStatus InterruptManager::EnableInterrupt( uint32 nInterrupt ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterUINT32( &sPackage, nInterrupt );
    return MM_Call( m_nEnableInterrupt, &sPackage );
}


