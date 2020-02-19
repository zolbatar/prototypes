#ifndef __STRTOL_H__
#define __STRTOL_H__

#include <Printf.h>
#include <Limits.h>

long int strtol( const char *nptr, char **endptr, int base );
unsigned long int strtoul( const char *nptr, char **endptr, int base );

#endif // __STRTOL_H__

