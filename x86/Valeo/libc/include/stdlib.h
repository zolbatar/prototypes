#ifndef __LIBC_STDLIB_H
#define __LIBC_STDLIB_H

#include <sys/cdefs.h>

__BEGIN_DECLS
long int strtol( const char *nptr, char **endptr, int base );
unsigned long int strtoul( const char *nptr, char **endptr, int base );
int ltostr( char *s, unsigned int size, unsigned long i, unsigned int base, int UpCase );
__END_DECLS

#endif // __LIBC_STDLIB_H
