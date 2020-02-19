#include <Kernel.h>

extern void Syscall_Interface_Microkernel( void );

void Syscall_Init() {

    // Attach interrupt handlers for each syscall interface
    Descriptor_SetInterruptGate( 0x80, &Syscall_Interface_Microkernel );
}

