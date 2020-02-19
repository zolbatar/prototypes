#ifndef __API_MODULESMANAGER_H__
#define __API_MODULESMANAGER_H__

#include <API/Types.h>

#define MM_MAXPARAMETERS 16

#define MM_PARAMETERTYPE_NONE 0
#define MM_PARAMETERTYPE_UINT32 1
#define MM_PARAMETERTYPE_UINT32PTR 2
#define MM_PARAMETERTYPE_STRING 3
#define MM_PARAMETERTYPE_VOID 4

typedef struct {
    uint32 m_nCallingProcessID;
    uint32 m_nCallingThreadID;
    uint32 m_nParameterCount;
    uint32 m_nCurrentParameter;
    uint32 m_nValue[ MM_MAXPARAMETERS ];
    uint32 m_nType[ MM_MAXPARAMETERS ];
}
sParameterPackage_t;

static inline void MM_InitParameterBlock( sParameterPackage_t *psPackage ) {
    psPackage->m_nParameterCount = 0;
}

static inline void MM_AddParameterUINT32( sParameterPackage_t *psPackage, uint32 nValue ) {
    psPackage->m_nValue[ psPackage->m_nParameterCount ] = nValue;
    psPackage->m_nType[ psPackage->m_nParameterCount++ ] = MM_PARAMETERTYPE_UINT32;
}

static inline void MM_AddParameterUINT32PTR( sParameterPackage_t *psPackage, uint32 *nValue ) {
    psPackage->m_nValue[ psPackage->m_nParameterCount ] = ( uint32 ) nValue;
    psPackage->m_nType[ psPackage->m_nParameterCount++ ] = MM_PARAMETERTYPE_UINT32PTR;
}

static inline void MM_AddParameterSTRING( sParameterPackage_t *psPackage, char *pszString ) {
    psPackage->m_nValue[ psPackage->m_nParameterCount ] = ( uint32 ) pszString;
    psPackage->m_nType[ psPackage->m_nParameterCount++ ] = MM_PARAMETERTYPE_STRING;
}

static inline void MM_AddParameterVOIDPTR( sParameterPackage_t *psPackage, void *pAddress ) {
    psPackage->m_nValue[ psPackage->m_nParameterCount ] = ( uint32 ) pAddress;
    psPackage->m_nType[ psPackage->m_nParameterCount++ ] = MM_PARAMETERTYPE_VOID;
}

static inline uint32 MM_GetParameterUINT32( sParameterPackage_t *psPackage ) {
    return ( uint32 ) psPackage->m_nValue[ psPackage->m_nCurrentParameter++ ];
}

static inline uint32 *MM_GetParameterUINT32PTR( sParameterPackage_t *psPackage ) {
    return ( uint32 * ) psPackage->m_nValue[ psPackage->m_nCurrentParameter++ ];
}

static inline char *MM_GetParameterSTRING( sParameterPackage_t *psPackage ) {
    return ( char * ) psPackage->m_nValue[ psPackage->m_nCurrentParameter++ ];
}

static inline void * MM_GetParameterVOIDPTR( sParameterPackage_t *psPackage ) {
    return ( void * ) psPackage->m_nValue[ psPackage->m_nCurrentParameter++ ];
}

static inline KStatus MM_GetCallID( char *pszModule, char *pszModuleCall ) {
    uint32 nResult;
asm volatile( "int $0x80" : "=a" ( nResult ) : "a" ( pszModule ), "b" ( pszModuleCall ) );
    return nResult;
}

static inline KStatus MM_Call( uint32 nCode, sParameterPackage_t *psData ) {
    uint32 nResult;
asm volatile( "int $0x81" : "=a" ( nResult ) : "a" ( nCode ), "b" ( psData ) );
    return nResult;
}

// Errors
#define MM_INVALIDPARAMETER 0xFFFFFFFF
#define MM_INVALIDCALLID 0xFFFFFFFE
#define MM_INVALIDMODULE 0xFFFFFFFD

typedef int ModuleEntry( void );
typedef KStatus ModuleCall( sCallStack_t *psStack, sParameterPackage_t *pParameters );

#ifndef API_IN_KERNEL
namespace os {

class ModuleManager {
public:
    ModuleManager();
    ~ModuleManager();
    KStatus CreateModule( char *pszModule );
    KStatus CreateModuleCall( char *pszModule, char *pszCallName, ModuleCall *pHandler );

private:
    MMModuleCallID m_nCreateModule;
    MMModuleCallID m_nCreateModuleCall;
};

} // End namespace os
#endif

#endif // __API_MODULESMANAGER_H__
