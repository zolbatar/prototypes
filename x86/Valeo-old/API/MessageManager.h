#ifndef __API_MESSAGEMANAGER_H__
#define __API_MESSAGEMANAGER_H__

#include <API/Types.h>
#include <API/MessageManager-KeyboardCodes.h>

// Message types
enum {
    MeM_KEYDOWN,
    MeM_KEYUP,
    MeM_KEYPRESS
};

// Errors
#define MeM_PORTALREADYEXISTS 0xFFFFFFFF
#define MeM_PORTDOESNTEXIST 0xFFFFFFFE
#define MeM_DESTINATIONPORTNOTFOUND 0xFFFFFFFD
#define MeM_ALREADYCREATINGMESSAGE 0xFFFFFFFC
#define MeM_NOMESSAGETOSEND 0xFFFFFFFB

#ifndef API_IN_KERNEL
namespace os {

class MessageManager {
public:
    MessageManager();
    ~MessageManager();
    KStatus CreateMessagePort( );
    KStatus GetMessagePortThreadID( char *pszDestination, uint32 *nTID );

private:
    MMModuleCallID m_nCreateMessagePort;
    MMModuleCallID m_nGetMessagePortThreadID;
};

class MessagePort {
public:
    MessagePort();
    ~MessagePort();
    KStatus GetMessage( void );
    KStatus MessageProcessed( void );
    KStatus CreateMessage( uint32 nMessageCode, uint32 nValue );
    KStatus SendMessage( uint32 nTID );
    KStatus GetMessageQueueLength( uint32 *nNumMessagesWaiting );

    uint32 m_nMessageCode;
    uint32 m_nValue;
private:
    MMModuleCallID m_nGetMessage;
    MMModuleCallID m_nMessageProcessed;
    MMModuleCallID m_nCreateMessage;
    MMModuleCallID m_nSendMessage;
    MMModuleCallID m_nGetMessageQueueLength;
};

} // End namespace os
#endif

#endif // __API_MESSAGEMANAGER_H__

