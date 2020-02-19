#ifndef __LIBC_STDIO_H
#define __LIBC_STDIO_H

#include <sys/cdefs.h>
#include <stdarg.h>

__BEGIN_DECLS
int snprintf( char *str, size_t size, const char *format, ... );
int vsprintf( char *str, const char *format, va_list args );
int vsnprintf( char *str, size_t size, const char *format, va_list args );
__END_DECLS

#endif // __LIBC_STDIO_H
