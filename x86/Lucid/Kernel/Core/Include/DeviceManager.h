#ifndef __K_DEVICEMANAGER_H__
#define __K_DEVICEMANAGER_H__

#include <Types.h>

typedef struct {
    uint32 m_nResourceType;
    uint32 m_nValue;
}
K_sResource_t;

void DeviceManager_Init( void );
uint32 DeviceManager_RegisterDevice( char *pszName );
uint32 DeviceManager_AttachResource( char *pszName, uint32 nType, uint32 nValue );

#endif // __K_DEVICEMANAGER_H__
