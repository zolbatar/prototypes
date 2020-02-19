#ifndef __K_STANDARD_SCANF_H__
#define __K_STANDARD_SCANF_H__

#include <Stdarg.h>
#include <Types.h>
#include <Limits.h>

struct arg_scanf {
    void *data;
    int ( *getch ) ( void* );
    int ( *putch ) ( int, void* );
};

int sscanf( const char *str, const char *format, ... );

#endif // __K_STANDARD_SCANF_H__

