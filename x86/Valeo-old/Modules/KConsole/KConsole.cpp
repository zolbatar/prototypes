#include <API/Valeo-API.h>

// Initialise modules used
os::Console *pcConsole = new os::Console();
os::ProcessManager *pcProcessManager = new os::ProcessManager();
os::InterruptManager *pcInterruptManager = new os::InterruptManager();
os::DeviceManager *pcDeviceManager = new os::DeviceManager();
os::MessageManager *pcMessageManager = new os::MessageManager();

// Scratch space
char szScratch[ 1000 ];
char szBuffer[ 1000 ];
uint32 nBufferPos = 0;

extern "C" {
    int snprintf( char * buf, size_t size, const char * fmt, ... );
}

// Prototypes
void KConsole_MessageThread();

int main( ) {

    // Clear console
//    pcConsole->Clear();

    // Show kernel version and welcome
//    uint32 nMajor, nMinor, nRevision;
//    KObject_GetEntityWord( "Kernel/Version(Major)", &nMajor );
//    KObject_GetEntityWord( "Kernel/Version(Minor)", &nMinor );
//    KObject_GetEntityWord( "Kernel/Version(Revision)", &nRevision );
//    snprintf( ( char * ) & szScratch, 1000, "Console (Kernel Version %u.%u.%u)\n\n", nMajor, nMinor, nRevision );
//    KConsole_Print( ( char * ) & szScratch );

    // Show memory size
//    uint32 nMemorySize;
//    KObject_GetEntityWord( "MemoryManager/MemorySize(InPages)", &nMemorySize );
//    snprintf( ( char * ) & szScratch, 1000, "%u Kbytes memory free\n\n", nMemorySize << 2 );
//    KConsole_Print( ( char * ) & szScratch );

    // Create message thread
    uint32 nPID;
    pcProcessManager->CreateThread( (void *)&KConsole_MessageThread, &nPID);
    pcProcessManager->RunThread(nPID);

    // Return success (to keep the module loaded)
    return 1;
}


void KConsole_MessageThread() {

    // Create message port
    pcMessageManager->CreateMessagePort( );
    os::MessagePort *pcMessagePort = new os::MessagePort();

    // Send a request focus command to the keyboard driver
    MMModuleCallID nKeyboardCallRequestFocus = MM_GetCallID( "Keyboard", "RequestFocus" );
    if (MM_Call( nKeyboardCallRequestFocus, NULL ) != NULL) {
       pcConsole->LogPrint( "KCONSOLE", "Error obtaining keyboard focus\n" );
    }

    // Console prompt
    pcConsole->Print( "*" );

    // Loop checking for messages
    while ( 1 ) {

        // Sleep until a message is ready
        uint32 nMessages;
        pcMessagePort->GetMessageQueueLength( &nMessages );
        if ( nMessages == 0 ) {
            pcProcessManager->Sleep(PM_SLEEPFOREVER);
        }

        // Get message
        pcMessagePort->GetMessage();
        switch ( pcMessagePort->m_nMessageCode ) {
        case MeM_KEYPRESS:
            if ( pcMessagePort->m_nValue == 9 ) {
                if ( nBufferPos > 0 ) {
                    szBuffer[ --nBufferPos ] = '\0';
		    pcConsole->DeleteCharacter();
                }
            } else if ( pcMessagePort->m_nValue >= 32 && pcMessagePort->m_nValue <= 127 ) {
                szBuffer[ nBufferPos++ ] = pcMessagePort->m_nValue;
                szBuffer[ nBufferPos ] = '\0';
    		pcConsole->WriteCharacter(pcMessagePort->m_nValue);
            }
            break;
        }
        // And tell message manager it can delete the message
        pcMessagePort->MessageProcessed();
    }
}

