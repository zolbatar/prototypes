#ifndef __K_KFS_H__
#define __K_KFS_H__

#include <Types.h>

#define KFS_MAXIMUMFULLPATHSIZE 8192
#define KFS_READONLY (1 << 0)
#define KFS_WRITE (1 << 1)

#define KFS_PATHTOOLONG 0xFFFFFFFF
#define KFS_INVALIDFULLPATH 0xFFFFFFFE
#define KFS_INVALIDVOLUME 0xFFFFFFFD
#define KFS_INVALIDPATH 0xFFFFFFFC
#define KFS_INVALIDFILENAME 0xFFFFFFFB
#define KFS_VOLUMENOTFOUND 0xFFFFFFFA
#define KFS_ERROROPENINGFILE 0xFFFFFFF9
#define KFS_ERRORMOUNTING 0xFFFFFFF8
#define KFS_INVALIDHANDLE 0xFFFFFFF7
#define KFS_ERRORREADINGFROMFILE 0xFFFFFFF6
#define KFS_INVALIDELFFILE 0xFFFFFFF5

uint32 KFS_Mount( char *pszName, char *pszDevice, char *pszFileSystem, char *pszAddress, char *pszData );
uint32 KFS_Open( char *pszFullPath, uint32 nFlags, uint32 *nHandle );

#endif // __K_KFS_H__
