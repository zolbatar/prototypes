#ifndef __TIMER_H__
#define __TIMER_H__

typedef KStatus TimerHandler( sCallStack_t *psStack );

typedef struct sTimer sTimer_t;
struct sTimer {
    uint32 m_nPID;
    uint32 m_nTimeOut;
    uint32 m_nTimeOutLeft;
    TimerHandler *m_pHandler;
    sTimer_t *m_psPrevious;
};

void Timer_Init( void );
void Timer_AttachTimerHandler( uint32 nTimeOut, TimerHandler *pHandler );

#endif // __TIMER_H__
