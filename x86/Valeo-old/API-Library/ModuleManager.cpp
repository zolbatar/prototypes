#include <API/Valeo-API.h>

using namespace os;

ModuleManager::ModuleManager() {
    m_nCreateModule = MM_GetCallID( "ModuleManager", "CreateModule" );
    m_nCreateModuleCall = MM_GetCallID( "ModuleManager", "CreateModuleCall" );
}

ModuleManager::~ModuleManager() {}

KStatus ModuleManager::CreateModule( char *pszModule ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterSTRING( &sPackage, pszModule );
    return MM_Call( m_nCreateModule, &sPackage );
}

KStatus ModuleManager::CreateModuleCall( char *pszModule, char *pszCallName, ModuleCall *pHandler ) {
    sParameterPackage_t sPackage;
    MM_InitParameterBlock( &sPackage );
    MM_AddParameterSTRING( &sPackage, pszModule );
    MM_AddParameterSTRING( &sPackage, pszCallName );
    MM_AddParameterVOIDPTR( &sPackage, ( void * ) pHandler );
    return MM_Call( m_nCreateModuleCall, &sPackage );
}


