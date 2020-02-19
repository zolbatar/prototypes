#include <Kernel.h>

void PIT_Init() {

    outb( inb( 0x61 ) | 1, 0x61 );

    // Select counter 0, set to read/load LSB then MSB, mode 2 (Rate generator), Binary 16 bit
    outb( 0x34, 0x43 );
    outb( PIT_SPEED & 0xff, 0x40 );
    outb( PIT_SPEED >> 8, 0x40 );

    // Stop counter 1
    outb( 0x74, 0x43 );
    outb( 0, 0x42 );
    outb( 0, 0x42 );

    // Stop counter 2
    outb( 0xB4, 0x43 );
    outb( 0, 0x42 );
    outb( 0, 0x42 );

    // Add resources to kernel
    /*    DeviceManager_RegisterDevice( "8254 PIT" );
        DeviceManager_AttachResource( "8254 PIT", KDEVICE_RES_PORT, 0x40 );
        DeviceManager_AttachResource( "8254 PIT", KDEVICE_RES_PORT, 0x41 );
        DeviceManager_AttachResource( "8254 PIT", KDEVICE_RES_PORT, 0x42 );
        DeviceManager_AttachResource( "8254 PIT", KDEVICE_RES_PORT, 0x43 );
        DeviceManager_AttachResource( "8254 PIT", KDEVICE_RES_IRQ, 0x0 );*/
    KPrint( "PIT", "PIT Initialised\n" );
}

void PIT_StopTimer() {

    // Select counter 0, set to read/load LSB then MSB, mode 2 (Rate generator), Binary 16 bit
    // Stop counter 0
    outb( 0x34, 0x43 );
    outb( 0, 0x40 );
    outb( 0, 0x40 );
}

