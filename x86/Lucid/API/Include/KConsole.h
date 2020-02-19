#ifndef __K_KCONSOLE_H__
#define __K_KCONSOLE_H__

#include <Types.h>

#define KVERBOSE 0
#define KDEBUG 1
#define KSEVERE 2

void KConsole_Clear( void );
void KConsole_WriteCharacter( uchar nChar );
void KConsole_DeleteCharacter( void );
void KConsole_Print( char *pszString );
void KConsole_DebugPrint( uint32 nSeverity, char *pszModule, char *pszString );

#endif // __K_KCONSOLE_H__
