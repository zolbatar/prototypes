#ifndef __TYPES_H__
#define __TYPES_H__

#define NULL 0
#define false 0
#define true 1

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int int16;
typedef unsigned short int uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef long long int64;
typedef unsigned char uchar;
typedef unsigned long int size_t;
#ifndef GNUCPP
typedef unsigned char bool;
#endif

#endif // __TYPES_H__

