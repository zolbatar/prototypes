#ifndef __TIMER_H__
#define __TIMER_H__

#include <Types.h>

typedef KStatus TimerHandler( sCallStack_t *psStack );

typedef struct sTimer sTimer_t;
struct sTimer {
    char m_szName[ OM_NAMELENGTH ];
    uint32 m_nIndex;
    uint32 m_nTimeOut;
    uint32 m_nTimeOutLeft;
    TimerHandler *m_pHandler;
    sTimer_t *m_psPrevious;
};

void TimerManager_Init( void );
void TimerManager_AttachTimerHandler( char *pszName, uint32 nTimeOut, TimerHandler *pHandler );

#endif // __TIMER_H__
