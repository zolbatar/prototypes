#include <Kernel.h>

#define MEMADDR 0xB8000
#define MEMPAGES 0x8
#define COLUMNS 80
#define ROWS 25

#define ADDRESSREGISTER 0x3d4
#define DATAREGISTER 0x3d5

// Keep track of screen position
volatile uchar *g_pVideo;
uint32 nX;
uint32 nY;
uint32 nPos;
uchar nAttr = TEXTCOLOUR_WHITE;

void TextModeVideo_Init() {

    // Set memory address
    g_pVideo = ( uchar * ) MEMADDR;

    // Change cursor shape
    outb( ADDRESSREGISTER, ( uchar ) 0x9 );
    uchar nCursorSizeMax = inb( DATAREGISTER ) & 0x1f;
    outb( ADDRESSREGISTER, ( uchar ) 0xa );
    outb( DATAREGISTER, ( uchar ) nCursorSizeMax >> 1 );
    outb( ADDRESSREGISTER, ( uchar ) 0xb );
    outb( DATAREGISTER, ( uchar ) nCursorSizeMax );

    // And clear console
    TextModeVideo_Cls();
}

void TextModeVideo_PostMMInit() {

    // Move video memory from 0xB8000 to driver area
    MM_Lock();
    MM_Page_Map( MEMADDR, ( uint32 ) g_sKernel.m_pPhysicalMemMapArea, MEMPAGES, MM_FLAGS_KERNEL | MM_FLAGS_READWRITE );
    g_pVideo = ( unsigned char * ) g_sKernel.m_pPhysicalMemMapArea;
    g_sKernel.m_pPhysicalMemMapArea += MEMPAGES << MM_PAGESIZESHIFT;
    MM_Unlock();
}

void TextModeVideo_MoveCursor() {

    // Change cursor position on screen
    uint32 nPosition = ( nY * 80 ) + nX;

    outb( ADDRESSREGISTER, ( uchar ) 0xf );
    outb( DATAREGISTER, ( uchar ) nPosition & 0xFF );
    outb( ADDRESSREGISTER, ( uchar ) 0xe );
    outb( DATAREGISTER, ( uchar ) ( nPosition >> 8 ) & 0xFF );
}

void TextModeVideo_Cls() {

    // Clear video memory
    memset( ( void * ) g_pVideo, 0, COLUMNS * ROWS * 2 );

    // Initialise cursor variables
    nX = 0;
    nY = 0;
    nPos = 0;
    TextModeVideo_MoveCursor();
}

void TextModeVideo_ChangeColour( uchar nColour ) {
    nAttr = nColour;
}

void TextModeVideo_WriteChar ( uchar c ) {

    // Write character at cursor and scroll etc. as needed
    if ( c == '\n' || c == '\r' ) {
newline:
        nX = 0;
        nY++;
        nPos = ( nY * 160 );
        if ( nY == ROWS ) {

            // Scroll 1 lines up
            memcpy( ( void * ) g_pVideo, ( void * ) g_pVideo + ( COLUMNS * 2 ) , ( ( ROWS - 1 ) * COLUMNS * 2 ) );

            // Clear new lines
            memset( ( void * ) g_pVideo + ( ( ROWS - 1 ) * COLUMNS * 2 ) , 0, ( 1 * COLUMNS * 2 ) );
            nY --;
            nPos -= 160;
        }
        TextModeVideo_MoveCursor();
        return ;
    }

    g_pVideo[ nPos ] = c & 0xFF;
    g_pVideo[ nPos + 1 ] = nAttr;

    nX++;
    nPos += 2;
    if ( nX >= COLUMNS ) {
        goto newline;
    }
}

void TextModeVideo_DeleteChar ( ) {

    // Delete character at cursor
    nX--;
    nPos -= 2;
    *( g_pVideo + nPos ) = 0;
    *( g_pVideo + nPos + 1 ) = nAttr;
}

void TextModeVideo_WriteString( char *pszString ) {

    // Output to screen
    int i = 0;
    while ( pszString[ i ] != 0 ) {
        TextModeVideo_WriteChar( pszString[ i++ ] );
    }
}

