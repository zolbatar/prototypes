#ifndef __K_CI_IO_H__
#define __K_CI_IO_H__

#include <Types.h>

// Read struct
typedef struct {
    K_sFileHandle_t *m_psHandle;
    void *m_pBuffer;
    uint32 m_nBytesNeeded;
    uint32 *m_nBytesRead;
}
KIO_sRead_t;

#endif // __K_CI_IO_H__
