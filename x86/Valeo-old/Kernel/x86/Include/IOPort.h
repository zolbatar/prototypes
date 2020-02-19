#ifndef __IOPORT_H__
#define __IOPORT_H__

#include <Types.h>

static inline uchar inb( uint16 nPort ) {
    unsigned char v;
asm volatile ( "inb %w1,%0": "=a" ( v ) : "Nd" ( nPort ) );
    return v;
}

static inline void outb( uchar nValue, uint16 nPort ) {
asm volatile ( "outb %b0,%w1": : "a" ( nValue ), "Nd" ( nPort ) );
}

#endif // __IOPORT_H__

