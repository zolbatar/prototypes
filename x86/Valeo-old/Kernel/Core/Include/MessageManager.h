#ifndef __MESSSAGEMANAGER_H__
#define __MESSSAGEMANAGER_H__

// Main message object structures
typedef struct {
    uint32 m_nType;
    void *m_pData;
    sObject_t *m_psNext;
}
sMessageParameter_t;

typedef struct {
    uint32 m_nMessageCode;	   	   // Message code
    uint32 m_nValue;			   // Value
    sObject_t *m_psParameters;	           // Parameters
    sObject_t *m_psHeadParameter;	   // Last in list
    sObject_t *m_psNext;	   	   // Next message
}
sMessage_t;

// Message port
typedef struct {
    uint32 m_nMessagesWaiting;	   	   // Number of messages in queue
    sObject_t *m_psTail;	   	   // Last event in list (more added on here)
    sObject_t *m_psHead;	   	   // First event in list (taken off here when processed)
    bool m_bProcessingMessage;		   // Are we currently processing message?
    sObject_t *m_psMessage;		   // Current message being constructed
}
sMessagePort_t;

void MessageManager_Init( void );
void MessageManager_CreateModuleInterface( void );

#endif // __MESSSAGEMANAGER_H__
