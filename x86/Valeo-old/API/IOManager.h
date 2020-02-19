#ifndef __API_IOMANAGER_H__
#define __API_IOMANAGER_H__

#include <API/Types.h>

// Device struct
typedef struct {

    // Device definition
    bool m_bRemoveable;	       	   		       // Removable media?
    uint32 m_nTotalBlocks;     	   		       // Maximum blocks
    uint32 m_nBlockSize;     	   		       // Block size in bytes

    // Position
    uint32 m_nBlock;   	       	   		       // Position

    // I/O Cache settings
    uint32 m_nBlocksPerCacheEntry;

    // Calls
    void *m_pMountCall;
    void *m_pDismountCall;
}
sIODevice_t ;

// Function prototypes used for device drivers
typedef KStatus IORegisterCallBack( sIODevice_t *psIODevice );
typedef KStatus IOMountCall( sIODevice_t *psIODevice, char *pszData );
typedef KStatus IODismountCall( sIODevice_t *psIODevice );

// Errors
#define IOM_ERRORREADINGBLOCK 0xFFFFFFFF

#endif // __API_IOMANAGER_H__
