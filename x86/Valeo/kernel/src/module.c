#include <Kernel.h>

void Module_Init( ) {

    // Create module object paths and object types
    Object_Lock();
    g_sKernel.m_psModules = Object_CreateDirectory( g_sKernel.m_psSystemRoot, "Modules" );
    g_sKernel.m_nTypeModule = Object_CreateType( "Module" );
    Object_Unlock();
}

KStatus Module_Add( void *pAddress, uint32 nPages, OS_sModuleDefinition_t *pDefinition ) {

    Object_Lock();

    // Create module object
    sObject_t * psObject = Object_CreateObject( g_sKernel.m_psModules, g_sKernel.m_nTypeModule, ( char * ) & pDefinition->m_szName, sizeof( sModule_t ) );

    // Create module data
    sModule_t *psModule = ( sModule_t * ) psObject->m_pData;
    psModule->m_pAddress = pAddress;
    psModule->m_nPages = nPages;
    psModule->m_nVersionMajor = pDefinition->m_nVersionMajor;
    psModule->m_nVersionMinor = pDefinition->m_nVersionMinor;
    psModule->m_pInterface = pDefinition->m_pInterface;

    Syslog_Lock();
    Syslog_Entry( "MODULE", "Loaded '%s', Version %lu.%lu at 0x%X\n", ( char * ) & pDefinition->m_szName, psModule->m_nVersionMajor, psModule->m_nVersionMinor, pAddress );
    Syslog_Unlock();

    Object_Unlock();

    return NULL;
}


