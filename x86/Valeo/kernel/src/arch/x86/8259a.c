#include <Kernel.h>

static uint16 l_nPICMask = 0xFFFF;
#define __byte(x,y) 	(((unsigned char *)&(y))[x])
#define PICLower	(__byte(0,l_nPICMask))
#define PICUpper	(__byte(1,l_nPICMask))

void PIC_Init() {

    // We want to remap the hardware interrupts in the 0x0-0x1F range and move them up ]
    // to 0x20-2F, this is because the processor interrupts exist in the 0x0-0x1F range
    // and we need to access them

    outb( 0x21, PICLower );
    outb( 0xA1, PICUpper );

    // Setup 8259A-1
    outb( 0x20, 0x11 );       // Select 8259A-1
    outb( 0x21, 0x20 );       // 8259A-1 IRQ0-7 map to 0x20-0x27 (i.e after i386 interrupts)
    outb( 0x21, 0x04 );       // 8259A-1 (Master) cascades to slave or IRQ2
    outb( 0x21, 0x01 );       // Set manual EOI (0x02 for Auto EOI)

    // Setup 8259A-2
    outb( 0xA0, 0x11 );       // Select 8259A-2
    outb( 0xA1, 0x28 );       // 8259A-2 IRQ0-7 map to 0x28-0x2F
    outb( 0xA1, 0x02 );       // 8259A-2 (Slave)
    outb( 0xA1, 0x01 );       // Set manual EOI

    // Disable all interrupts for now, individual drivers can enable them selectively later
    outb( PICLower, 0x21 );
    outb( PICUpper, 0xA1 );
}

void PIC_EnableIRQ( uint16 nIRQ ) {

    l_nPICMask &= ~( 1 << nIRQ );
    if ( nIRQ & 8 ) {
        outb( 0xA1, PICUpper );
    } else {
        outb( 0x21, PICLower );
    }
}

void PIC_DisableIRQ( uint16 nIRQ ) {

    l_nPICMask |= 1 << nIRQ;
    if ( nIRQ & 8 ) {
        outb( 0xA1, PICUpper );
    } else {
        outb( 0x21, PICLower );
    }
}

void PIC_MaskAndAcknowledge( uint16 nIRQ ) {

    // Save saved PIC flags
    l_nPICMask |= 1 << nIRQ;

    if ( nIRQ & 8 ) {
        inb( 0xA1 );
        outb( 0xA1, PICUpper );
        outb( 0xA0, 0x60 + ( nIRQ & 7 ) );
        outb( 0x20, 0x62 );
    } else {
        inb( 0x21 );
        outb( 0x21, PICLower );
        outb( 0x20, 0x60 + nIRQ );
    }
}


