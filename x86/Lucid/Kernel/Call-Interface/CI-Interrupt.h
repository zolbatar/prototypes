#ifndef __K_CI_Interrupt_H__
#define __K_CI_Interrupt_H__

#include <Types.h>

typedef struct {
    char *m_pszName;
    uint16 m_nInterrupt;
    void *m_pHandler;
}
KInterrupt_sAttachHandler_t;

typedef struct {
    uint16 m_nInterrupt;
}
KInterrupt_sIRQ_t;

#endif // __K_CI_Interrupt_H__

