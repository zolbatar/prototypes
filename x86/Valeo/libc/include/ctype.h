#ifndef	__LIBC_CTYPE_H
#define __LIBC_CTYPE_H

#include <sys/cdefs.h>

__BEGIN_DECLS
int isascii ( int c );
int isblank ( int c );
int isalnum ( int c );
int isalpha ( int c );
int isdigit ( int c );
int isspace ( int c );
int isupper ( int c );
int islower ( int c );
int tolower( int c );
int toupper( int c );
int isprint( int c );
int ispunct( int c );
int iscntrl( int c );
int isxdigit( int c );
int isgraph( int c );
__END_DECLS

#endif // __LIBC_CTYPE_H
