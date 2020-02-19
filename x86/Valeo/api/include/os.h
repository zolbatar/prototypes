#ifndef __OS_OS_H__
#define __OS_OS_H__

// Architecture specific
#include <arch/x86/os-atomic.h>
#include <arch/x86/os-spinlock.h>

// Basics
#include <os-syscalls.h>
#include <os-locking.h>

// Kernel
#include <os-syslog.h>
#include <os-module.h>
#include <os-process.h>
#include <os-mm.h>

#endif // __OS_OS_H__
