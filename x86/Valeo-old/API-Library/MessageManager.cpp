#include <API/Valeo-API.h>

using namespace os;

MessageManager::MessageManager() {
    m_nCreateMessagePort = MM_GetCallID( "MessageManager", "CreateMessagePort" );
    m_nGetMessagePortThreadID = MM_GetCallID( "MessageManager", "GetMessagePortThreadID" );
}

MessageManager::~MessageManager() {}

KStatus MessageManager::CreateMessagePort( ) {
    return MM_Call( m_nCreateMessagePort, NULL );
}

KStatus MessageManager::GetMessagePortThreadID( char *pszDestination, uint32 *nTID ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterSTRING( &sPackage, pszDestination );
    MM_AddParameterUINT32PTR( &sPackage, nTID );
    return MM_Call( m_nGetMessagePortThreadID, &sPackage );
}

MessagePort::MessagePort() {
    m_nCreateMessage = MM_GetCallID( "MessageManager", "CreateMessage" );
    m_nMessageProcessed = MM_GetCallID( "MessageManager", "MessageProcessed" );
    m_nGetMessage = MM_GetCallID( "MessageManager", "GetMessage" );
    m_nSendMessage = MM_GetCallID( "MessageManager", "SendMessage" );
    m_nGetMessageQueueLength = MM_GetCallID( "MessageManager", "GetMessageQueueLength" );
}

MessagePort::~MessagePort() {}

KStatus MessagePort::GetMessage() {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterUINT32PTR( &sPackage, &m_nMessageCode );
    MM_AddParameterUINT32PTR( &sPackage, &m_nValue );
    return MM_Call( m_nGetMessage, &sPackage );
}

KStatus MessagePort::MessageProcessed() {
    return MM_Call( m_nMessageProcessed, NULL );
}

KStatus MessagePort::CreateMessage( uint32 nMessageCode, uint32 nValue ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterUINT32( &sPackage, nMessageCode );
    MM_AddParameterUINT32( &sPackage, nValue );
    return MM_Call( m_nCreateMessage, &sPackage );
}

KStatus MessagePort::SendMessage( uint32 nTID ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterUINT32( &sPackage, nTID );
    return MM_Call( m_nSendMessage, &sPackage );
}

KStatus MessagePort::GetMessageQueueLength( uint32 *nNumMessagesWaiting ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterUINT32PTR( &sPackage, nNumMessagesWaiting );
    return MM_Call( m_nGetMessageQueueLength, &sPackage );
}

