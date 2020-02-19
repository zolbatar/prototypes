#ifndef __API_MEMORYMANAGER_H__
#define __API_MEMORYMANAGER_H__

#include <API/Types.h>

#ifndef API_IN_KERNEL

static inline void *MemoryNew( size_t nBytes ) {
    void * nResult;
asm volatile( "int $0x90" : "=a" ( nResult ) : "a" ( nBytes ) );
    return nResult;
}

static inline void MemoryFree( void *pPtr ) {
asm volatile( "int $0x91" : : "a" ( pPtr ) );
}

static inline void *operator new ( size_t nBytes ) {
    return MemoryNew( nBytes );
};

static inline void *operator new[] ( size_t nBytes ) {
    return MemoryNew( nBytes );
};

static inline void operator delete ( void *pAddress ) {
    MemoryFree( pAddress );
}

static inline void operator delete[] ( void *pAddress ) {
    MemoryFree( pAddress );
}

#endif

#endif // __API_MEMORYMANAGER_H__
