#ifndef __K_CI_OBJECT_H__
#define __K_CI_OBJECT_H__

#include <Types.h>

typedef struct {
    char *m_pszName;
    uint32 m_nValue;
}
KObject_sGetSetEntityWord_t;

typedef struct {
    char *m_pszName;
    char *m_pszValue;
}
KObject_sGetSetEntityString_t;

#endif // __K_CI_OBJECT_H__
