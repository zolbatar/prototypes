#ifndef __K_STANDARD_STRTOL_H__
#define __K_STANDARD_STRTOL_H__

#include <Printf.h>
#include <Limits.h>

long int strtol( const char *nptr, char **endptr, int base );
unsigned long int strtoul( const char *nptr, char **endptr, int base );

#endif // __K_STANDARD_STRTOL_H__

