#ifndef __K_KPROCESS_H__
#define __K_KPROCESS_H__

#include <Types.h>

#define KPROCESS_THREADPRIORITY_REALTIME 31
#define KPROCESS_THREADPRIORITY_HIGH 24
#define KPROCESS_THREADPRIORITY_NORMAL 16
#define KPROCESS_THREADPRIORITY_LOW 8
#define KPROCESS_THREADPRIORITY_IDLE 1

#define KPROCESS_SLEEPFOREVER 0

uint32 KProcess_CreateThread( void *nEIP );
uint32 KProcess_Sleep( uint32 nTimeOut );
uint32 KProcess_Awaken( uint32 nThreadID );
uint32 KProcess_Relinquish( void );

#endif // __K_KPROCESS_H__
