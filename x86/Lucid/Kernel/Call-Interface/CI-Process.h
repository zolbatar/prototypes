#ifndef __K_CI_PROCESS_H__
#define __K_CI_PROCESS_H__

#include <Types.h>

typedef struct {
    void *m_nEIP;
}
KProcess_sCreateThread_t;

typedef struct {
    uint32 m_nTimeOut;
}
KProcess_sSleep_t;

typedef struct {
    uint32 m_nThreadID;
}
KProcess_sAwaken_t;

#endif // __K_CI_PROCESS_H__
