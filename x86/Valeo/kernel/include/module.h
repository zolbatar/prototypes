#ifndef __MODULE_H__
#define __MODULE_H__

typedef struct {
    void *m_pAddress;
    uint32 m_nPages;
    uint32 m_nVersionMajor;
    uint32 m_nVersionMinor;
    OS_ModuleInterface *m_pInterface;
}
sModule_t;

void Module_Init( void );
KStatus Module_Add( void *pAddress, uint32 nPages, OS_sModuleDefinition_t *pDefinition );

#endif // __MODULE_H__

