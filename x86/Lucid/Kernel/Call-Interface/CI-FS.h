#ifndef __K_CI_FS_H__
#define __K_CI_FS_H__

#include <Types.h>

// Filesystem register
typedef struct {
    char *m_pszName;
    FilesystemHandler *m_pHandler;
}
KFS_sRegisterFilesystem_t;

// Volume mount structure
typedef struct {
    char *m_pszName;
    char *m_pszDevice;
    char *m_pszFileSystem;
    char *m_pszAddress;
    char *m_pszData;
}
KFS_sMount_t;

// Open struct
typedef struct {
    K_sVolume_t *m_psVolume;
    char *m_pszVolume;
    char *m_pszPath;
    char *m_pszFilename;
    K_sFileHandle_t *m_psFileHandle;
}
KFS_sOpen_t;

// Read struct
typedef struct {
    K_sFileHandle_t *m_psHandle;
    void *m_pBuffer;
    uint32 m_nBytesNeeded;
    uint32 *m_nBytesRead;
}
KFS_sRead_t;

#endif // __K_CI_FS_H__
