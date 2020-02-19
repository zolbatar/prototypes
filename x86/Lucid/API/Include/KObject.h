#ifndef __K_KOBJECT_H__
#define __K_KOBJECT_H__

#include <Types.h>

enum {
    KOBJECT_OBJ_ENTITY,
    KOBJECT_OBJ_PROCESS,
    KOBJECT_OBJ_THREAD,
    KOBJECT_OBJ_MODULEHANDLE,
    KOBJECT_OBJ_MODULE,
    KOBJECT_OBJ_MODULECALL,
    KOBJECT_OBJ_MESSAGEPORT,
    KOBJECT_OBJ_MESSAGE,
    KOBJECT_OBJ_DEVICE,
    KOBJECT_OBJ_DEVICERESOURCE,
    KOBJECT_OBJ_IODEVICE,
    KOBJECT_OBJ_FILESYSTEM,
    KOBJECT_OBJ_VOLUME,
    KOBJECT_OBJ_FILEHANDLE
};

#define KOBJECT_NAMELENGTH 48
#define KOBJECT_ENTITYLENGTH 256
#define KOBJECT_MAXKEYSTRINGSIZE 4096
#define KOBJECT_OBJECTNOTFOUND 0xFFFFFFFF

uint32 KObject_GetEntityWord( char *pszName, uint32 *nValue );
uint32 KObject_GetEntityStringLength( char *pszName, uint32 *nValue );
uint32 KObject_GetEntityString( char *pszName, char *pszValue );
uint32 KObject_CreateEntityWord( char *pszName, uint32 nValue );
uint32 KObject_CreateEntityString( char *pszName, char *pszValue );

#endif // __K_KOBJECT_H__
