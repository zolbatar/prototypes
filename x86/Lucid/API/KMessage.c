#include <OSCalls.h>
#include <CI-Message.h>

uint32 Message_nHandle;
uint32 Message_nCreateMessagePort;
uint32 Message_nSetMessageDestination;
uint32 Message_nMessageQueueLength;
uint32 Message_nCreateMessage;
uint32 Message_nSendMessage;
uint32 Message_nGetMessage;
uint32 Message_nMessageProcessed;

void KMessage_Init() {

    // Get handle
    Message_nHandle = KModule_GetHandle( "MessageManager" );

    // Get call codes
    Message_nCreateMessagePort = KModule_GetCallID( Message_nHandle, "CreateMessagePort" );
    Message_nSetMessageDestination = KModule_GetCallID( Message_nHandle, "SetMessageDestination" );
    Message_nMessageQueueLength = KModule_GetCallID( Message_nHandle, "MessageQueueLength" );
    Message_nCreateMessage = KModule_GetCallID( Message_nHandle, "CreateMessage" );
    Message_nSendMessage = KModule_GetCallID( Message_nHandle, "SendMessage" );
    Message_nGetMessage = KModule_GetCallID( Message_nHandle, "GetMessage" );
    Message_nMessageProcessed = KModule_GetCallID( Message_nHandle, "MessageProcessed" );
}

uint32 KMessage_CreateMessagePort( char *pszName ) {

    // Check if initialised
    if ( Message_nHandle == NULL )
        KMessage_Init();

    KMessage_sCreateMessagePort_t sData;
    sData.m_pszName = pszName;
    return KModule_Call( Message_nHandle, Message_nCreateMessagePort, &sData );
}

uint32 KMessage_SetMessageDestination( char *pszName ) {

    // Check if initialised
    if ( Message_nHandle == NULL )
        KMessage_Init();

    KMessage_sSetMessageDestination_t sData;
    sData.m_pszName = pszName;
    return KModule_Call( Message_nHandle, Message_nSetMessageDestination, &sData );
}

uint32 KMessage_MessageQueueLength( uint32 *nQueueLength ) {

    // Check if initialised
    if ( Message_nHandle == NULL )
        KMessage_Init();

    KMessage_sMessageQueueLength_t sData;
    uint32 nReturn = KModule_Call( Message_nHandle, Message_nMessageQueueLength, &sData );
    *nQueueLength = sData.m_nLength;
    return nReturn;
}

uint32 KMessage_CreateMessage( uint32 nMessageCode, uint32 nValue ) {

    // Check if initialised
    if ( Message_nHandle == NULL )
        KMessage_Init();

    KMessage_sSendGetMessage_t sData;
    sData.m_nMessageCode = nMessageCode;
    sData.m_nValue = nValue;
    return KModule_Call( Message_nHandle, Message_nCreateMessage, &sData );
}

uint32 KMessage_SendMessage() {

    // Check if initialised
    if ( Message_nHandle == NULL )
        KMessage_Init();

    return KModule_Call( Message_nHandle, Message_nSendMessage, NULL );
}

uint32 Message_GetMessage( Message_t *psMessage ) {

    // Check if initialised
    if ( Message_nHandle == NULL )
        KMessage_Init();

    return KModule_Call( Message_nHandle, Message_nGetMessage, psMessage );
}

uint32 KMessage_MessageProcessed( void ) {

    // Check if initialised
    if ( Message_nHandle == NULL )
        KMessage_Init();

    return KModule_Call( Message_nHandle, Message_nMessageProcessed, NULL );
}



