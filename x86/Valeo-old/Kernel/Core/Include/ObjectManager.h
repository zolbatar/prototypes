#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

typedef struct sObject sObject_t;
struct sObject {
    char m_szName[ OM_NAMELENGTH ];
    uint32 m_nObjectIndex;  	 	   // Object index
    uint32 m_nTypeIndex;  	 	   // Index used by certain object types
    uint32 m_nTypeSubIndex;  	 	   // Sub-index used by certain object types
    uint32 m_nProcessID; 	       	   // Process ID of creator
    uint32 m_nThreadID; 	       	   // Thread ID of creator
    uint32 m_nClass;   	     	   	   // Object class (i.e module/resource)
    uint32 m_nReferenceCount;		   // handles held
    void *m_pData;			   // Pointer to data area
    sObject_t *m_psPrevious;		   // Pointer to previous in list
    sObject_t *m_psNext;		   // Pointer to next in list
};

void ObjectManager_Init( void );
void ObjectManager_Lock( void );
void ObjectManager_Unlock( void );
void ObjectManager_ConstructPath( char *pszPathComponent );
void ObjectManager_ConstructPathAppend( char *pszPathComponent );
void ObjectManager_ConstructKey( char *pszKeyComponent );
void ObjectManager_ConstructKeyAppend( char *pszKeyComponent );
sObject_t *ObjectManager_CreateObject( uint32 nClass, uint32 nSize );
sObject_t *ObjectManager_GetStart( sObject_t *psStart );
sObject_t *ObjectManager_SearchNameInClass( sObject_t *psStart, uint32 m_nClass );
sObject_t *ObjectManager_SearchNameInClassTypeIndex( sObject_t *psStart, uint32 m_nClass, uint32 nTypeIndex );
sObject_t *ObjectManager_SearchInClass( sObject_t *psStart, uint32 m_nClass );
sObject_t *ObjectManager_SearchInClassTypeIndex( sObject_t * psStart, uint32 m_nClass, uint32 nTypeIndex );
sObject_t *ObjectManager_SearchInClassTypeSubIndex( sObject_t * psStart, uint32 m_nClass, uint32 nTypeSubIndex );
sObject_t *ObjectManager_GetObjectContainingData( void *pData );
void ObjectManager_DeleteObject( sObject_t *psObject );
KStatus ObjectManager_CreateEntityWord( uint32 nValue );
KStatus ObjectManager_CreateEntityString( char *pszValue );
KStatus ObjectManager_GetEntityWord( uint32 *pnValue );
KStatus ObjectManager_GetEntityStringLength( uint32 *pnValue );
KStatus ObjectManager_GetEntityString( char *pszValue );

#endif // __OBJECTMANAGER_H__
