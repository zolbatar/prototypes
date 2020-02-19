#ifndef __K_KDEVICE_H__
#define __K_KDEVICE_H__

#include <Types.h>

enum {
    KDEVICE_RES_PORT,
    KDEVICE_RES_IRQ,
    KDEVICE_RES_DMA
};

#define KDEVICE_INVALIDDEVICE 0xFFFFFFFF

void KDevice_RegisterDevice( char *pszName );
void KDevice_AttachResource( char *pszName, uint32 m_nType, uint32 m_nValue );

#endif // __K_KDEVICE_H__
