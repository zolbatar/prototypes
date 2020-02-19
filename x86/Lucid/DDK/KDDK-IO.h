#ifndef __K_KDDKIO_H__
#define __K_KDDKIO_H__

#include <Types.h>

enum {
    KIO_MOUNT,
    KIO_READ
};

// Device struct
typedef uint32 IOHandler( uint32 nCode, void *pData );
typedef struct {

    // Device definition
    bool m_bRemoveable;	       	   		       // Removable media?
    uint32 m_nTotalBlocks;     	   		       // Maximum blocks
    uint32 m_nBlockSize;     	   		       // Block size in bytes

    // Position
    uint32 m_nBlock;   	       	   		       // Position

    // I/O Cache settings
    uint32 m_nBlocksPerCacheEntry;

    // Call handler
    IOHandler *m_pHandler;			       // Handler function

    // Command
    uint32 m_nCommand;				       // Current command
    uint32 m_nRequestBlock;			       // Block requested
}
K_sIODevice_t ;

typedef struct {

    // Current position
    uint32 m_nHead;
    uint32 m_nCylinder;
    uint32 m_nSector;

    // Dimensions
    uint32 m_nTotalHeads;
    uint32 m_nTotalCylinders;
    uint32 m_nSectorsPerCylinder;
    uint32 m_nSectorSize;
    uint32 m_nTotalSectors;
}
K_sBlockIODevice_Disk_t;

// Register device struct
typedef struct {
    char *m_pszName;
    IOHandler *m_pHandler;
}
KIO_sRegisterIODevice_t;

// Mount device struct
typedef struct {
    K_sIODevice_t *m_psIODevice;
    char *m_pszData;
}
KIO_sDDKMount_t;

uint32 KIO_RegisterIODevice( char *pszName, IOHandler *pHandler, K_sIODevice_t *psDevice );

#endif // __K_KDDKIO_H__
