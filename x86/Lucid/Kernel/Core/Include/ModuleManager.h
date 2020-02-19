#ifndef __K_MODULEMANAGER_H__
#define __K_MODULEMANAGER_H__

#include <Types.h>

typedef uint32 ModuleHandler( uint32 nCode, void *pData );

typedef struct {
    void *m_pHandler;
}
K_sModule_t;

void ModuleManager_Init( void );
uint32 ModuleManager_CreateModule( char *pszName, void *psHandler );
uint32 ModuleManager_CreateModuleCall( char *pszModuleName, char *pszCallName, uint32 nCode );
uint32 ModuleManager_Load( char *pszFilename );

#endif // __K_MODULEMANAGER_H__
