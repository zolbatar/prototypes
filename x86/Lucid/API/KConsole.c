#include <OSCalls.h>
#include <CI-Console.h>

uint32 Console_nHandle;
uint32 Console_nClear;
uint32 Console_nWriteCharacter;
uint32 Console_nDeleteCharacter;
uint32 Console_nPrint;
uint32 Console_nDebugPrint;

void KConsole_Init() {

    // Get handle to console
    Console_nHandle = KModule_GetHandle( "Console" );

    // Get call codes
    Console_nClear = KModule_GetCallID( Console_nHandle, "Clear" );
    Console_nWriteCharacter = KModule_GetCallID( Console_nHandle, "WriteCharacter" );
    Console_nDeleteCharacter = KModule_GetCallID( Console_nHandle, "DeleteCharacter" );
    Console_nPrint = KModule_GetCallID( Console_nHandle, "Print" );
    Console_nDebugPrint = KModule_GetCallID( Console_nHandle, "DebugPrint" );
}

void KConsole_Clear() {

    // Check if initialised
    if ( Console_nHandle == NULL )
        KConsole_Init();

    KModule_Call( Console_nHandle, Console_nClear, NULL );
}

void KConsole_WriteCharacter( uchar nChar ) {

    // Check if initialised
    if ( Console_nHandle == NULL )
        KConsole_Init();

    KConsole_sWriteCharacter_t sData;
    sData.m_nChar = nChar;
    KModule_Call( Console_nHandle, Console_nWriteCharacter, &sData );
}

void KConsole_DeleteCharacter( ) {
    // Check if initialised
    if ( Console_nHandle == NULL )
        KConsole_Init();

    KModule_Call( Console_nHandle, Console_nDeleteCharacter, NULL );
}

void KConsole_Print( char *pszString ) {

    // Check if initialised
    if ( Console_nHandle == NULL )
        KConsole_Init();

    KModule_Call( Console_nHandle, Console_nPrint, pszString );
}

void KConsole_DebugPrint( uint32 nSeverity, char *pszModule, char *pszString ) {

    // Check if initialised
    if ( Console_nHandle == NULL )
        KConsole_Init();

    KConsole_sDebugPrint_t sData;
    sData.m_nSeverity = nSeverity;
    sData.m_pszModule = pszModule;
    sData.m_pszString = pszString;
    KModule_Call( Console_nHandle, Console_nDebugPrint, &sData );
}

