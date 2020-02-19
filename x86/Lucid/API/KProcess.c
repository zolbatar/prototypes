#include <OSCalls.h>
#include <CI-Process.h>

uint32 Process_nHandle;
uint32 Process_nCreateProcess;
uint32 Process_nCreateThread;
uint32 Process_nSleep;
uint32 Process_nAwaken;
uint32 Process_nRelinquish;

void KProcess_Init() {

    // Get handle
    Process_nHandle = KModule_GetHandle( "ProcessManager" );

    // Get call codes
    Process_nCreateProcess = KModule_GetCallID( Process_nHandle, "CreateProcess" );
    Process_nCreateThread = KModule_GetCallID( Process_nHandle, "CreateThread" );
    Process_nSleep = KModule_GetCallID( Process_nHandle, "Sleep" );
    Process_nAwaken = KModule_GetCallID( Process_nHandle, "Awaken" );
    Process_nRelinquish = KModule_GetCallID( Process_nHandle, "Relinquish" );
}

uint32 KProcess_CreateThread( void *nEIP ) {

    // Check if initialised
    if ( Process_nHandle == NULL )
        KProcess_Init();

    KProcess_sCreateThread_t sData;
    sData.m_nEIP = nEIP;
    return KModule_Call( Process_nHandle, Process_nCreateThread, &sData );
}

uint32 KProcess_Sleep( uint32 nTimeOut ) {

    // Check if initialised
    if ( Process_nHandle == NULL )
        KProcess_Init();

    KProcess_sSleep_t sData;
    sData.m_nTimeOut = nTimeOut;
    return KModule_Call( Process_nHandle, Process_nSleep, &sData );
}

uint32 KProcess_Awaken( uint32 nThreadID ) {

    // Check if initialised
    if ( Process_nHandle == NULL )
        KProcess_Init();

    KProcess_sAwaken_t sData;
    sData.m_nThreadID = nThreadID;
    return KModule_Call( Process_nHandle, Process_nAwaken, &sData );
}

uint32 KProcess_Relinquish() {

    // Check if initialised
    if ( Process_nHandle == NULL )
        KProcess_Init();

    return KModule_Call( Process_nHandle, Process_nRelinquish, NULL );
}

