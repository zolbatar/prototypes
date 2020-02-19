// (C) Daryl Dudey 2002

#ifndef __K_X86_PIC_H__
#define __K_X86_PIC_H__

void PIC_Init( void );
void PIC_EnableIRQ( uint16 nIRQ );
void PIC_DisableIRQ( uint16 nIRQ );
void PIC_MaskAndAcknowledge( uint16 nIRQ );

#endif // __K_X86_PIC_H__
