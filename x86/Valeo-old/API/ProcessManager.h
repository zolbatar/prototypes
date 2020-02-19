#ifndef __API_PROCESSMANAGER_H__
#define __API_PROCESSMANAGER_H__

#include <API/Types.h>

#define PM_THREADPRIORITY_REALTIME 31
#define PM_THREADPRIORITY_HIGH 24
#define PM_THREADPRIORITY_NORMAL 16
#define PM_THREADPRIORITY_LOW 8
#define PM_THREADPRIORITY_IDLE 1

#define PM_NAMELENGTH 128

#define PM_SLEEPFOREVER 0

#ifndef API_IN_KERNEL
namespace os {

class ProcessManager {
public:
    ProcessManager();
    ~ProcessManager();
    KStatus CreateThread( void *nEIP, uint32 *nTID );
    KStatus RunThread( uint32 nTID );
    KStatus AwakenThread( uint32 nTID );
    KStatus Sleep( uint32 nTime );
    KStatus Relinquish( void );

private:
    MMModuleCallID m_nCreateThread;
    MMModuleCallID m_nRunThread;
    MMModuleCallID m_nAwakenThread;
    MMModuleCallID m_nSleep;
    MMModuleCallID m_nRelinquish;
};

} // End namespace os
#endif

#endif // __API_PROCESSMANAGER_H__
