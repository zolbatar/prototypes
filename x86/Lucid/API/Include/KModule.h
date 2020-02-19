#ifndef __K_KMODULES_H__
#define __K_KMODULES_H__

#include <Types.h>

#define KMODULE_INVALIDPARAMETER 0xFFFFFFFF
#define KMODULE_MODULENOTFOUND 0xFFFFFFFE
#define KMODULE_INVALIDHANDLE 0xFFFFFFFD
#define KMODULE_INVALIDCALL 0xFFFFFFFC
#define KMODULE_CALLNOTFOUND 0xFFFFFFFB

static inline uint32 KModule_GetHandle( const char *pszModule ) {
    uint32 nResult;
asm volatile( "int $0x80" : "=a" ( nResult ) : "a" ( pszModule ) );
    return nResult;
}

static inline uint32 KModule_ReleaseHandle( uint32 nHandle ) {
    uint32 nResult;
asm volatile( "int $0x81" : "=a" ( nResult ) : "a" ( nHandle ) );
    return nResult;
}

static inline uint32 KModule_GetCallID( uint32 nHandle, const char *pszModule ) {
    uint32 nResult;
asm volatile( "int $0x82" : "=a" ( nResult ) : "a" ( nHandle ), "b" ( pszModule ) );
    return nResult;
}

static inline uint32 KModule_Call( uint32 nHandle, uint32 nCode, void *pData ) {
    uint32 nResult;
asm volatile( "int $0x83" : "=a" ( nResult ) : "a" ( nHandle ), "b" ( nCode ), "c" ( pData ) );
    return nResult;
}

static inline uint32 KModule_CreateModule( char *pszName, void *psHandler ) {
    uint32 nResult;
asm volatile( "int $0x84" : "=a" ( nResult ) : "a" ( pszName ), "b" ( psHandler ) );
    return 0;
}

static inline uint32 KModule_CreateModuleCall( char *pszModuleName, char *pszCallName, uint32 nCode ) {
    uint32 nResult;
asm volatile( "int $0x85" : "=r" ( nResult ) : "a" ( pszModuleName ), "b" ( pszCallName ), "c" ( nCode ) );
    return 0;
}

#endif // __K_KMODULES_H__
