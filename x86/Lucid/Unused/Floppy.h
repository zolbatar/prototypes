// Lucid - Operating System Project
// (C) Daryl Dudey 2002

#ifndef __K_RAMFSDEVICE_H__
#define __K_RAMFSDEVICE_H__

void Floppy_Init();
bool Floppy_Handler( K_sKBlockIODevice_t *psDevice );
void Floppy_Worker();

#endif // __K_RAMFSDEVICE_H__

