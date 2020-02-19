#include <OSCalls.h>
#include <CI-IO.h>

uint32 KIO_nHandle;
//uint32 KIO_nRegisterIODevice;

void KIO_Init() {

    // Get handle
    KIO_nHandle = KModule_GetHandle( "IOManager" );

    // Get call codes
    //    KIO_nRegisterIODevice = KModule_GetCallID( KIO_nHandle, "RegisterIODevice" );
}

