#ifndef __API_DEVICEMANAGER_H__
#define __API_DEVICEMANAGER_H__

#include <API/Types.h>

enum {
    DM_PORT,
    DM_IRQ,
    DM_DMA
};

// Errors
#define DM_INVALIDDEVICE 0xFFFFFFFF

#ifndef API_IN_KERNEL
namespace os {

class DeviceManager {
public:
    DeviceManager();
    ~DeviceManager();
    KStatus RegisterDevice( char *pszName );
    KStatus AttachResource( char *pszName, uint32 nType, uint32 nValue );

private:
    MMModuleCallID m_nRegisterDevice;
    MMModuleCallID m_nAttachResource;
};

} // End namespace os
#endif

#endif // __API_DEVICEMANAGER_H__
