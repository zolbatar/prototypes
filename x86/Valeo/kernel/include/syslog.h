#ifndef __SYSLOG_H__
#define __SYSLOG_H__

void Syslog_Init( void );
void Syslog_Entry( char * pszModule, const char * pszFormat, ... );
void Syslog_Lock( void );
void Syslog_Unlock( void );

#endif // __SYSLOG_H__
