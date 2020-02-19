#ifndef __K_FS_H__
#define __K_FS_H__

#include <Types.h>
#include <KDDK-FS.h>

#define K_FS_CHECKVOLUME 0
#define K_FS_CHECKPATH 1
#define K_FS_CHECKFILENAME 2

void FS_Init( void );
uint32 FS_RegisterFilesystem( char *pszName, FilesystemHandler *pHandler );
uint32 FS_Mount( char *pszName, char *pszDevice, char *pszFileSystem, char *pszData );
uint32 FS_Open( char *pszFullPath, uint32 nFlags, uint32 *nHandle );
uint32 FS_Read( uint32 nHandle, void *pBuffer, uint32 nBytes, uint32 *nBytesRead );
uint32 FS_LoadElf( char * pszFilename );

#endif // __K_FS_H__
