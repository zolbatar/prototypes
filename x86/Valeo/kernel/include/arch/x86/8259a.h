#ifndef __ARCH_X86_PIC_H__
#define __ARCH_X86_PIC_H__

void PIC_Init( void );
void PIC_EnableIRQ( uint16 nIRQ );
void PIC_DisableIRQ( uint16 nIRQ );
void PIC_MaskAndAcknowledge( uint16 nIRQ );
KStatus *PIC_Interface( uint32 nCode, void *pData );

#endif // __ARCH_X86_PIC_H__
