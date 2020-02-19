#include <sys/io.h>
#include <API/Valeo-API.h>
#include "Keyboard.h"
#include "Keyboard-British.h"

// Initialise modules used
os::Console *pcConsole = new os::Console();
os::ProcessManager *pcProcessManager = new os::ProcessManager();
os::InterruptManager *pcInterruptManager = new os::InterruptManager();
os::DeviceManager *pcDeviceManager = new os::DeviceManager();
os::MessageManager *pcMessageManager = new os::MessageManager();
os::ModuleManager *pcModuleManager = new os::ModuleManager();

#define K_KBD_BUFFERSIZE 256

uchar g_pcKeyboardBuffer [ K_KBD_BUFFERSIZE ];
uint32 g_nKeyboardBufferPos = 0;
uint32 g_nKeyboardBufferEnd = 0;
bool g_nKeyStates[ 128 ];
uint32 g_nWorkerTID;
uint32 g_nThreadFocusID = 0;

// Prototypes
void Shutdown( void );
KStatus Keyboard_Interrupt( sCallStack_t *psStack );
void Keyboard_MessageThread( void );
KStatus Keyboard_Call_RequestFocus( sCallStack_t *psStack, sParameterPackage_t *pParameters );

int main( ) {

    // Clear key states
    uint32 i;
    for ( i = 0;i < 128; i++ ) {
        g_nKeyStates[ i ] = 0;
    }

    // Attach resoureces
    pcDeviceManager->RegisterDevice( "Keyboard" );
    pcDeviceManager->AttachResource( "Keyboard", DM_PORT, 0x60 );
    pcDeviceManager->AttachResource( "Keyboard", DM_PORT, 0x64 );
    pcDeviceManager->AttachResource( "Keyboard", DM_IRQ, 0x1 );

    // Create module interface
    pcModuleManager->CreateModule( "Keyboard" );
    pcModuleManager->CreateModuleCall( "Keyboard", "RequestFocus", &Keyboard_Call_RequestFocus );

    // Attach keyboard to irq 0x1 and enable interrupt
    pcInterruptManager->AttachHandler( "Keyboard", 0x1, &Keyboard_Interrupt );
    pcInterruptManager->EnableInterrupt( 0x1 );

    // Create key processing thread
    pcProcessManager->CreateThread( ( void * ) & Keyboard_MessageThread, &g_nWorkerTID );
    pcProcessManager->RunThread( g_nWorkerTID );

    pcConsole->LogPrint( "KEYBOARD", "Keyboard initialised\n" );

    // Return success (to keep the module loaded)
    return 1;
}

void Shutdown() {

    // Release all module classes
    delete pcConsole;
    delete pcProcessManager;
    delete pcInterruptManager;
    delete pcDeviceManager;
    delete pcMessageManager;
}

void Keyboard_MessageThread() {

    // Create a message port for sending messages
    pcMessageManager->CreateMessagePort( );
    os::MessagePort *pcMessagePort = new os::MessagePort();

    // Wait until a focus request has been made, no point processing otherwise
    while ( g_nThreadFocusID == 0 ) {
        pcProcessManager->Relinquish();
    }

    // Clear the buffer
    g_nKeyboardBufferPos = g_nKeyboardBufferEnd;

    // And loop checking for scan codes
    static bool bExtended = false;
    static uint32 bCapsLock = 0;
    static uint32 bScrollLock = 0;
    static uint32 bNumLock = 0;

    while ( 1 ) {

        // If no scancodes to process or messages then sleep
        while ( g_nKeyboardBufferPos == g_nKeyboardBufferEnd ) {
            pcProcessManager->Sleep( PM_SLEEPFOREVER );
        }

        // Okay, process scancodes and send events as necessary
        while ( g_nKeyboardBufferPos != g_nKeyboardBufferEnd ) {

            bool bStateChange = false;

            // Get scancode from buffer
            uchar nScanCode = g_pcKeyboardBuffer[ g_nKeyboardBufferPos++ ];
            if ( g_nKeyboardBufferPos == K_KBD_BUFFERSIZE ) {
                g_nKeyboardBufferPos = 0;
            }

            // Process key
            uchar nAsciiCode = 0;
            if ( bExtended == false ) {
                if ( nScanCode == 0xE0 ) {
                    bExtended = true;
                } else {

                    // Set up/down state of key
                    bool bOldKeyState = g_nKeyStates[ nScanCode & 0x7f ];
                    if ( nScanCode >= 0x80 ) {
                        g_nKeyStates[ nScanCode & 0x7f ] = false;
                    } else {
                        g_nKeyStates[ nScanCode ] = true;
                    }
                    if ( bOldKeyState != g_nKeyStates[ nScanCode & 0x7f ] )
                        bStateChange = true;

                    // Caps/scroll/num lock change
                    if ( nScanCode >= 0x80 ) {
                        if ( nScanCode == 0xba ) {
                            bCapsLock ^= 1;
                        } else if ( nScanCode == 0xc5 ) {
                            bNumLock ^= 1;
                        } else if ( nScanCode == 0xc6 ) {
                            bScrollLock ^= 1;
                        }

                        // Write keyboard led status
                        //uchar nLEDStatus = ( bCapsLock << 2 ) | ( bNumLock << 1 ) | ( bScrollLock );
                        //while ( inb( 0x64 ) & 0x02 )
                        //    ;
                        //outb( 0xed, 0x60 );
                        //while ( inb( 0x64 ) & 0x02 )
                        //    ;
                        //outb( nLEDStatus, 0x60 );
                        //while ( inb( 0x64 ) & 0x02 )
                        //    ;

                    }
                    // Is shift down?
                    if ( ( g_nKeyStates[ 42 ] == true ) || ( g_nKeyStates[ 54 ] == true ) ) {
                        nAsciiCode = g_nKeyCodesShift[ nScanCode & 0x7f ];
                    } else {
                        nAsciiCode = g_nKeyCodes[ nScanCode & 0x7f ];
                    }

                    // Is caps lock on, if so we need uppercase
                    if ( bCapsLock == 1 ) {
                        if ( nAsciiCode >= 'a' && nAsciiCode <= 'z' )
                            nAsciiCode -= ( 'a' - 'A' );
                    }

                    // Convert if using nunlock
                    if ( bNumLock == true ) {
                        if ( nAsciiCode == MeM_KEY_KEYPAD_HOME )
                            nAsciiCode = '7';
                        else if ( nAsciiCode == MeM_KEY_KEYPAD_UP )
                            nAsciiCode = '8';
                        else if ( nAsciiCode == MeM_KEY_KEYPAD_PGUP )
                            nAsciiCode = '9';
                        else if ( nAsciiCode == MeM_KEY_KEYPAD_LEFT )
                            nAsciiCode = '4';
                        else if ( nAsciiCode == MeM_KEY_KEYPAD_CENTRE )
                            nAsciiCode = '5';
                        else if ( nAsciiCode == MeM_KEY_KEYPAD_RIGHT )
                            nAsciiCode = '6';
                        else if ( nAsciiCode == MeM_KEY_KEYPAD_END )
                            nAsciiCode = '1';
                        else if ( nAsciiCode == MeM_KEY_KEYPAD_DOWN )
                            nAsciiCode = '2';
                        else if ( nAsciiCode == MeM_KEY_KEYPAD_PGDN )
                            nAsciiCode = '3';
                        else if ( nAsciiCode == MeM_KEY_KEYPAD_INS )
                            nAsciiCode = '0';
                    }
                }
            } else if ( bExtended == true ) {
                bExtended = false;
                if ( nScanCode == 0x5B ) {
                    nAsciiCode = MeM_KEY_LEFTWINDOWS;
                } else if ( nScanCode == 0x5C ) {
                    nAsciiCode = MeM_KEY_RIGHTWINDOWS;
                } else if ( nScanCode == 0x5D ) {
                    nAsciiCode = MeM_KEY_MENUPOPUP;
                }
            }

            // Send the message(s)
            if ( nAsciiCode != MeM_KEY_NOKEY && nScanCode < 0x80 ) {
                pcMessagePort->CreateMessage( MeM_KEYPRESS, nAsciiCode );
                pcMessagePort->SendMessage( g_nThreadFocusID );
            }
        }
    }
}

KStatus Keyboard_Interrupt( sCallStack_t *psStack ) {

    // Read in scan code
    uint16 nScancode = inb( 0x60 );

    g_pcKeyboardBuffer[ g_nKeyboardBufferEnd++ ] = nScancode;
    if ( g_nKeyboardBufferEnd == K_KBD_BUFFERSIZE ) {
        g_nKeyboardBufferEnd = 0;
    }

    // Awaken processing thread (if its asleep)
    pcProcessManager->AwakenThread( g_nWorkerTID );

    // Return that we have handled it
    return NULL;
}

KStatus Keyboard_Call_RequestFocus( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {

    // This sets where the keyboard driver send its keypress messages
    g_nThreadFocusID = pParameters->m_nCallingThreadID;
    return NULL;
}

