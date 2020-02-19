#ifndef __API_INTERUPTMANAGER_H__
#define __API_INTERUPTMANAGER_H__

#include <API/Types.h>

typedef struct {
    uint32 sesp;
    uint16 sss, __sssu;
    uint32 edi;
    uint32 esi;
    uint32 ebp;
    uint32 edx;
    uint32 ecx;
    uint32 ebx;
    uint32 eax;
    uint16 ds, __dsh;
    uint16 es, __esh;
    uint16 fs, __fsh;
    uint16 gs, __gsh;
    uint32 eip;
    uint16 cs, __csh;
    uint32 eflags;
    uint32 esp;
    uint16 ss, __ssu;
}
sCallStack_t;

typedef KStatus IRQHandler( sCallStack_t *psStack );

#ifndef API_IN_KERNEL
namespace os {

class InterruptManager {
public:
    InterruptManager();
    ~InterruptManager();
    KStatus EnableInterrupt( uint32 nInterrupt );
    KStatus AttachHandler( char *pszName, uint32 nInterrupt, IRQHandler *pHandler );

private:
    MMModuleCallID m_nEnableInterrupt;
    MMModuleCallID m_nAttachHandler;
};

} // End namespace os
#endif

#endif // __API_INTERUPTMANAGER_H__
