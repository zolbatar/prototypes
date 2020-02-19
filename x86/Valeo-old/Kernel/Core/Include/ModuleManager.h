#ifndef __MODULEMANAGER_H__
#define __MODULEMANAGER_H__

typedef struct {
    ModuleCall *m_pHandler;
}
sModuleCall_t;

void ModuleManager_Init( void );
KStatus ModuleManager_CreateModule( char *pszName );
KStatus ModuleManager_CreateModuleCall( char *pszModuleName, char *pszCallName, ModuleCall *pHandler );
KStatus ModuleManager_Load( char *pszFilename );
void ModuleManager_CreateModuleInterface( void );

#endif // __MODULEMANAGER_H__
