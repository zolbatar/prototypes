#ifndef __LOCKING_H__
#define __LOCKING_H__

#define LOCKING_NAMELENGTH 48

// Locking struct
typedef struct {
    sSpinlock_t m_sSpinlock;
    char m_szName[ LOCKING_NAMELENGTH ];
}
sLock_t;

void Lock_Init( char *pszName, sLock_t *psLock );
void Lock_Lock( sLock_t *psLock );
void Lock_Unlock( sLock_t * psLock );

#endif // __LOCKING_H__
