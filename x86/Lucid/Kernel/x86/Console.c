// (C) Daryl Dudey 2002

#include <OSCalls.h>
#include <x86.h>
#include <Core.h>
#include <CI-Console.h>

#define CIO_CONSOLEMEMADDR 0xB8000
#define CIO_CONSOLECOLUMNS 80
#define CIO_CONSOLEROWS 25
#define CIO_CONSOLEBUFFER 1024

#define CIO_VGAADDRESSREGISTER 0x3d4
#define CIO_VGADATAREGISTER 0x3d5

// Keep track of screen position
volatile unsigned char *Kg_pConsoleVideo;
int nConsoleX;
int nConsoleY;
uchar n_ConsoleAttr = 7;

// Prototypes
uint32 Console_Handler( uint32 nCode, void *pData );

// Calls
enum {
    CONSOLE_CLEAR,
    CONSOLE_WRITECHARACTER,
    CONSOLE_DELETECHARACTER,
    CONSOLE_PRINT,
    CONSOLE_DEBUGPRINT
};

void Console_Init() {

    Kg_pConsoleVideo = ( unsigned char * ) CIO_CONSOLEMEMADDR;

    // Change cursor shape
    outb( 0x9, CIO_VGAADDRESSREGISTER );
    uchar nCursorSizeMax = inb( CIO_VGADATAREGISTER ) & 0x1f;
    outb( 0xa, CIO_VGAADDRESSREGISTER );
    outb( nCursorSizeMax >> 1, CIO_VGADATAREGISTER );
    outb( 0xb, CIO_VGAADDRESSREGISTER );
    outb( nCursorSizeMax, CIO_VGADATAREGISTER );

    // And clear console
    KClear();
}

void Console_Remap() {

    // Move video memory from 0xB8000 to driver area
    MemoryManager_Lock();
    MemoryManager_Page_Map( CIO_CONSOLEMEMADDR, ( uint32 ) Kg_sKernel.m_pDriverAreaEnd, CIO_CONSOLEMEMPAGES, K_MM_FLAGS_KERNEL | K_MM_FLAGS_READWRITE );
    MemoryManager_Unlock();
    Kg_pConsoleVideo = ( unsigned char * ) Kg_sKernel.m_pDriverAreaEnd;
    Kg_sKernel.m_pDriverAreaEnd += CIO_CONSOLEMEMPAGES << K_MM_PAGESIZESHIFT;
}

void Console_CreateModuleInterface() {
    // Add console to module manager
    ModuleManager_CreateModule( "Console", Console_Handler );
    ModuleManager_CreateModuleCall( "Console", "Clear", CONSOLE_CLEAR );
    ModuleManager_CreateModuleCall( "Console", "WriteCharacter", CONSOLE_WRITECHARACTER );
    ModuleManager_CreateModuleCall( "Console", "DeleteCharacter", CONSOLE_DELETECHARACTER );
    ModuleManager_CreateModuleCall( "Console", "Print", CONSOLE_PRINT );
    ModuleManager_CreateModuleCall( "Console", "DebugPrint", CONSOLE_DEBUGPRINT );
}

void Console_MoveCursor() {
    // Change cursor position on screen
    uint32 nPosition = ( nConsoleY * CIO_CONSOLECOLUMNS ) + nConsoleX;

    outb( 0xf, CIO_VGAADDRESSREGISTER );
    outb( nPosition & 0xFF, CIO_VGADATAREGISTER );
    outb( 0xe, CIO_VGAADDRESSREGISTER );
    outb( ( nPosition >> 8 ) & 0xFF, CIO_VGADATAREGISTER );
}

void KClear() {

    // Clear video memory
    memset( ( void * ) Kg_pConsoleVideo, 0, CIO_CONSOLECOLUMNS * CIO_CONSOLEROWS * 2 );

    // Initialise cursor variables
    nConsoleX = 0;
    nConsoleY = 0;
    Console_MoveCursor();
}

void Console_WriteChar ( uchar c ) {
    if ( c == '\n' || c == '\r' ) {
newline:
        nConsoleX = 0;
        nConsoleY++;
        if ( nConsoleY == CIO_CONSOLEROWS ) {

            // Scroll 1 lines up
            memcpy( ( void * ) Kg_pConsoleVideo, ( void * ) Kg_pConsoleVideo + ( CIO_CONSOLECOLUMNS * 2 )
                    , ( ( CIO_CONSOLEROWS - 1 ) * CIO_CONSOLECOLUMNS * 2 ) );

            // Clear new lines
            memset( ( void * ) Kg_pConsoleVideo + ( ( CIO_CONSOLEROWS - 1 ) * CIO_CONSOLECOLUMNS * 2 ), 0, ( 1 * CIO_CONSOLECOLUMNS * 2 ) );
            nConsoleY --;
        }
        return ;
    }

    *( Kg_pConsoleVideo + ( nConsoleX + nConsoleY * CIO_CONSOLECOLUMNS ) * 2 ) = c & 0xFF;
    *( Kg_pConsoleVideo + ( nConsoleX + nConsoleY * CIO_CONSOLECOLUMNS ) * 2 + 1 ) = n_ConsoleAttr;

    nConsoleX++;
    if ( nConsoleX >= CIO_CONSOLECOLUMNS )
        goto newline;
}

void Console_DeleteChar ( ) {
    nConsoleX--;
    *( Kg_pConsoleVideo + ( nConsoleX + nConsoleY * CIO_CONSOLECOLUMNS ) * 2 ) = 0;
    *( Kg_pConsoleVideo + ( nConsoleX + nConsoleY * CIO_CONSOLECOLUMNS ) * 2 + 1 ) = n_ConsoleAttr;
    Console_MoveCursor();
}

void KPrint( uint32 nSeverity, const char * pszModule, const char * pszFormat, ... ) {

    char pszConsoleBuffer [ CIO_CONSOLEBUFFER ];

    // Decide if we need to print this message or not depending on debug settings
    bool bDoPrint = false;
    if ( nSeverity == KVERBOSE && Kg_sKernel.m_ShowVerbose == true ) {
        bDoPrint = true;
    } else if ( nSeverity == KDEBUG && Kg_sKernel.m_ShowDebug == true ) {
        bDoPrint = true;
    } else if ( nSeverity == KSEVERE ) {
        bDoPrint = true;
    }

    if ( bDoPrint == true ) {

        // Display module
        snprintf( pszConsoleBuffer, CIO_CONSOLEBUFFER, "[%-10s] ", pszModule );
        int i = 0;
        n_ConsoleAttr = 14;
        while ( pszConsoleBuffer[ i ] != 0 ) {
            Console_WriteChar( pszConsoleBuffer[ i++ ] );
        }

        // Use printf to generate buffer
        va_list args;
        va_start( args, pszFormat );
        vsnprintf( pszConsoleBuffer, CIO_CONSOLEBUFFER - 14, pszFormat, args );
        va_end( args );

        // Now put buffer to screen
        i = 0;
        n_ConsoleAttr = 7;
        while ( pszConsoleBuffer[ i ] != 0 ) {
            Console_WriteChar( pszConsoleBuffer[ i++ ] );
        }
    }
    Console_MoveCursor();
}

static inline void Console_DebugPrint( KConsole_sDebugPrint_t *psData ) {
    KPrint( psData->m_nSeverity, psData->m_pszModule, psData->m_pszString );
    Console_MoveCursor();
}

static inline void Console_WriteCharacter( KConsole_sWriteCharacter_t *psData ) {
    Console_WriteChar( psData->m_nChar );
    Console_MoveCursor();
}

uint32 Console_Handler( uint32 nCall, void *pData ) {
    uint32 i;

    switch ( nCall ) {
    case CONSOLE_CLEAR:
        KClear();
        return NULL;
    case CONSOLE_WRITECHARACTER:
        Console_WriteCharacter( ( KConsole_sWriteCharacter_t * ) pData );
        return NULL;
    case CONSOLE_DELETECHARACTER:
        Console_DeleteChar();
        return NULL;
    case CONSOLE_PRINT:
        i = 0;
        n_ConsoleAttr = 7;
        char *pszString = ( char * ) pData;
        while ( pszString[ i ] != 0 ) {
            Console_WriteChar( pszString[ i++ ] );
        }
        return NULL;
    case CONSOLE_DEBUGPRINT:
        Console_DebugPrint ( ( KConsole_sDebugPrint_t * ) pData );
        return NULL;
    }

    return KMODULE_INVALIDCALL;
}



