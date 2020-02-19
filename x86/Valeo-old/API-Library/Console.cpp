#include <API/Valeo-API.h>

using namespace os;

Console::Console() {
    m_nCallClear = MM_GetCallID( "Console", "Clear" );
    m_nCallWriteCharacter = MM_GetCallID( "Console", "WriteCharacter" );
    m_nCallDeleteCharacter = MM_GetCallID( "Console", "DeleteCharacter" );
    m_nCallPrint = MM_GetCallID( "Console", "Print" );
    m_nCallLogPrint = MM_GetCallID( "Console", "LogPrint" );
}

Console::~Console() {}

KStatus Console::Clear( ) {
    return MM_Call( m_nCallClear, NULL );
}

KStatus Console::WriteCharacter( uchar cCharacter ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterUINT32( &sPackage, ( uint32 ) cCharacter );
    return MM_Call( m_nCallWriteCharacter, &sPackage );
}

KStatus Console::DeleteCharacter() {
    return MM_Call( m_nCallDeleteCharacter, NULL );
}

KStatus Console::Print( char *pszString ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterSTRING( &sPackage, pszString );
    return MM_Call( m_nCallPrint, &sPackage );
}

KStatus Console::LogPrint( char *pszModule, char *pszString ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterSTRING( &sPackage, pszModule );
    MM_AddParameterSTRING( &sPackage, pszString );
    return MM_Call( m_nCallLogPrint, &sPackage );
}
