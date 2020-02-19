#include <Types.h>
#include <Printf.h>
#include <IOPort.h>
#include <OSCalls.h>

// Scratch space
char szScratch[ 1000 ];
char szBuffer[ 1000 ];
uint32 nBufferPos = 0;

void KConsole_MessageThread();

void Start() {

    // Clear console
    //LucidConsole_Clear();

    // Show kernel version and welcome
    uint32 nMajor, nMinor, nRevision;
    KObject_GetEntityWord( "Kernel/Version(Major)", &nMajor );
    KObject_GetEntityWord( "Kernel/Version(Minor)", &nMinor );
    KObject_GetEntityWord( "Kernel/Version(Revision)", &nRevision );
    snprintf( ( char * ) & szScratch, 1000, "Console (Kernel Version %u.%u.%u)\n\n", nMajor, nMinor, nRevision );
    KConsole_Print( ( char * ) & szScratch );

    // Show memory size
    uint32 nMemorySize;
    KObject_GetEntityWord( "MemoryManager/MemorySize(InPages)", &nMemorySize );
    snprintf( ( char * ) & szScratch, 1000, "%u Kbytes memory free\n\n", nMemorySize << 2 );
    KConsole_Print( ( char * ) & szScratch );

    // Create event consumer thread
    KProcess_CreateThread( & KConsole_MessageThread );

    // Show prompt
    KConsole_Print( "*" );

    while ( 1 ) {}
}

void KConsole_MessageThread() {

    // Set this thread as an event consumer
    KMessage_CreateMessagePort( "Kernel Console" );
    KMessage_SetMessageDestination( "Keyboard" );

    // And loop checking for events
    KMessage_t sMessage;
    while ( 1 ) {

        // Sleep until a message is ready
        uint32 nMessages;
        KMessage_MessageQueueLength( &nMessages );
        if ( nMessages == 0 ) {
            KProcess_Sleep( KPROCESS_SLEEPFOREVER );
        }

        // Get message
        KMessage_GetMessage( &sMessage );
        switch ( sMessage.m_nMessageCode ) {
        case KMESSAGE_KEYPRESS:
            if ( sMessage.m_nValue == 9 ) {
                if ( nBufferPos > 0 ) {
                    LucidConsole_DeleteCharacter();
                    szBuffer[ --nBufferPos ] = '\0';
                }
            } else if ( sMessage.m_nValue >= 32 && sMessage.m_nValue <= 127 ) {
                szBuffer[ nBufferPos++ ] = sMessage.m_nValue;
                szBuffer[ nBufferPos ] = '\0';
                KConsole_WriteCharacter( ( uchar ) sMessage.m_nValue );
            }
            break;
        }
        // And tell message manager it can delete the message
        KMessage_MessageProcessed();
    }
}

