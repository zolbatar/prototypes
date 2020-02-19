#ifndef __OS_MODULE_H__
#define __OS_MODULE_H__

#define OS_MODULE_NAMELENGTH 32

// Main entry
typedef OS_KStatus OS_ModuleMain( void );
typedef OS_KStatus OS_ModuleInterface( void );

typedef struct {
    char m_szName[ OS_MODULE_NAMELENGTH ];
    uint32 m_nVersionMajor;
    uint32 m_nVersionMinor;
    OS_ModuleInterface *m_pInterface;
    OS_ModuleMain *m_pEntryPoint;
}
OS_sModuleDefinition_t;

// Initial entry point to get definition
typedef OS_sModuleDefinition_t *OS_ModuleEntry( void );

#endif // __OS_MODULE_H__
