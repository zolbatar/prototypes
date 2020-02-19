#ifndef __LIBC_LIMITS_H
#define __LIBC_LIMITS_H

#define CHAR_BIT 8

#define SCHAR_MIN (-128)
#define SCHAR_MAX 0x7f
#define UCHAR_MAX 0xff

#ifdef __CHAR_UNSIGNED__
#undef CHAR_MIN
#define CHAR_MIN 0
#undef CHAR_MAX
#define CHAR_MAX UCHAR_MAX
#else
#undef CHAR_MIN
#define CHAR_MIN SCHAR_MIN
#undef CHAR_MAX
#define CHAR_MAX SCHAR_MAX
#endif

#define SHRT_MIN (-SHRT_MAX-1)
#define SHRT_MAX 0x7fff
#define USHRT_MAX 0xffff

#define INT_MIN (-INT_MAX-1)
#define INT_MAX 0x7fffffff
#define UINT_MAX 0xffffffff

#define LONG_MAX 2147483647L
#define ULONG_MAX 4294967295UL
#define LONG_MIN (-LONG_MAX - 1L)
#define ABS_LONG_MIN 2147483648UL

#define LLONG_MAX 9223372036854775807LL
#define LLONG_MIN (-LLONG_MAX - 1LL)

#define ULLONG_MAX 18446744073709551615ULL

#endif // __LIBC_LIMITS_H
