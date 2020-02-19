#ifndef __IPC_H__
#define __IPC_H__

// Error messages
enum {
    IPC_SUCCESS,
    IPC_PORTALREADYEXISTS,
    IPC_PORTDOESNTEXIST,
    IPC_ALREADYEDITINGMESSAGE
};

// Message port struct
typedef struct {
    uint32 m_nMessagesWaiting;	   	   // Number of messages in queue
    sObject_t *m_psTail;	   	   // Last event in list (more added on here)
    sObject_t *m_psHead;	   	   // First event in list (taken off here when processed)
    bool m_bProcessingMessage;		   // Are we currently processing message?
    sObject_t *m_psMessage;		   // Current message being constructed
}
sMessagePort_t;

// Message struct
typedef struct {
    uint32 m_nMessageCode;	   	   // Message code
    void *m_pData;			   // Serialised data (i.e. parameters)
}
sMessage_t;

void IPC_Init( void );
KStatus IPC_CreatePort( void );
KStatus IPC_GetMessageQueueLength( uint32 *pnLength );
KStatus IPC_CreateMessage( uint32 nMessageCode, void *pData );

#endif // __IPC_H__

