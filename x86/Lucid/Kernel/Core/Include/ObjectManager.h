#ifndef __K_OBJECTMANAGER_H__
#define __K_OBJECTMANAGER_H__

#include <Types.h>

#define OBJECTMANAGER_MAXKEYSTRINGSIZE 4096

typedef struct {
    char m_szName[ KOBJECT_ENTITYLENGTH ];
    uint32 m_nValueType;		   // Type of value i.e. string/number
    uint32 m_nValue;			   // Value (use specific)
    void *m_pData;			   // Pointer to data (used for strings)
}
K_sObjectEntity_t;

typedef struct K_sObject K_sObject_t;
struct K_sObject {
    char m_szName[ KOBJECT_NAMELENGTH ];
    uint32 m_nObjectIndex;  	 	   // Object index
    uint32 m_nTypeIndex;  	 	   // Index used by certain object types
    uint32 m_nTypeSubIndex;  	 	   // Sub-index used by certain object types
    uint32 m_nProcessID; 	       	   // Process ID of creator
    uint32 m_nThreadID; 	       	   // Thread ID of creator
    uint32 m_nClass;   	     	   	   // Object class (i.e module/resource)
    uint32 m_nReferenceCount;		   // handles held
    void *m_pData;			   // Pointer to data area
    K_sObject_t *m_psPrevious;		   // Pointer to previous in list
    K_sObject_t *m_psNext;		   // Pointer to next in list
};

void ObjectManager_Init( void );
void ObjectManager_Lock( void );
void ObjectManager_Unlock( void );
K_sObject_t *ObjectManager_CreateObject( uint32 nClass, uint32 nSize, char *pszName );
K_sObject_t *ObjectManager_SearchNameInClass( K_sObject_t *psStart, uint32 m_nClass, char *pszSearchString );
K_sObject_t *ObjectManager_SearchNameInClassTypeIndex( K_sObject_t *psStart, uint32 m_nClass, char *pszSearchString, uint32 nTypeIndex );
K_sObject_t *ObjectManager_SearchInClass( K_sObject_t *psStart, uint32 m_nClass );
K_sObject_t *ObjectManager_SearchInClassTypeIndex( K_sObject_t * psStart, uint32 m_nClass, uint32 nTypeIndex );
void ObjectManager_DeleteObject( K_sObject_t *psObject );
uint32 ObjectManager_CreateEntityWord( char *pszName, uint32 nValue );
uint32 ObjectManager_CreateEntityString( char *pszName, char *pszValue );

#endif // __K_OBJECTMANAGER_H__
