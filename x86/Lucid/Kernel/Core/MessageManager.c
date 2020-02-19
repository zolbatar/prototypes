#include <OSCalls.h>
#include <x86.h>
#include <Core.h>
#include <CI-Message.h>

// Prototypes
uint32 MessageManager_Handler( uint32 nCall, void * pData );

// Calls
enum {
    CREATEMESSAGEPORT,
    SETMESSAGEDESTINATION,
    MESSAGEQUEUELENGTH,
    CREATEMESSAGE,
    SENDMESSAGE,
    GETMESSAGE,
    MESSAGEPROCESSED
};

void MessageManager_Init() {
    // Add interrupt manager to module list
    ModuleManager_CreateModule( "MessageManager", MessageManager_Handler );
    ModuleManager_CreateModuleCall( "MessageManager", "CreateMessagePort", CREATEMESSAGEPORT );
    ModuleManager_CreateModuleCall( "MessageManager", "SetMessageDestination", SETMESSAGEDESTINATION );
    ModuleManager_CreateModuleCall( "MessageManager", "MessageQueueLength", MESSAGEQUEUELENGTH );
    ModuleManager_CreateModuleCall( "MessageManager", "CreateMessage", CREATEMESSAGE );
    ModuleManager_CreateModuleCall( "MessageManager", "SendMessage", SENDMESSAGE );
    ModuleManager_CreateModuleCall( "MessageManager", "GetMessage", GETMESSAGE );
    ModuleManager_CreateModuleCall( "MessageManager", "MessageProcessed", MESSAGEPROCESSED );

    KPrint( KDEBUG, "MESSAGES", "Message manager initialised\n" );
}

uint32 MessageManager_CreateMessagePort( KMessage_sCreateMessagePort_t *psData ) {

    // Lock object manager
    ObjectManager_Lock();

    // Get thread struct
    K_sThread_t * psThread = ( K_sThread_t * ) Kg_sKernel.m_psRunningThread->m_pData;

    // See if there is already a message port attached to this thread
    if ( psThread->m_psMessagePort != NULL ) {
        KPrint( KVERBOSE, "MESSAGES", "Thread [%u] already has message port while creating [%s]\n", Kg_sKernel.m_psRunningThreadID, psData->m_pszName );
        ObjectManager_Unlock();
        return KMESSAGE_PORTALREADYEXISTS;
    }

    // Create a message port and attach to thread
    K_sObject_t * psMessagePortObject = ObjectManager_CreateObject( KOBJECT_OBJ_MESSAGEPORT, sizeof( K_sMessagePort_t ), psData->m_pszName );
    psMessagePortObject->m_nTypeIndex = Kg_sKernel.m_psRunningThreadID;
    K_sMessagePort_t *psMessagePort = ( K_sMessagePort_t * ) psMessagePortObject->m_pData;
    psMessagePort->m_psHead = NULL;
    psMessagePort->m_psTail = NULL;
    psMessagePort->m_psMessage = NULL;
    psMessagePort->m_nMessagesWaiting = 0;
    psMessagePort->m_bProcessingMessage = false;
    psThread->m_psMessagePort = psMessagePortObject;

    // And unlock object manager
    ObjectManager_Unlock();

    KPrint( KVERBOSE, "MESSAGES", "Message port created [%s] for thread [%u]\n", psData->m_pszName, psMessagePortObject->m_nThreadID );
    return NULL;
}

uint32 MessageManager_SetMessageDestination( KMessage_sSetMessageDestination_t *psData ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Get thread struct
    K_sThread_t * psThread = ( K_sThread_t * ) Kg_sKernel.m_psRunningThread->m_pData;

    // Check there is a message port attached to this thread
    if ( psThread->m_psMessagePort == NULL ) {
        KPrint( KVERBOSE, "MESSAGES", "Thread [%u] doesn't have message port to link to [%s]\n", Kg_sKernel.m_psRunningThreadID, psData->m_pszName );
        ObjectManager_Unlock();
        return KMESSAGE_PORTDOESNTEXIST;
    }

    // Search for destination message port
    K_sObject_t * psDestinationPortObject = ObjectManager_SearchNameInClass( NULL, KOBJECT_OBJ_MESSAGEPORT, psData->m_pszName );

    // See if there is already a message port attached to this thread
    if ( psDestinationPortObject == NULL ) {
        KPrint( KVERBOSE, "MESSAGES", "Thread [%u], destination message port [%s] not found\n", Kg_sKernel.m_psRunningThreadID, psData->m_pszName );
        ObjectManager_Unlock();
        return KMESSAGE_DESTINATIONPORTNOTFOUND;
    }

    // Set destination
    K_sMessagePort_t *psMessagePort = ( K_sMessagePort_t * ) psDestinationPortObject->m_pData;
    psMessagePort->m_psMessageDestination = psThread->m_psMessagePort;

    KPrint( KVERBOSE, "MESSAGES", "Message port on thread [%u] link to destination [%s]\n", psDestinationPortObject->m_nThreadID, psData->m_pszName );

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

uint32 MessageManager_MessageQueueLength( KMessage_sMessageQueueLength_t *psData ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Get thread struct
    K_sThread_t * psThread = ( K_sThread_t * ) Kg_sKernel.m_psRunningThread->m_pData;

    // Get message port
    K_sMessagePort_t *psMessagePort = ( K_sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // See if we have any messages waiting
    if ( psMessagePort->m_nMessagesWaiting == 0 ) {
        psData->m_nLength = 0;
        ObjectManager_Unlock();
        return NULL;
    }

    // Get message object and count all messages
    psData->m_nLength = 0;
    K_sObject_t * psMessageObject = psMessagePort->m_psTail;
    K_sMessage_t * psMessage = ( K_sMessage_t * ) psMessageObject->m_pData;
    while ( psMessageObject != NULL ) {
        psData->m_nLength++;
        psMessageObject = psMessage->m_psNext;
        psMessage = ( K_sMessage_t * ) psMessageObject->m_pData;
    }

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

uint32 MessageManager_CreateMessage( KMessage_sSendGetMessage_t *psData ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Get thread struct
    K_sThread_t * psThread = ( K_sThread_t * ) Kg_sKernel.m_psRunningThread->m_pData;

    // Check there is a message port attached to this thread
    if ( psThread->m_psMessagePort == NULL ) {
        KPrint( KVERBOSE, "MESSAGES", "Thread [%u] doesn't have message port, can't create message\n", Kg_sKernel.m_psRunningThreadID );
        ObjectManager_Unlock();
        return KMESSAGE_PORTDOESNTEXIST;
    }

    // Get message port
    K_sMessagePort_t *psMessagePort = ( K_sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // Check we are not already editing a message
    if ( psMessagePort->m_psMessage != NULL ) {
        KPrint( KVERBOSE, "MESSAGES", "Thread [%u] already creating message, can't create message\n", Kg_sKernel.m_psRunningThreadID );
        ObjectManager_Unlock();
        return KMESSAGE_ALREADYCREATINGMESSAGE;
    }

    // Construct message object
    psMessagePort->m_psMessage = ObjectManager_CreateObject( KOBJECT_OBJ_MESSAGE, sizeof( K_sMessage_t ), "Message" );
    psMessagePort->m_psMessage->m_nTypeIndex = Kg_sKernel.m_psRunningThreadID;
    K_sMessage_t * psMessage = ( K_sMessage_t * ) psMessagePort->m_psMessage->m_pData;
    psMessage->m_nMessageCode = psData->m_nMessageCode;
    psMessage->m_nValue = psData->m_nValue;
    psMessage->m_psParameters = NULL;
    psMessage->m_psHeadParameter = NULL;

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;

}

uint32 MessageManager_SendMessage( ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Get thread struct
    K_sThread_t * psThread = ( K_sThread_t * ) Kg_sKernel.m_psRunningThread->m_pData;

    // Get message port
    K_sMessagePort_t *psMessagePort = ( K_sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // Check we editing a message we can send
    if ( psMessagePort->m_psMessage == NULL ) {
        KPrint( KVERBOSE, "MESSAGES", "Thread [%u] no message created, can't send message\n", Kg_sKernel.m_psRunningThreadID );
        ObjectManager_Unlock();
        return KMESSAGE_NOMESSAGETOSEND;
    }

    // Check the destination port is valid
    if ( psMessagePort->m_psMessageDestination == NULL ) {
        KPrint( KVERBOSE, "MESSAGES", "Thread [%u], destination message port not found, can't send message\n", Kg_sKernel.m_psRunningThreadID );
        ObjectManager_Unlock();
        return KMESSAGE_DESTINATIONPORTNOTFOUND;
    }

    // Set destination message port
    K_sObject_t * psDestinationMessagePortObject = psMessagePort->m_psMessageDestination;
    K_sMessagePort_t *psDestinationMessagePort = ( K_sMessagePort_t * ) psDestinationMessagePortObject->m_pData;

    // Construct message object
    K_sObject_t * psMessageObject = psMessagePort->m_psMessage;
    K_sMessage_t * psMessage = ( K_sMessage_t * ) psMessageObject->m_pData;

    // Attach to destination message queue
    if ( psDestinationMessagePort->m_psTail == NULL ) {
        psDestinationMessagePort->m_psTail = psMessageObject;
    } else {
        K_sObject_t *psHeadMessageObject = psDestinationMessagePort->m_psHead;
        K_sMessage_t * psHeadMessage = ( K_sMessage_t * ) psHeadMessageObject->m_pData;
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
    ProcessManager_Awaken( psDestinationMessagePortObject->m_nThreadID );

    return NULL;

}

uint32 MessageManager_GetMessage( KMessage_sSendGetMessage_t *psData ) {

    // Lock object manager first
    ObjectManager_Lock();

    // Get thread struct
    K_sThread_t * psThread = ( K_sThread_t * ) Kg_sKernel.m_psRunningThread->m_pData;

    // Get message port
    K_sMessagePort_t *psMessagePort = ( K_sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // See if we have any messages waiting
    if ( psMessagePort->m_nMessagesWaiting == 0 ) {
        KPrint( KVERBOSE, "MESSAGES", "Thread [%u], no messages waiting, can't get message\n", Kg_sKernel.m_psRunningThreadID );
        psData->m_nValue = 0;
        ObjectManager_Unlock();
        return KMESSAGE_DESTINATIONPORTNOTFOUND;
    }

    // Get message object
    K_sObject_t * psMessageObject = psMessagePort->m_psTail;
    K_sMessage_t * psMessage = ( K_sMessage_t * ) psMessageObject->m_pData;

    // Copy data to structure
    psData->m_nMessageCode = psMessage->m_nMessageCode;
    psData->m_nValue = psMessage->m_nValue;
    psMessagePort->m_nMessagesWaiting--;
    psMessagePort->m_bProcessingMessage = true;

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

uint32 MessageManager_MessageProcessed() {

    // Lock object manager first
    ObjectManager_Lock();

    // Get thread struct
    K_sThread_t * psThread = ( K_sThread_t * ) Kg_sKernel.m_psRunningThread->m_pData;

    // Get message port
    K_sMessagePort_t *psMessagePort = ( K_sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // See if we are processing a message
    if ( psMessagePort->m_bProcessingMessage == false ) {
        KPrint( KVERBOSE, "MESSAGES", "Thread [%u], not processing message\n", Kg_sKernel.m_psRunningThreadID );
        ObjectManager_Unlock();
        return KMESSAGE_DESTINATIONPORTNOTFOUND;
    }

    // Get message object
    K_sObject_t * psMessageObject = psMessagePort->m_psTail;
    K_sMessage_t * psMessage = ( K_sMessage_t * ) psMessageObject->m_pData;

    // Remove message from message list attached to message port and free memory
    psMessagePort->m_psTail = psMessage->m_psNext;

    // Clear message port processing status
    psMessagePort->m_bProcessingMessage = false;

    // Delete message from object manager
    ObjectManager_DeleteObject( psMessageObject );

    // Unlock object manager
    ObjectManager_Unlock();

    return NULL;
}

uint32 MessageManager_Handler( uint32 nCall, void * pData ) {
    switch ( nCall ) {
    case CREATEMESSAGEPORT:
        return MessageManager_CreateMessagePort( ( KMessage_sCreateMessagePort_t * ) pData );
    case SETMESSAGEDESTINATION:
        return MessageManager_SetMessageDestination( ( KMessage_sSetMessageDestination_t * ) pData );
    case MESSAGEQUEUELENGTH:
        return MessageManager_MessageQueueLength( ( KMessage_sMessageQueueLength_t * ) pData );
    case CREATEMESSAGE:
        return MessageManager_CreateMessage( ( KMessage_sSendGetMessage_t * ) pData );
    case SENDMESSAGE:
        return MessageManager_SendMessage( );
    case GETMESSAGE:
        return MessageManager_GetMessage( ( KMessage_sSendGetMessage_t * ) pData );
    case MESSAGEPROCESSED:
        return MessageManager_MessageProcessed( );
    }

    return KMODULE_INVALIDCALL;
}

