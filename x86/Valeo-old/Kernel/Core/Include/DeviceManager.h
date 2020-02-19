#ifndef __DEVICEMANAGER_H__
#define __DEVICEMANAGER_H__

typedef struct {
    uint32 m_nResourceType;
    uint32 m_nValue;
}
sResource_t;

void DeviceManager_Init( void );
KStatus DeviceManager_RegisterDevice( char *pszName );
KStatus DeviceManager_AttachResource( char *pszName, uint32 nType, uint32 nValue );
void DeviceManager_CreateModuleInterface( void );

#endif // __DEVICEMANAGER_H__
