#ifndef __K_KDDKFS_H__
#define __K_KDDKFS_H__

#include <Types.h>

enum {
    KFS_OPEN,
    KFS_READ
};

// Filesystem struct
typedef uint32 FilesystemHandler( uint32 nCode, void *pData );
typedef struct {

    // Handler
    FilesystemHandler *m_pHandler;
}
K_sFilesystem_t;

// Volume struct
typedef struct {
    void *m_psIODeviceObject;        // These are essentially K_sObject_t pointers
    void *m_psFilesystemObject;      // These are essentially K_sObject_t pointers
    K_sIODevice_t *m_psIODevice;
    K_sFilesystem_t *m_psFilesystem;
}
K_sVolume_t;

// File handle struct
typedef struct {
    K_sVolume_t *m_psVolume;        // Associated volume
    uint32 m_nPosition;             // Current file position
}
K_sFileHandle_t;

uint32 KFS_RegisterFilesystem( char *pszName, FilesystemHandler *pHandler );

#endif // __K_KDDKFS_H__
