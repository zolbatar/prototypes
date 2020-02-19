#ifndef __LIB_STRTOL_H__
#define __LIB_STRING_H__

#include <printf.h>
#include <limits.h>

long int strtol( const char *nptr, char **endptr, int base );
unsigned long int strtoul( const char *nptr, char **endptr, int base );

#endif // __LIB_STRING_H__

