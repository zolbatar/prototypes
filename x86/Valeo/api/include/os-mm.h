#ifndef __OS_MM_H__
#define __OS_MM_H__

static inline uint32 OS_MM_GetDataAreaSize( void ) {

    // Call kernel function
    uint32 nEAX = OS_MM_GETDATAAREASIZE;
    OS_KStatus nPages;
asm volatile( "int $0x80" : "=a" ( nPages ) : "a" ( nEAX ) );

    return nPages;
}

#endif // __OS_MM_H__
