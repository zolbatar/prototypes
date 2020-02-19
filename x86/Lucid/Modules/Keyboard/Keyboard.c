#include <IOPort.h>
#include <Types.h>
#include <OSCalls.h>
#include <Spinlock.h>
#include "Keyboard.h"
#include "Keyboard-British.h"

// Spinlock
K_sSpinlock_t sLockKeyboard;

#define K_KBD_BUFFERSIZE 256

uchar Kg_pcKeyboardBuffer [ K_KBD_BUFFERSIZE ];
uint32 Kg_nKeyboardBufferPos = 0;
uint32 Kg_nKeyboardBufferEnd = 0;

// Prototypes
bool Keyboard_Interrupt();
void Keyboard_MessageThread();

void Start() {

    // Clear key states
    uint32 i;
    for ( i = 0;i < 128; i++ )
        Kg_nKeyStates[ i ] = 0;

    // Attach keyboard to irq 0x1 and enable interrupt
    KInterrupt_AttachHandler( "Keyboard Controller", 0x1, Keyboard_Interrupt );
    KInterrupt_EnableInterrupt( 0x1 );

    // Attach resoureces
    KDevice_RegisterDevice( "Keyboard Controller" );
    KDevice_AttachResource( "Keyboard Controller", KDEVICE_RES_PORT, 0x60 );
    KDevice_AttachResource( "Keyboard Controller", KDEVICE_RES_PORT, 0x64 );
    KDevice_AttachResource( "Keyboard Controller", KDEVICE_RES_IRQ, 0x1 );

    // Create event producer thread
    KProcess_CreateThread( & Keyboard_MessageThread );

    KConsole_DebugPrint( KDEBUG, "KEYBOARD", "Keyboard initialised\n" );
}

void Keyboard_MessageThread() {

    // Set this thread as an event producer
    KMessage_CreateMessagePort( "Keyboard" );

    // And loop checking for scan codes
    static bool bExtended = false;
    static uint32 bCapsLock = 0;
    static uint32 bScrollLock = 0;
    static uint32 bNumLock = 0;

    while ( 1 ) {

        // Start of critical section
        asm volatile( "cli;" );

        // If no scancodes to process, switch task
        if ( Kg_nKeyboardBufferPos == Kg_nKeyboardBufferEnd ) {
            // End of critical section
            asm volatile( "sti;" );
            KProcess_Relinquish();
            // Restart of critical section
            asm volatile( "cli;" );
        }

        // Okay, process scancodes and send events as necessary
        while ( Kg_nKeyboardBufferPos != Kg_nKeyboardBufferEnd ) {

            bool bStateChange = false;

            // Get scancode from buffer
            uchar nScanCode = Kg_pcKeyboardBuffer[ Kg_nKeyboardBufferPos++ ];
            if ( Kg_nKeyboardBufferPos == K_KBD_BUFFERSIZE ) {
                Kg_nKeyboardBufferPos = 0;
            }

            // Process key
            uchar nAsciiCode = 0;
            if ( bExtended == false ) {
                if ( nScanCode == 0xE0 ) {
                    bExtended = true;
                } else {

                    // Set up/down state of key
                    bool bOldKeyState = Kg_nKeyStates[ nScanCode & 0x7f ];
                    if ( nScanCode >= 0x80 ) {
                        Kg_nKeyStates[ nScanCode & 0x7f ] = false;
                    } else {
                        Kg_nKeyStates[ nScanCode ] = true;
                    }
                    if ( bOldKeyState != Kg_nKeyStates[ nScanCode & 0x7f ] )
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
                        /*uchar nLEDStatus = ( bCapsLock << 2 ) | ( bNumLock << 1 ) | ( bScrollLock );
                        while ( inb( 0x64 ) & 0x02 )
                            ;
                        outb( 0xed, 0x60 );
                        while ( inb( 0x64 ) & 0x02 )
                            ;
                        outb( nLEDStatus, 0x60 );
                        while ( inb( 0x64 ) & 0x02 )
                            ;*/

                    }
                    // Is shift down?
                    if ( ( Kg_nKeyStates[ 42 ] == true ) || ( Kg_nKeyStates[ 54 ] == true ) ) {
                        nAsciiCode = Kg_nKeyCodesShift[ nScanCode & 0x7f ];
                    } else {
                        nAsciiCode = Kg_nKeyCodes[ nScanCode & 0x7f ];
                    }

                    // Is caps lock on, if so we need uppercase
                    if ( bCapsLock == 1 ) {
                        if ( nAsciiCode >= 'a' && nAsciiCode <= 'z' )
                            nAsciiCode -= ( 'a' - 'A' );
                    }

                    // Convert if using nunlock
                    if ( bNumLock == true ) {
                        if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_HOME )
                            nAsciiCode = '7';
                        else if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_UP )
                            nAsciiCode = '8';
                        else if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_PGUP )
                            nAsciiCode = '9';
                        else if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_LEFT )
                            nAsciiCode = '4';
                        else if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_CENTRE )
                            nAsciiCode = '5';
                        else if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_RIGHT )
                            nAsciiCode = '6';
                        else if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_END )
                            nAsciiCode = '1';
                        else if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_DOWN )
                            nAsciiCode = '2';
                        else if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_PGDN )
                            nAsciiCode = '3';
                        else if ( nAsciiCode == KMESSAGE_KEY_KEYPAD_INS )
                            nAsciiCode = '0';
                    }
                }
            } else if ( bExtended == true ) {
                bExtended = false;
                if ( nScanCode == 0x5B ) {
                    nAsciiCode = KMESSAGE_KEY_LEFTWINDOWS;
                } else if ( nScanCode == 0x5C ) {
                    nAsciiCode = KMESSAGE_KEY_RIGHTWINDOWS;
                } else if ( nScanCode == 0x5D ) {
                    nAsciiCode = KMESSAGE_KEY_MENUPOPUP;
                }
            }

            // Send the event(s)
            if ( nAsciiCode != KMESSAGE_KEY_NOKEY ) {
                if ( bStateChange == true ) {
                    if ( nScanCode >= 0x80 ) {
                        KMessage_CreateMessage( KMESSAGE_KEYUP, nAsciiCode );
                        KMessage_SendMessage( );
                    } else {
                        KMessage_CreateMessage( KMESSAGE_KEYPRESS, nAsciiCode );
                        KMessage_SendMessage( );
                        KMessage_CreateMessage( KMESSAGE_KEYDOWN, nAsciiCode );
                        KMessage_SendMessage( );
                    }
                } else {
                    KMessage_CreateMessage( KMESSAGE_KEYDOWN, nAsciiCode );
                    KMessage_SendMessage( );
                    KMessage_CreateMessage( KMESSAGE_KEYPRESS, nAsciiCode );
                    KMessage_SendMessage( );
                }
            }
        }
    }
}

bool Keyboard_Interrupt( ) {

    // Start of critical section
    asm volatile( "cli;" );

    // Read in scan code
    uint16 nScancode = inb( 0x60 );

    Kg_pcKeyboardBuffer[ Kg_nKeyboardBufferEnd++ ] = nScancode;
    if ( Kg_nKeyboardBufferEnd == K_KBD_BUFFERSIZE ) {
        Kg_nKeyboardBufferEnd = 0;
    }

    // End of critical section
    asm volatile( "sti;" );

    // Return that we have handled it
    return true;
}


