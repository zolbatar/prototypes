#ifndef __API_FILESYSTEM_H__
#define __API_FILESYSTEM_H__

#include <API/Types.h>

// Filesystem struct
typedef struct {
    // Calls
    void *m_pOpenCall;
    void *m_pReadCall;
}
sFilesystem_t;

// Volume struct
typedef struct {
    sIODevice_t *m_psIODevice;
    sFilesystem_t *m_psFilesystem;
}
sVolume_t;

// File handle struct
typedef struct {
    sVolume_t *m_psVolume;
    uint32 m_nPosition;
}
sFileHandle_t;

// Function prototypes used for file system drivers
typedef KStatus FSRegisterCallBack( sFilesystem_t *psFilesystem );
typedef KStatus FSOpenCall( sVolume_t *psVolume, char *pszVolume, char *pszPath, char *pszFilename, sFileHandle_t *psFileHandle );
typedef KStatus FSReadCall( sFileHandle_t *psHandle, void *pBuffer, uint32 nBytesNeeded, uint32 *nBytesRead );

#define FS_READONLY (1 << 0)
#define FS_WRITE (1 << 1)

// Errors
#define FS_PATHTOOLONG 0xFFFFFFFF
#define FS_INVALIDFULLPATH 0xFFFFFFFE
#define FS_INVALIDVOLUME 0xFFFFFFFD
#define FS_INVALIDPATH 0xFFFFFFFC
#define FS_INVALIDFILENAME 0xFFFFFFFB
#define FS_INVALIDFILESYSTEM 0xFFFFFFFA
#define FS_ERROROPENINGFILE 0xFFFFFFF9
#define FS_ERRORMOUNTING 0xFFFFFFF8
#define FS_INVALIDHANDLE 0xFFFFFFF7
#define FS_ERRORREADINGFROMFILE 0xFFFFFFF6
#define FS_INVALIDELFFILE 0xFFFFFFF5
#define FS_INVALIDIODEVICE 0xFFFFFFF4
#define FS_HASREFERENCES 0xFFFFFFF3
#define FS_ERRORCLOSINGFILE 0xFFFFFFF2
#define FS_ERRORDISMOUNTING 0xFFFFFFF1

#endif // __API_FILESYSTEM_H__
