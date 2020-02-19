#ifndef __DMMFILEIO_H__
#define __DMMFILEIO_H__

void DMMFileIO_Init( void );
KStatus DMMFileIO_RegisterIOCallback( sIODevice_t *psIODevice );
KStatus DMMFileIO_RegisterFilesystemCallback( sFilesystem_t *psFilesystem );
KStatus DMMFileIO_Mount( sIODevice_t *psIODevice, char *pszData );
KStatus DMMFileIO_Dismount( sIODevice_t *psIODevice );
KStatus DMMFileIO_Open( sVolume_t *psVolume, char *pszVolume, char *pszPath, char *pszFilename, sFileHandle_t *psFileHandle );
KStatus DMMFileIO_Read( sFileHandle_t *psHandle, void *pBuffer, uint32 nBytesNeeded, uint32 *nBytesRead );

#endif // __DMMFILEIO_H__
