#ifndef __OS_SYSCALLS_H__
#define __OS_SYSCALLS_H__

// Syscall types
typedef uint32 OS_KStatus;

enum {
    OS_SYSCALL_SYSLOG,
    OS_PROCESS_CREATETHREAD,
    OS_PROCESS_ENDTHREAD,
    OS_PROCESS_RELINQUISH,
    OS_MM_GETDATAAREASIZE
};

#endif // __OS_SYSCALLS_H__
