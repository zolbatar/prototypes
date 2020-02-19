#ifndef __K_KINTERRUPT_H__
#define __K_KINTERRUPT_H__

#include <Types.h>

void KInterrupt_AttachHandler( char *pszName, uint16 nInterrupt, void *pHandler );
void KInterrupt_EnableInterrupt( uint16 nInterrupt );

#endif // __K_KINTERRUPT_H__
