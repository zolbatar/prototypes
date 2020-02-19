#include <Kernel.h>

void MessageManager_Init() {

    // Set kernel variables
    g_sKernel.m_nMessageID = 0;

    // Create module interface
    MessageManager_CreateModuleInterface();

    KPrint( "MESSAGES", "Message manager initialised\n" );
}

KStatus MessageManager_CreateMessagePort( ) {

    // Get thread struct
    ObjectManager_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // See if there is already a message port attached to this thread
    if ( psThread->m_psMessagePort != NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "MESSAGES", "Thread [%u] already has message port, cant create\n", g_sKernel.m_psRunningThreadID );
#endif

        return MeM_PORTALREADYEXISTS;
    }

    // Construct object path and key
    ObjectManager_ConstructPath( "/System/MessageManager/MessagePorts/" );
    char szID[ OM_NAMELENGTH ] = "";
    snprintf( ( char * ) szID, OM_NAMELENGTH, "Thread %u/", g_sKernel.m_psRunningThreadID );
    ObjectManager_ConstructPathAppend( ( char * ) & szID );
    ObjectManager_ConstructKey( "" );

    // Create a message port and attach to thread
    sObject_t * psMessagePortObject = ObjectManager_CreateObject( OM_MESSAGEPORT, sizeof( sMessagePort_t ) );
    psMessagePortObject->m_nTypeIndex = psMessagePortObject->m_nThreadID;
    sMessagePort_t *psMessagePort = ( sMessagePort_t * ) psMessagePortObject->m_pData;
    psMessagePort->m_psHead = NULL;
    psMessagePort->m_psTail = NULL;
    psMessagePort->m_psMessage = NULL;
    psMessagePort->m_nMessagesWaiting = 0;
    psMessagePort->m_bProcessingMessage = false;
    psThread->m_psMessagePort = psMessagePortObject;
    ObjectManager_Unlock();

#ifdef VERBOSEDEBUG

    KPrint( "MESSAGES", "Message port created for thread [%u]\n", psMessagePortObject->m_nThreadID );
#endif

    return NULL;
}

KStatus MessageManager_MessageQueueLength( uint32 *pnLength ) {

    // Get thread struct
    ObjectManager_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Get message port
    sMessagePort_t *psMessagePort = ( sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // See if we have any messages waiting
    *pnLength = psMessagePort->m_nMessagesWaiting;
    ObjectManager_Unlock();
    return NULL;
}

KStatus MessageManager_CreateMessage( uint32 nMessageCode, uint32 nValue ) {

    // Get thread struct
    ObjectManager_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Check there is a message port attached to this thread
    if ( psThread->m_psMessagePort == NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "MESSAGES", "Thread [%u] doesn't have message port, can't create message\n", g_sKernel.m_psRunningThreadID );
#endif

        return MeM_PORTDOESNTEXIST;
    }

    // Get message port
    sMessagePort_t *psMessagePort = ( sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // Check we are not already editing a message
    if ( psMessagePort->m_psMessage != NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "MESSAGES", "Thread [%u] already creating message, can't create message\n", g_sKernel.m_psRunningThreadID );
#endif

        return MeM_ALREADYCREATINGMESSAGE;
    }

    // Construct object path and key
    ObjectManager_ConstructPath( "/System/MessageManager/MessagePorts/" );
    char szID[ OM_NAMELENGTH ] = "";
    snprintf( ( char * ) szID, OM_NAMELENGTH, "Thread %u/n", g_sKernel.m_psRunningThreadID );
    ObjectManager_ConstructPathAppend( ( char * ) & szID );
    snprintf( ( char * ) szID, OM_NAMELENGTH, "Message %u", g_sKernel.m_nMessageID );
    ObjectManager_ConstructKey( ( char * ) & szID );

    // Construct message object
    psMessagePort->m_psMessage = ObjectManager_CreateObject( OM_MESSAGE, sizeof( sMessage_t ) );
    psMessagePort->m_psMessage->m_nTypeIndex = g_sKernel.m_nMessageID;
    sMessage_t * psMessage = ( sMessage_t * ) psMessagePort->m_psMessage->m_pData;
    psMessage->m_nMessageCode = nMessageCode;
    psMessage->m_nValue = nValue;
    psMessage->m_psParameters = NULL;
    psMessage->m_psHeadParameter = NULL;
    ObjectManager_Unlock();

    return NULL;

}

KStatus MessageManager_GetMessagePortThreadID( char *pszDestination, uint32 *nThreadID ) {

    // Get thread struct
    ObjectManager_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Check there is a message port attached to this thread
    if ( psThread->m_psMessagePort == NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "MESSAGES", "Thread [%u] doesn't have message port to link to [%s]\n", g_sKernel.m_psRunningThreadID, pszDestination );
#endif

        return MeM_PORTDOESNTEXIST;
    }

    // Search for destination message port
    ObjectManager_ConstructPath( "/System/MessageManager/MessagePorts/Public/" );
    ObjectManager_ConstructKey( pszDestination );
    sObject_t * psDestinationPortObject = ObjectManager_SearchNameInClass( NULL, OM_MESSAGEPORT );

    // See if there is a message port attached to this thread
    if ( psDestinationPortObject == NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "MESSAGES", "Thread [%u], destination message port [%s] not found\n", g_sKernel.m_psRunningThreadID, pszDestination );
#endif

        return MeM_DESTINATIONPORTNOTFOUND;
    }

    // Set destination
    *nThreadID = psDestinationPortObject->m_nThreadID;
    KPrint( "MESSAGES", "Message port [%s] on thread [%u] found\n", pszDestination, psDestinationPortObject->m_nThreadID );
    ObjectManager_Unlock();
    return NULL;
}

KStatus MessageManager_SendMessage( uint32 nThreadID ) {

    // Search for destination message port
    ObjectManager_Lock();
    sObject_t * psDestinationPortObject = ObjectManager_SearchInClassTypeIndex( NULL, OM_MESSAGEPORT, nThreadID );
    sMessagePort_t *psDestinationMessagePort = ( sMessagePort_t * ) psDestinationPortObject->m_pData;

    // See if there is a message port attached to this thread
    if ( psDestinationPortObject == NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "MESSAGES", "Thread [%u], destination message port [%u] not found\n", g_sKernel.m_psRunningThreadID, nThreadID );
#endif

        return MeM_DESTINATIONPORTNOTFOUND;
    }

    // Get message port
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;
    sMessagePort_t *psMessagePort = ( sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // Check we editing a message we can send
    if ( psMessagePort->m_psMessage == NULL ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "MESSAGES", "Thread [%u] no message created, can't send message\n", g_sKernel.m_psRunningThreadID );
#endif

        return MeM_NOMESSAGETOSEND;
    }

    // Get message
    sObject_t * psMessageObject = psMessagePort->m_psMessage;
    sMessage_t * psMessage = ( sMessage_t * ) psMessageObject->m_pData;

    // Attach to destination message queue
    if ( psDestinationMessagePort->m_psTail == NULL ) {
        psDestinationMessagePort->m_psTail = psMessageObject;
    } else {
        sObject_t *psHeadMessageObject = psDestinationMessagePort->m_psHead;
        sMessage_t * psHeadMessage = ( sMessage_t * ) psHeadMessageObject->m_pData;
        psHeadMessage->m_psNext = psMessageObject;
    }
    psMessage->m_psNext = NULL;
    psDestinationMessagePort->m_psHead = psMessageObject;
    psDestinationMessagePort->m_nMessagesWaiting++;

    // And clear current message
    psMessagePort->m_psMessage = NULL;

    // Unlock object manager
    ObjectManager_Unlock();

    // Awaken destination thread (just in case its asleep waiting for messages)
    ProcessManager_Awaken( psDestinationPortObject->m_nThreadID );

    return NULL;

}

KStatus MessageManager_GetMessage( uint32 *pnMessageCode, uint32 *pnValue ) {

    // Get thread struct
    ObjectManager_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Get message port
    sMessagePort_t *psMessagePort = ( sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // See if we have any messages waiting
    if ( psMessagePort->m_nMessagesWaiting == 0 ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "MESSAGES", "Thread [%u], no messages waiting, can't get message\n", g_sKernel.m_psRunningThreadID );
#endif

        return MeM_DESTINATIONPORTNOTFOUND;
    }

    // Get message object
    sObject_t * psMessageObject = psMessagePort->m_psTail;
    sMessage_t * psMessage = ( sMessage_t * ) psMessageObject->m_pData;

    // Copy data to structure
    *pnMessageCode = psMessage->m_nMessageCode;
    *pnValue = psMessage->m_nValue;
    psMessagePort->m_nMessagesWaiting--;
    psMessagePort->m_bProcessingMessage = true;
    ObjectManager_Unlock();

    return NULL;
}

KStatus MessageManager_MessageProcessed() {

    // Get thread struct
    ObjectManager_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Get message port
    sMessagePort_t *psMessagePort = ( sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // See if we are processing a message
    if ( psMessagePort->m_bProcessingMessage == false ) {
        ObjectManager_Unlock();
#ifdef DEBUG

        KPrint( "MESSAGES", "Thread [%u], not processing message\n", g_sKernel.m_psRunningThreadID );
#endif

        return MeM_DESTINATIONPORTNOTFOUND;
    }

    // Remove message from queue
    sObject_t * psMessageObject = psMessagePort->m_psTail;
    sMessage_t * psMessage = ( sMessage_t * ) psMessageObject->m_pData;
    psMessagePort->m_psTail = psMessage->m_psNext;
    psMessagePort->m_bProcessingMessage = false;
    ObjectManager_DeleteObject( psMessageObject );
    ObjectManager_Unlock();

    return NULL;
}

KStatus MessageManager_Call_CreateMessagePort( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    return MessageManager_CreateMessagePort( );
}

KStatus MessageManager_Call_GetMessagePortThreadID( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    char * pszDestination = MM_GetParameterSTRING( pParameters );
    uint32 * nThreadID = MM_GetParameterUINT32PTR( pParameters );
    return MessageManager_GetMessagePortThreadID( pszDestination, nThreadID );
}

KStatus MessageManager_Call_CreateMessage( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    uint32 nMessageCode = MM_GetParameterUINT32( pParameters );
    uint32 nValue = MM_GetParameterUINT32( pParameters );
    return MessageManager_CreateMessage( nMessageCode, nValue );
}

KStatus MessageManager_Call_GetMessage( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    uint32 * nMessageCode = MM_GetParameterUINT32PTR( pParameters );
    uint32 * nValue = MM_GetParameterUINT32PTR( pParameters );
    return MessageManager_GetMessage( nMessageCode, nValue );
}

KStatus MessageManager_Call_MessageProcessed( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    return MessageManager_MessageProcessed( );
}

KStatus MessageManager_Call_SendMessage( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    uint32 nThreadID = MM_GetParameterUINT32( pParameters );
    return MessageManager_SendMessage( nThreadID );
}

KStatus MessageManager_Call_GetMessageQueueLength( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // Get parameters and call
    uint32 * nMessages = MM_GetParameterUINT32PTR( pParameters );
    return MessageManager_MessageQueueLength( nMessages );
}

void MessageManager_CreateModuleInterface() {

    // Create module calls
    ModuleManager_CreateModule( "MessageManager" );
    ModuleManager_CreateModuleCall( "MessageManager", "CreateMessagePort", &MessageManager_Call_CreateMessagePort );
    ModuleManager_CreateModuleCall( "MessageManager", "CreateMessage", &MessageManager_Call_CreateMessage );
    ModuleManager_CreateModuleCall( "MessageManager", "GetMessage", &MessageManager_Call_GetMessage );
    ModuleManager_CreateModuleCall( "MessageManager", "MessageProcessed", &MessageManager_Call_MessageProcessed );
    ModuleManager_CreateModuleCall( "MessageManager", "SendMessage", &MessageManager_Call_SendMessage );
    ModuleManager_CreateModuleCall( "MessageManager", "GetMessagePortThreadID", &MessageManager_Call_GetMessagePortThreadID );
    ModuleManager_CreateModuleCall( "MessageManager", "GetMessageQueueLength", &MessageManager_Call_GetMessageQueueLength );
}
