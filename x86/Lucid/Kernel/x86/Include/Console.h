// (C) Daryl Dudey 2002

#ifndef __K_X86_CONSOLE_H__
#define __K_X86_CONSOLE_H__

#define CIO_CONSOLEMEMPAGES 0x8

extern volatile unsigned char *Kg_pConsoleVideo;

void Console_Init( void );
void Console_Remap( void );
void Console_CreateModuleInterface( void );
void KClear( void );
void KPrint( uint32 nSeverity, const char *pszModule, const char *pszFormat, ... );

#endif // __K_X86_CONSOLE_H__

