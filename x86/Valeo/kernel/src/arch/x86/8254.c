#include <Kernel.h>

void PIT_Init() {

    outb( 0x61, inb( 0x61 ) | 1 );

    // Select counter 0, set to read/load LSB then MSB, mode 2 (Rate generator), Binary 16 bit
    outb( 0x43, 0x34 );
    outb( 0x40, PIT_SPEED & 0xff );
    outb( 0x40, PIT_SPEED >> 8 );

    // Stop counter 1
    outb( 0x43, 0x74 );
    outb( 0x42, 0 );
    outb( 0x42, 0 );

    // Stop counter 2
    outb( 0x43, 0xB4 );
    outb( 0x42, 0 );
    outb( 0x42, 0 );
}

void PIT_StopTimer() {

    // Select counter 0, set to read/load LSB then MSB, mode 2 (Rate generator), Binary 16 bit
    // Stop counter 0
    outb( 0x43, 0x34 );
    outb( 0x40, 0 );
    outb( 0x40, 0 );
}

