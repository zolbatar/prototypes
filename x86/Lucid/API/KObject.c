#include <OSCalls.h>
#include <CI-Object.h>

uint32 Object_nHandle;
uint32 Object_nGetKeyValue;
uint32 Object_nGetKeyStringLength;
uint32 Object_nGetKeyString;
uint32 Object_nCreateKeyWord;
uint32 Object_nCreateKeyString;

void KObject_Init() {

    // Get handle
    Object_nHandle = KModule_GetHandle( "ObjectManager" );

    // Get call codes
    Object_nGetKeyValue = KModule_GetCallID( Object_nHandle, "GetKeyWord" );
    Object_nGetKeyStringLength = KModule_GetCallID( Object_nHandle, "GetKeyStringLength" );
    Object_nGetKeyString = KModule_GetCallID( Object_nHandle, "GetKeyString" );
    Object_nCreateKeyWord = KModule_GetCallID( Object_nHandle, "CreateKeyWord" );
    Object_nCreateKeyString = KModule_GetCallID( Object_nHandle, "CreateKeyString" );
}

uint32 KObject_GetEntityWord( char *pszName, uint32 *nValue ) {

    // Check if initialised
    if ( Object_nHandle == NULL )
        KObject_Init();

    KObject_sGetSetEntityWord_t sData;
    sData.m_pszName = pszName;
    uint32 nReturn = KModule_Call( Object_nHandle, Object_nGetKeyValue, &sData );
    *nValue = sData.m_nValue;
    return nReturn;
}

uint32 KObject_GetEntityStringLength( char *pszName, uint32 *nValue ) {

    // Check if initialised
    if ( Object_nHandle == NULL )
        KObject_Init();

    KObject_sGetSetEntityWord_t sData;
    sData.m_pszName = pszName;
    uint32 nReturn = KModule_Call( Object_nHandle, Object_nGetKeyStringLength, &sData );
    *nValue = sData.m_nValue;
    return nReturn;
}

uint32 KObject_GetEntityString( char *pszName, char *pszValue ) {

    // Check if initialised
    if ( Object_nHandle == NULL )
        KObject_Init();

    KObject_sGetSetEntityString_t sData;
    sData.m_pszName = pszName;
    sData.m_pszValue = pszValue;
    uint32 nReturn = KModule_Call( Object_nHandle, Object_nGetKeyStringLength, &sData );
    return nReturn;
}

uint32 KObject_CreateEntityWord( char *pszName, uint32 nValue ) {

    // Check if initialised
    if ( Object_nHandle == NULL )
        KObject_Init();

    KObject_sGetSetEntityWord_t sData;
    sData.m_pszName = pszName;
    sData.m_nValue = nValue ;
    return KModule_Call( Object_nHandle, Object_nCreateKeyWord, &sData );
}

uint32 KObject_CreateEntityString( char *pszName, char *pszValue ) {

    // Check if initialised
    if ( Object_nHandle == NULL )
        KObject_Init();

    KObject_sGetSetEntityString_t sData;
    sData.m_pszName = pszName;
    sData.m_pszValue = pszValue;
    return KModule_Call( Object_nHandle, Object_nCreateKeyString, &sData );
}


