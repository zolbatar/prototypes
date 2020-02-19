#ifndef __K_CI_CONSOLE_H__
#define __K_CI_CONSOLE_H__

#include <Types.h>

typedef struct {
    // Parameters
    uint32 m_nSeverity;
    char *m_pszModule;
    char *m_pszString;
}
KConsole_sDebugPrint_t;

typedef struct {
    uchar m_nChar;
}
KConsole_sWriteCharacter_t;

#endif // __K_CI_CONSOLE_H__
