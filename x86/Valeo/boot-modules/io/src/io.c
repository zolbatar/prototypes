#include <stdio.h>
#include <os.h>
#include <io.h>

// Prototypes
OS_KStatus Start( void );
OS_KStatus Interface();
void IO_WorkerThread( void );

// Module definition
OS_sModuleDefinition_t g_sModule = {"I/O Core", 1, 0, &Interface, &Start};

OS_sModuleDefinition_t *Entry( ) {
    return & g_sModule;
}

OS_KStatus Start() {

    // Calculate number of IO Cache entries (set to maximum of kernel data area)
    uint32 nDataAreaPages = OS_MM_GetDataAreaSize();
    char buffer[ 1000 ];
    snprintf( ( char * ) & buffer, 1000, "Pages = %lu\n", ( nDataAreaPages * 4096 ) >> 10 );
    OS_Syslog_Entry( "IO", ( char * ) & buffer );

    // Start up worker thread
    uint32 nTID;
    OS_KStatus nResult = OS_Process_Createthread( &IO_WorkerThread, &nTID );
    if ( nResult != NULL ) {
        OS_Syslog_Entry( "IO", "Error starting 'Worker Thread', aborting.\n" );
        return NULL;
    }

    // We want to stay loaded
    return 1;
}

OS_KStatus Interface() {
    return NULL;
}

void IO_WorkerThread() {

    OS_Syslog_Entry( "IO", "Worker thread\n" );
    while ( 1 ) {
        OS_Process_Relinquish();
    }
}
