#include <Kernel.h>

extern bool g_bQuietMode;

#define SYSLOG_BUFFER 1024

// Lock
sLock_t l_sSysLogLock;

void Syslog_LockInit() {
    Lock_Init( &l_sSysLogLock );
}

void Syslog_Lock() {
    Lock_Lock( &l_sSysLogLock );
}

void Syslog_Unlock() {
    Lock_Unlock( &l_sSysLogLock );
}

void Syslog_Init() {

    // Initialise lock
    Syslog_LockInit();

}

void Syslog_Entry( char * pszModule, const char * pszFormat, ... ) {

#ifdef DEBUG

    // If debug enabled, show which thread this call was made from
    char szThread[ 20 ];
    snprintf( ( char * ) & szThread, 20, "%lu", g_sKernel.m_psRunningThreadID );
    TextModeVideo_ChangeColour( TEXTCOLOUR_YELLOW );
    TextModeVideo_WriteString( ( char * ) & szThread );
    TextModeVideo_ChangeColour( TEXTCOLOUR_LPURPLE );
    TextModeVideo_WriteChar( ' ' );
    TextModeVideo_WriteChar( '-' );
    TextModeVideo_WriteChar( ' ' );
#endif

    // If quiet mode enabled don't display to screen
    if ( !g_bQuietMode ) {

        // Display module (if wanted)
        if ( pszModule != NULL ) {
            TextModeVideo_ChangeColour( TEXTCOLOUR_LRED );
            TextModeVideo_WriteString( pszModule );
        }

        // Pad with spaces if necessary
        uint32 i;
        for ( i = 0; i < 12 - strlen( pszModule ); i++ ) {
            TextModeVideo_WriteChar( ' ' );
        }

        // Display a separator
        TextModeVideo_ChangeColour( TEXTCOLOUR_LPURPLE );
        TextModeVideo_WriteChar( ' ' );
        TextModeVideo_WriteChar( '-' );
        TextModeVideo_WriteChar( ' ' );

        // Use printf to generate buffer
        char pszConsoleBuffer[ SYSLOG_BUFFER ];
        va_list args;
        va_start( args, pszFormat );
        vsnprintf( ( char * ) & pszConsoleBuffer, SYSLOG_BUFFER, pszFormat, args );
        va_end( args );
        TextModeVideo_ChangeColour( TEXTCOLOUR_WHITE );
        TextModeVideo_WriteString( ( char * ) & pszConsoleBuffer );
    }
}

KStatus Syslog_Entry_Call( sCallStack_t *psStack ) {

    // Lock
    Syslog_Lock();

    void * pszModule = ( void * ) psStack->ebx;
    void *pszEntry = ( void * ) psStack->ecx;

    // And call kernel syslog_entry call
    Syslog_Entry( pszModule, pszEntry );

    // Unlock
    Syslog_Unlock();

    // Return success
    return NULL;
}
