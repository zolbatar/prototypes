#include <Kernel.h>

#define CIO_CONSOLEMEMADDR 0xB8000
#define CIO_CONSOLEMEMPAGES 0x8
#define CIO_CONSOLECOLUMNS 80
#define CIO_CONSOLEROWS 25
#define CIO_CONSOLEBUFFER 1024

#define CIO_VGAADDRESSREGISTER 0x3d4
#define CIO_VGADATAREGISTER 0x3d5

// Keep track of screen position
volatile unsigned char *g_pConsoleVideo;
int nConsoleX;
int nConsoleY;
uchar nConsoleAttr = 7;

void Console_Init() {

    g_pConsoleVideo = ( unsigned char * ) CIO_CONSOLEMEMADDR;

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
    MemoryManager_Page_Map( CIO_CONSOLEMEMADDR, ( uint32 ) g_sKernel.m_pDriverAreaEnd, CIO_CONSOLEMEMPAGES, MM_FLAGS_KERNEL | MM_FLAGS_READWRITE );
    MemoryManager_Unlock();
    g_pConsoleVideo = ( unsigned char * ) g_sKernel.m_pDriverAreaEnd;
    g_sKernel.m_pDriverAreaEnd += CIO_CONSOLEMEMPAGES << MM_PAGESIZESHIFT;
}

void Console_MoveCursor() {

    // Change cursor position on screen
    uint32 nPosition = ( nConsoleY * CIO_CONSOLECOLUMNS ) + nConsoleX;

    outb( 0xf, CIO_VGAADDRESSREGISTER );
    outb( nPosition & 0xFF, CIO_VGADATAREGISTER );
    outb( 0xe, CIO_VGAADDRESSREGISTER );
    outb( ( nPosition >> 8 ) & 0xFF, CIO_VGADATAREGISTER );
}

KStatus KClear() {

    // Clear video memory
    memset( ( void * ) g_pConsoleVideo, 0, CIO_CONSOLECOLUMNS * CIO_CONSOLEROWS * 2 );

    // Initialise cursor variables
    nConsoleX = 0;
    nConsoleY = 0;
    Console_MoveCursor();

    return NULL;
}

KStatus Console_WriteChar ( uchar c ) {

    // Write character at cursor and scroll etc. as needed
    if ( c == '\n' || c == '\r' ) {
newline:
        nConsoleX = 0;
        nConsoleY++;
        if ( nConsoleY == CIO_CONSOLEROWS ) {

            // Scroll 1 lines up
            memcpy( ( void * ) g_pConsoleVideo, ( void * ) g_pConsoleVideo + ( CIO_CONSOLECOLUMNS * 2 )
                    , ( ( CIO_CONSOLEROWS - 1 ) * CIO_CONSOLECOLUMNS * 2 ) );

            // Clear new lines
            memset( ( void * ) g_pConsoleVideo + ( ( CIO_CONSOLEROWS - 1 ) * CIO_CONSOLECOLUMNS * 2 ), 0, ( 1 * CIO_CONSOLECOLUMNS * 2 ) );
            nConsoleY --;
        }
        Console_MoveCursor();
        return NULL;
    }

    *( g_pConsoleVideo + ( nConsoleX + nConsoleY * CIO_CONSOLECOLUMNS ) * 2 ) = c & 0xFF;
    *( g_pConsoleVideo + ( nConsoleX + nConsoleY * CIO_CONSOLECOLUMNS ) * 2 + 1 ) = nConsoleAttr;

    nConsoleX++;
    if ( nConsoleX >= CIO_CONSOLECOLUMNS ) {
        goto newline;
    }
    Console_MoveCursor();
    return NULL;
}

KStatus Console_DeleteChar ( ) {

    // Delete character at cursor
    nConsoleX--;
    *( g_pConsoleVideo + ( nConsoleX + nConsoleY * CIO_CONSOLECOLUMNS ) * 2 ) = 0;
    *( g_pConsoleVideo + ( nConsoleX + nConsoleY * CIO_CONSOLECOLUMNS ) * 2 + 1 ) = nConsoleAttr;
    Console_MoveCursor();
    return NULL;
}

KStatus KPrint( char * pszModule, const char * pszFormat, ... ) {

    char pszConsoleBuffer [ CIO_CONSOLEBUFFER ];

    // Display module (if wanted)
    uint32 i;
    if ( pszModule != NULL ) {
        snprintf( ( char * ) & pszConsoleBuffer, CIO_CONSOLEBUFFER , "[%-10s] ", pszModule );
        i = 0;
        nConsoleAttr = 14;
        while ( pszConsoleBuffer[ i ] != 0 ) {
            Console_WriteChar( pszConsoleBuffer[ i++ ] );
        }
    }

    // Use printf to generate buffer
    va_list args;
    va_start( args, pszFormat );
    vsnprintf( ( char * ) & pszConsoleBuffer, CIO_CONSOLEBUFFER - 14, pszFormat, args );
    va_end( args );

    // Now put buffer to screen
    i = 0;
    nConsoleAttr = 7;
    while ( pszConsoleBuffer[ i ] != 0 ) {
        Console_WriteChar( pszConsoleBuffer[ i++ ] );
    }
    Console_MoveCursor();

    return NULL;
}


KStatus Console_Call_WriteCharacter( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {
    uchar cChar = ( uchar ) MM_GetParameterUINT32( pParameters );
    Console_WriteChar( cChar );
    return NULL;
}

KStatus Console_Call_DeleteCharacter( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {
    Console_DeleteChar();
    return NULL;
}

KStatus Console_Call_Print( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {
    KPrint( NULL, MM_GetParameterSTRING( pParameters ) );
    return NULL;
}

KStatus Console_Call_LogPrint( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {
    char * pszModule = MM_GetParameterSTRING( pParameters );
    char *pszText = MM_GetParameterSTRING( pParameters );
    KPrint( pszModule, pszText );
    return NULL;
}

KStatus Console_Call_Clear( sCallStack_t *psStack, sParameterPackage_t *pParameters ) {
    KClear();
    return NULL;
}

void Console_CreateModuleInterface() {

    // Create module calls
    ModuleManager_CreateModule( "Console" );
    ModuleManager_CreateModuleCall( "Console", "Clear", &Console_Call_Clear );
    ModuleManager_CreateModuleCall( "Console", "WriteCharacter", &Console_Call_WriteCharacter );
    ModuleManager_CreateModuleCall( "Console", "DeleteCharacter", &Console_Call_DeleteCharacter );
    ModuleManager_CreateModuleCall( "Console", "Print", &Console_Call_Print );
    ModuleManager_CreateModuleCall( "Console", "LogPrint", &Console_Call_LogPrint );
}
