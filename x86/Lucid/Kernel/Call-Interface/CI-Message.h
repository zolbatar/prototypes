#ifndef __K_CI_MESSAGE_H__
#define __K_CI_MESSAGE_H__

#include <Types.h>

typedef struct {
    char *m_pszName;
}
KMessage_sCreateMessagePort_t;

typedef struct {
    char *m_pszName;
}
KMessage_sSetMessageDestination_t;

typedef struct {
    uint32 m_nMessageCode;
    uint32 m_nValue;
}
KMessage_sSendGetMessage_t, Message_t ;

typedef struct {
    uint32 m_nLength;
}
KMessage_sMessageQueueLength_t;

#endif // __K_CI_MESSAGE_H__
