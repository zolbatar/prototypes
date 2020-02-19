#ifndef __OBJECT_H__
#define __OBJECT_H__

#define OBJECT_NAMELENGTH 48

// Object item struct
typedef struct sObject sObject_t;
struct sObject {
    uint32 m_nPID;
    uint32 m_nType;
    char m_szName[ OBJECT_NAMELENGTH ];
    void *m_pData;
    sObject_t *m_psPrevious;
    sObject_t *m_psNext;
};

// Object type WORD
typedef struct {
    uint32 m_nPID;
    uint32 m_nType;
    char m_szName[ OBJECT_NAMELENGTH ];
    uint32 *m_pWord;
    sObject_t *m_psPrevious;
    sObject_t *m_psNext;
}
sObjectWord_t;

// Object directory struct
typedef struct sObjectDirectory sObjectDirectory_t;
struct sObjectDirectory {
    uint32 m_nPID;
    sObject_t *m_psObjectHead;
    sObject_t *m_psObjectTail;
};

// Object type struct
typedef struct {
    uint32 m_nPID;
    char m_szName[ OBJECT_NAMELENGTH ];
    uint32 m_nType;
}
sObjectType_t;

void Object_Init( void );
void Object_Lock( void );
void Object_Unlock( void );

// Create types/objects/directories
uint32 Object_CreateType( char *pszName );
sObjectDirectory_t *Object_CreateDirectory( sObjectDirectory_t *psDirectory, char *pszName );
sObject_t *Object_CreateObject( sObjectDirectory_t *psDirectory, uint32 nType, char *pszName, uint32 nSizeOfData );
sObjectWord_t *Object_CreateObjectWord( sObjectDirectory_t *psDirectory, char *pszName, uint32 *nValuePtr );
KStatus Object_Delete( sObjectDirectory_t *psDirectory, sObject_t *psObject );

// Searching for objects
sObjectDirectory_t *Object_GetObjectPath( sObjectDirectory_t * psPath, char *pszObjectPath, uint32 nPathLength, uint32 nIndex );
sObject_t *Object_GetObject( char *pszObjectPath, char *pszObjectName, uint32 nType );
void *Object_GetObjectData( char *pszObjectPath, char *pszObjectName, uint32 nType );

// Debug routines
#ifdef DEBUG
void Object_DumpTree( void );
#endif

#endif // __OBJECT_H__
