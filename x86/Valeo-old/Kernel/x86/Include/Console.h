#ifndef __K_X86_CONSOLE_H__
#define __K_X86_CONSOLE_H__

// Text mode frame buffer
extern volatile unsigned char *g_pConsoleVideo;

void Console_Init( void );
void Console_Remap( void );
void Console_CreateModuleInterface( void );
KStatus KClear( void );
KStatus KPrint( char *pszModule, const char *pszFormat, ... );

#endif // __K_X86_CONSOLE_H__

