#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

long int strtol( const char *nptr, char **endptr, int base ) {
    int neg = 0;
    unsigned long int v;

    while ( isspace( *nptr ) )
        nptr++;

    if ( *nptr == '-' ) {
        neg = -1;
        ++nptr;
    }
    v = strtoul( nptr, endptr, base );
    if ( v >= ABS_LONG_MIN ) {
        if ( v == ABS_LONG_MIN && neg ) {
            return v;
        }
        return ( neg ? LONG_MIN : LONG_MAX );
    }
    return ( neg ? -v : v );
}

unsigned long int strtoul( const char *nptr, char **endptr, int base ) {
    unsigned long int v = 0;

    while ( isspace( *nptr ) )
        ++nptr;
    if ( *nptr == '+' )
        ++nptr;
    if ( base == 16 && nptr[ 0 ] == '0' )
        goto skip0x;
    if ( !base ) {
        if ( *nptr == '0' ) {
            base = 8;
skip0x:
            if ( nptr[ 1 ] == 'x' || nptr[ 1 ] == 'X' ) {
                nptr += 2;
                base = 16;
            }
        } else
            base = 10;
    }
    while ( *nptr ) {
        register unsigned char c = *nptr;
        c = ( c >= 'a' ? c - 'a' + 10 : c >= 'A' ? c - 'A' + 10 : c <= '9' ? c - '0' : 0xff );
        if ( c >= base )
            break;
        {
            register unsigned long int w = v * base;
            if ( w < v ) {
                return ULONG_MAX;
            }
            v = w + c;
        }
        ++nptr;
    }
    if ( endptr )
        * endptr = ( char * ) nptr;
    return v;
}

int ltostr( char *s, unsigned int size, unsigned long i, unsigned int base, int UpCase ) {
    char * tmp;
    unsigned int j = 0;

    s[ --size ] = 0;

    tmp = s + size;

    if ( ( base == 0 ) || ( base > 36 ) )
        base = 10;

    j = 0;
    if ( !i ) {
        *( --tmp ) = '0';
        j = 1;
    }

    while ( ( tmp > s ) && ( i ) ) {
        tmp--;
        if ( ( *tmp = i % base + '0' ) > '9' )
            * tmp += ( UpCase ? 'A' : 'a' ) - '9' -1;
        i = i / base;
        j++;
    }
    memmove( s, tmp, j + 1 );

    return j;
}
