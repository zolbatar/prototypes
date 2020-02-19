#ifndef __K_TIMER_H__
#define __K_TIMER_H__

#include <Types.h>

typedef bool TimerHandler( );

typedef struct K_sTimer K_sTimer_t;
struct K_sTimer {
    char m_szName[ KOBJECT_ENTITYLENGTH ];
    uint32 m_nIndex;
    uint32 m_nTimeOut;
    uint32 m_nTimeOutLeft;
    TimerHandler *m_pHandler;
    K_sTimer_t *m_psPrevious;
};

void TimerManager_Init( void );
void TimerManager_AttachTimerHandler( char *pszName, uint32 nTimeOut, TimerHandler *pHandler );

#endif // __K_TIMER_H__
