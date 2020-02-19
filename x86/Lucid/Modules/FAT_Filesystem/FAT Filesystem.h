// Lucid - Operating System Project
// (C) Daryl Dudey 2002

#ifndef __K_RAMFS_H__
#define __K_RAMFS_H__

//typedef struct k_sRAMVolume {
//};

void RAMFilesystem_Init();
bool RAMFilesystem_FSHandler( K_sKBlockIODevice_t *psDevice );
void RAMFilesystem_Worker();

#endif // __K_RAMFS_H__

