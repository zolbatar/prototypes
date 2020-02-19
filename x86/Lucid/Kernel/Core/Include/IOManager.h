#ifndef __K_IOMANAGER_H__
#define __K_IOMANAGER_H__

#include <Types.h>
#include <CI-IO.h>

#define K_IOC_ENTRYSIZE 4096
#define K_IOC_PAGESPERENTRY (K_IOC_ENTRYSIZE / K_MM_PAGESIZE)

#define K_IOCACHE_INUSE (1 << 0)
#define K_IOCACHE_LOCKED (1 << 1)
#define K_IOCACHE_WAITINGFORUSE (1 << 2)
#define K_IOCACHE_DIRECTMAPPED (1 << 3)

#define K_ERR_

typedef struct {
    K_sIODevice_t *m_psIODevice;
    uint32 m_nStartBlock;
    uint32 m_nAge;
    uint32 m_nFlags;
}
K_sIOCache_t;

void IOManager_Init( void );
uint32 IOManager_RegisterIODevice( char *pszName, IOHandler *pHandler );
uint32 IOManager_RecalculateDevice( K_sIODevice_t *psDevice );
uint32 IOManager_Read( KIO_sRead_t *psData );
uint32 IOManager_MapCacheDirectPage( K_sIODevice_t *psIODevice, uint32 nPhysicalAddr, uint32 nPage );
uint32 IOManager_ReadFromBlock( K_sIODevice_t *psIODevice, uint32 nBlock, uint32 nOffset, uint32 nBytesNeeded, void *pBuffer );

#endif // __K_IOMANAGER_H__
