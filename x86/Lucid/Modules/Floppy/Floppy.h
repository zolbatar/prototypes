// Lucid - Operating System Project
// (C) Daryl Dudey 2002

#ifndef __K_RAMFSDEVICE_H__
#define __K_RAMFSDEVICE_H__

void RAMFSDevice_Init();
bool RAMFSDevice_Handler( K_sKBlockIODevice_t *psDevice );
void RAMFSDevice_Worker();

#endif // __K_RAMFSDEVICE_H__

