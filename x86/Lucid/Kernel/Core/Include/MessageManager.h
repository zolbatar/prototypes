#ifndef __K_MESSSAGEMANAGER_H__
#define __K_MESSSAGEMANAGER_H__

#include <Types.h>

// Main message object structures
typedef struct {
    uint32 m_nType;
    void *m_pData;
    K_sObject_t *m_psNext;
}
K_sMessageParameter_t;

typedef struct {
    uint32 m_nMessageCode;	   	   // Message code
    uint32 m_nValue;			   // Value
    K_sObject_t *m_psParameters;	   // Parameters
    K_sObject_t *m_psHeadParameter;	   // Last in list
    K_sObject_t *m_psNext;	   	   // Next message
}
K_sMessage_t;

// Message port
typedef struct {
    uint32 m_nMessagesWaiting;	   	   // Number of messages in queue
    K_sObject_t *m_psTail;	   	   // Last event in list (more added on here)
    K_sObject_t *m_psHead;	   	   // First event in list (taken off here when processed)
    K_sObject_t *m_psMessageDestination;
    bool m_bProcessingMessage;		   // Are we currently processing message?
    K_sObject_t *m_psMessage;		   // Current message being constructed
}
K_sMessagePort_t;

void MessageManager_Init( void );

#endif // __K_MESSSAGEMANAGER_H__
