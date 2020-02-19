#include <Kernel.h>

static uint16 PICMask = 0xFFFF;
#define __byte(x,y) 	(((unsigned char *)&(y))[x])
#define PICLower	(__byte(0,PICMask))
#define PICUpper	(__byte(1,PICMask))

void PIC_Init() {

    // We want to remap the hardware interrupts in the 0x0-0x1F range and move them up ]
    // to 0x20-2F, this is because the processor interrupts exist in the 0x0-0x1F range
    // and we need to access them

    outb( PICLower, 0x21 );
    outb( PICUpper, 0xA1 );

    // Setup 8259A-1
    outb( 0x11, 0x20 );       // Select 8259A-1
    outb( 0x20, 0x21 );       // 8259A-1 IRQ0-7 map to 0x20-0x27 (i.e after i386 interrupts)
    outb( 0x04, 0x21 );       // 8259A-1 (Master) cascades to slave or IRQ2
    outb( 0x01, 0x21 );       // Set manual EOI (0x02 for Auto EOI)

    // Setup 8259A-2
    outb( 0x11, 0xA0 );       // Select 8259A-2
    outb( 0x28, 0xA1 );       // 8259A-2 IRQ0-7 map to 0x28-0x2F
    outb( 0x02, 0xA1 );       // 8259A-2 (Slave)
    outb( 0x01, 0xA1 );       // Set manual EOI

    // Disable all interrupts for now, individual drivers can enable them selectively later
    outb( PICLower, 0x21 );
    outb( PICUpper, 0xA1 );

    // Add resources to kernel
    /*    DeviceManager_RegisterDevice( "8259a PIC" );
        DeviceManager_AttachResource( "8259a PIC", KDEVICE_RES_PORT, 0x20 );
        DeviceManager_AttachResource( "8259a PIC", KDEVICE_RES_PORT, 0x21 );
        DeviceManager_AttachResource( "8259a PIC", KDEVICE_RES_PORT, 0xA0 );
        DeviceManager_AttachResource( "8259a PIC", KDEVICE_RES_PORT, 0xA1 );*/
    KPrint( "PIC", "PIC Initialised\n" );
}

void PIC_EnableIRQ( uint16 nIRQ ) {

    PICMask &= ~( 1 << nIRQ );
    if ( nIRQ & 8 ) {
        outb( PICUpper, 0xA1 );
    } else {
        outb( PICLower, 0x21 );
    }
}

void PIC_DisableIRQ( uint16 nIRQ ) {

    PICMask |= 1 << nIRQ;
    if ( nIRQ & 8 ) {
        outb( PICUpper, 0xA1 );
    } else {
        outb( PICLower, 0x21 );
    }
}

void PIC_MaskAndAcknowledge( uint16 nIRQ ) {

    // Save saved PIC flags
    PICMask |= 1 << nIRQ;

    if ( nIRQ & 8 ) {
        inb( 0xA1 );
        outb( PICUpper, 0xA1 );
        outb( 0x60 + ( nIRQ & 7 ), 0xA0 );
        outb( 0x62, 0x20 );
    } else {
        inb( 0x21 );
        outb( PICLower, 0x21 );
        outb( 0x60 + nIRQ, 0x20 );
    }
}


