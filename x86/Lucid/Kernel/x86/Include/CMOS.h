// (C) Daryl Dudey 2002

#ifndef __K_X86_CMOS_H__
#define __K_X86_CMOS_H__

static inline uchar CMOS_Read( uchar nIndex ) {
    // Read in CMOS data register
    uchar nSaved = inb ( 0x70 );

    // Mask 5 lowest bits
    nSaved &= 0xE0;

    // Or the index we want
    nSaved |= nIndex;

    // Send our request
    outb( nSaved, 0x70 );

    // And return the result
    return inb ( 0x71 );
}

#endif // __K_X86_CMOS_H__
