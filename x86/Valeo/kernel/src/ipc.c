#include <Kernel.h>

void IPC_Init() {

    // Initialise kernel vars
    g_sKernel.m_nMessageID = 0;

    // Create the object directory /System/"Message Ports" and /System/"Messages" and object types
    Object_Lock();
    g_sKernel.m_psSystemMessagePorts = Object_CreateDirectory( g_sKernel.m_psSystemRoot, "Message Ports" );
    g_sKernel.m_psSystemMessages = Object_CreateDirectory( g_sKernel.m_psSystemRoot, "Messages" );
    g_sKernel.m_nTypeMessagePort = Object_CreateType( "Message Ports" );
    g_sKernel.m_nTypeMessages = Object_CreateType( "Messages" );
    Object_Unlock();
}

KStatus IPC_CreatePort( ) {

    // Get thread struct
    Object_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // See if there is already a message port attached to this thread
    if ( psThread->m_psMessagePort != NULL ) {
        Object_Unlock();
#ifdef DEBUG

        Syslog_Lock();
        Syslog_Entry( "IPC", "Thread %lu already has message port\n", g_sKernel.m_psRunningThreadID );
        Syslog_Unlock();
#endif

        return IPC_PORTALREADYEXISTS;
    }

    // Create a message port and attach to thread
    char szID[ OBJECT_NAMELENGTH ];
    snprintf( ( char * ) szID, OBJECT_NAMELENGTH, "Thread %lu", g_sKernel.m_psRunningThreadID );
    sObject_t * psMessagePortObject = Object_CreateObject( g_sKernel.m_psSystemMessagePorts, g_sKernel.m_nTypeMessagePort, ( char * ) & szID, sizeof( sMessagePort_t ) );
    sMessagePort_t *psMessagePort = ( sMessagePort_t * ) psMessagePortObject->m_pData;
    psMessagePort->m_psHead = NULL;
    psMessagePort->m_psTail = NULL;
    psMessagePort->m_psMessage = NULL;
    psMessagePort->m_nMessagesWaiting = 0;
    psMessagePort->m_bProcessingMessage = false;
    psThread->m_psMessagePort = psMessagePortObject;
    Object_Unlock();

#ifdef DEBUG

    Syslog_Lock();
    Syslog_Entry( "IPC", "Message port created for thread %lu\n", g_sKernel.m_psRunningThreadID );
    Syslog_Unlock();
#endif

    return IPC_SUCCESS;
}

KStatus IPC_GetMessageQueueLength( uint32 *pnLength ) {

    // Get thread struct
    Object_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Get message port
    sMessagePort_t *psMessagePort = ( sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // See if we have any messages waiting
    *pnLength = psMessagePort->m_nMessagesWaiting;
    Object_Unlock();

    return IPC_SUCCESS;
}

KStatus IPC_CreateMessage( uint32 nMessageCode, void *pData ) {

    // Get thread struct
    Object_Lock();
    sObject_t *psThreadObject = g_sKernel.m_psRunningThread;
    sThread_t * psThread = ( sThread_t * ) psThreadObject->m_pData;

    // Check there is a message port attached to this thread
    if ( psThread->m_psMessagePort == NULL ) {
        Object_Unlock();
#ifdef DEBUG

        Syslog_Lock();
        Syslog_Entry( "IPC", "Thread %lu doesn't have message port, can't create message\n", g_sKernel.m_psRunningThreadID );
        Syslog_Unlock();
#endif

        return IPC_PORTDOESNTEXIST;
    }

    // Get message port
    sMessagePort_t *psMessagePort = ( sMessagePort_t * ) psThread->m_psMessagePort->m_pData;

    // Check we are not already editing a message
    if ( psMessagePort->m_psMessage != NULL ) {
        Object_Unlock();
#ifdef DEBUG

        Syslog_Lock();
        Syslog_Entry( "IPC", "Thread %lu already creating message, can't create message\n", g_sKernel.m_psRunningThreadID );
        Syslog_Unlock();
#endif

        return IPC_ALREADYEDITINGMESSAGE;
    }

    // Construct message object
    char szID[ OBJECT_NAMELENGTH ];
    snprintf( ( char * ) szID, OBJECT_NAMELENGTH, "Message %lu", g_sKernel.m_nMessageID );
    psMessagePort->m_psMessage = Object_CreateObject( g_sKernel.m_psSystemMessages, g_sKernel.m_nTypeMessages, ( char * ) & szID, sizeof( sMessage_t ) );
    sMessage_t * psMessage = ( sMessage_t * ) psMessagePort->m_psMessage->m_pData;
    psMessage->m_nMessageCode = nMessageCode;
    psMessage->m_pData = pData;
    Object_Unlock();

    // Next message ID
    g_sKernel.m_nMessageID++;

    return IPC_SUCCESS;
}

