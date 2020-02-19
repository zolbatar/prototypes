#ifndef __OS_SYSLOG_H__
#define __OS_SYSLOG_H__

static inline OS_KStatus OS_Syslog_Entry( char * pszModule, const char * pszFormat ) {

    // Call kernel function
    uint32 nEAX = OS_SYSCALL_SYSLOG;
    OS_KStatus nResult;
asm volatile( "int $0x80" : "=a" ( nResult ) : "a" ( nEAX ), "b" ( pszModule ), "c" ( pszFormat ) );

    return nResult;
}

#endif // __OS_SYSLOG_H__
