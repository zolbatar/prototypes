#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define do_div(n,base) ({ \
	unsigned long __upper, __low, __high, __mod; \
	asm("":"=a" (__low), "=d" (__high):"A" (n)); \
	__upper = __high; \
	if (__high) { \
		__upper = __high % (base); \
		__high = __high / (base); \
	} \
	asm("divl %2":"=a" (__low), "=d" (__mod):"rm" (base), "0" (__low), "1" (__upper)); \
	asm("":"=A" (n):"a" (__low),"d" (__high)); \
	__mod; \
})

static int skip_atoi( const char **s ) {
    int i = 0;

    while ( isdigit( **s ) )
        i = i * 10 + *( ( *s ) ++ ) - '0';
    return i;
}

#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	32		/* 0x */
#define LARGE	64		/* use 'ABCDEF' instead of 'abcdef' */

static char * number( char * buf, char * end, long long num, int base, int size, int precision, int type ) {
    char c, sign, tmp[ 66 ];
    const char *digits;
    const char small_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    const char large_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;

    digits = ( type & LARGE ) ? large_digits : small_digits;
    if ( type & LEFT )
        type &= ~ZEROPAD;
    if ( base < 2 || base > 36 )
        return 0;
    c = ( type & ZEROPAD ) ? '0' : ' ';
    sign = 0;
    if ( type & SIGN ) {
        if ( num < 0 ) {
            sign = '-';
            num = -num;
            size--;
        } else if ( type & PLUS ) {
            sign = '+';
            size--;
        } else if ( type & SPACE ) {
            sign = ' ';
            size--;
        }
    }
    if ( type & SPECIAL ) {
        if ( base == 16 )
            size -= 2;
        else if ( base == 8 )
            size--;
    }
    i = 0;
    if ( num == 0 )
        tmp[ i++ ] = '0';
    else
        while ( num != 0 )
            tmp[ i++ ] = digits[ do_div( num, base ) ];
    if ( i > precision )
        precision = i;
    size -= precision;
    if ( !( type & ( ZEROPAD + LEFT ) ) ) {
        while ( size-- > 0 ) {
            if ( buf <= end )
                * buf = ' ';
            ++buf;
        }
    }
    if ( sign ) {
        if ( buf <= end )
            * buf = sign;
        ++buf;
    }
    if ( type & SPECIAL ) {
        if ( base == 8 ) {
            if ( buf <= end )
                * buf = '0';
            ++buf;
        } else if ( base == 16 ) {
            if ( buf <= end )
                * buf = '0';
            ++buf;
            if ( buf <= end )
                * buf = digits[ 33 ];
            ++buf;
        }
    }
    if ( !( type & LEFT ) ) {
        while ( size-- > 0 ) {
            if ( buf <= end )
                * buf = c;
            ++buf;
        }
    }
    while ( i < precision-- ) {
        if ( buf <= end )
            * buf = '0';
        ++buf;
    }
    while ( i-- > 0 ) {
        if ( buf <= end )
            * buf = tmp[ i ];
        ++buf;
    }
    while ( size-- > 0 ) {
        if ( buf <= end )
            * buf = ' ';
        ++buf;
    }
    return buf;
}

int vsnprintf( char *buf, size_t size, const char *fmt, va_list args ) {
    int len;
    unsigned long long num;
    int i, base;
    char *str, *end, c;
    const char *s;

    int flags;		/* flags to number() */

    int field_width;	/* width of output field */
    int precision;		/* min. # of digits for integers; max
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                				   number of chars for from st