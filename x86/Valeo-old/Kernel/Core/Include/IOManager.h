#ifndef __IOMANAGER_H__
#define __IOMANAGER_H__

#define IOM_ENTRYSIZE 4096
#define IOM_PAGESPERENTRY (IOM_ENTRYSIZE / MM_PAGESIZE)

#define IOM_IOCACHE_INUSE (1 << 0)
#define IOM_IOCACHE_LOCKED (1 << 1)
#define IOM_IOCACHE_WAITINGFORUSE (1 << 2)
#define IOM_IOCACHE_DIRECTMAPPED (1 << 3)

typedef struct {
    sIODevice_t *m_psIODevice;
    uint32 m_nStartBlock;
    uint32 m_nAge;
    uint32 m_nFlags;
}
sIOCache_t;

void IOManager_Init( void );
void IOManager_Lock( void );
void IOManager_Unlock( void );
KStatus IOManager_RegisterIODevice( char *pszName, IORegisterCallBack *pCallback );
KStatus IOManager_RecalculateDevice( sIODevice_t *psDevice );
KStatus IOManager_Read( sFileHandle_t *psHandle, void *pBuffer, uint32 nBytesNeeded, uint32 *nBytesRead );
KStatus IOManager_MapCacheDirectPage( sIODevice_t *psIODevice, uint32 nPhysicalAddr, uint32 nPage );
KStatus IOManager_UnmapCacheDirectPage( sIODevice_t *psIODevice, uint32 nPage );

#endif // __IOMANAGER_H__
