#ifndef __K_KMESSAGE_H__
#define __K_KMESSAGE_H__

#include <KMessage-Keyboard.h>

// Message types
enum {
    KMESSAGE_KEYDOWN,
    KMESSAGE_KEYUP,
    KMESSAGE_KEYPRESS
};

// Message struct
typedef struct {
    uint32 m_nMessageCode;
    uint32 m_nValue;
}
KMessage_t;

#define KMESSAGE_PORTALREADYEXISTS 0xFFFFFFFF
#define KMESSAGE_PORTDOESNTEXIST 0xFFFFFFFE
#define KMESSAGE_DESTINATIONPORTNOTFOUND 0xFFFFFFFD
#define KMESSAGE_ALREADYCREATINGMESSAGE 0xFFFFFFFC
#define KMESSAGE_NOMESSAGETOSEND 0xFFFFFFFB

uint32 KMessage_CreateMessagePort( char *pszName );
uint32 KMessage_SetMessageDestination( char *pszName );
uint32 KMessage_MessageQueueLength( uint32 *nQueueLength );
uint32 KMessage_CreateMessage( uint32 nMessageCode, uint32 nValue );
uint32 KMessage_SendMessage( void );
uint32 KMessage_GetMessage( KMessage_t *psMessage );
uint32 KMessage_MessageProcessed( void );

#endif // __K_KMESSAGE_H__

