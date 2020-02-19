#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#define FS_CHECKVOLUME 0
#define FS_CHECKPATH 1
#define FS_CHECKFILENAME 2

#define FS_MAXIMUMFULLPATHSIZE 8192

void FS_Init( void );
KStatus FS_RegisterFilesystem( char *pszName, FSRegisterCallBack *pCallback );
KStatus FS_Mount( char *pszName, char *pszDevice, char *pszFileSystem, char *pszData );
KStatus FS_Unmount( char *pszName );
KStatus FS_Open( char * pszFullPath, uint32 nFlags, uint32 * nHandle );
KStatus FS_Close( uint32 nHandle );
KStatus FS_Read( uint32 nHandle, void *pBuffer, uint32 nBytes, uint32 *nBytesRead );
KStatus FS_Seek( uint32 nHandle, uint32 nPosition );
KStatus FS_LoadElf( char *pszFilename, void **pAddress, void **pEntry );

#endif // __FILESYSTEM_H__
