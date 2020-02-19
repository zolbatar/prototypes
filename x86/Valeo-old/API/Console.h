#ifndef __API_CONSOLE_H__
#define __API_CONSOLE_H__

#include <API/Types.h>

#ifndef API_IN_KERNEL
namespace os {

class Console {
public:
    Console();
    ~Console();
    KStatus Clear( void );
    KStatus WriteCharacter( uchar cCharacter );
    KStatus DeleteCharacter( void );
    KStatus Print( char *pszString );
    KStatus LogPrint( char *pszModule, char *pszString );

private:
    MMModuleCallID m_nCallClear;
    MMModuleCallID m_nCallWriteCharacter;
    MMModuleCallID m_nCallDeleteCharacter;
    MMModuleCallID m_nCallPrint;
    MMModuleCallID m_nCallLogPrint;
};

} // End namespace os
#endif

#endif // __API_CONSOLE_H__
