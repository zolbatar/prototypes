// Lucid - Operating System Project
// (C) Daryl Dudey 2002

#include <All.h>

void RAMFSDevice_Init() {
    // Create device and attach
    Kg_sKernel.m_psRAMFSDevice = ( K_sKBlockIODevice_t * ) MemoryManager_KAlloc( sizeof( K_sKBlockIODevice_t ) );
    Kg_sKernel.m_psRAMFSDevice->m_pHandler = RAMFSDevice_Handler;
    snprintf( Kg_sKernel.m_psRAMFSDevice->m_szName, 32, "RAMFSDEV" );
    snprintf( Kg_sKernel.m_psRAMFSDevice->m_szDescription, 32, "RAMFS Device" );
    Kg_sKernel.m_psRAMFSDevice->m_nTotalBlocks = 0;
    Kg_sKernel.m_psRAMFSDevice->m_nBlockSize = 4096;
    Kg_sKernel.m_psRAMFSDevice->m_bRemoveable = false;
    BlockIO_AttachDevice( Kg_sKernel.m_psRAMFSDevice );

    // Create worker thread
    Kg_sKernel.m_psRAMFSDeviceThread = ( K_sThread_t * ) MemoryManager_KAlloc( sizeof( K_sThread_t ) );
    snprintf( Kg_sKernel.m_psRAMFSDeviceThread->m_szName, 32, "RAMFS Device I/O Worker" );
    K_sCallStack_t *psStack = &Kg_sKernel.m_psRAMFSDeviceThread->m_sStack;
    psStack->eip = ( uint32 ) & RAMFSDevice_Worker;
    Scheduler_AttachThread( Kg_sKernel.m_psKernelProcess, Kg_sKernel.m_psRAMFSDeviceThread );

    Console_Print( K_CIO_DEBUG, "RAMFSDEV", "RAMFS Device initialised\n" );
    //    LucidIO_Volume_Mount( ":RAM0", "RAMFSDEV", "RAMFS", "0x400000" );
}

bool RAMFSDevice_Handler( K_sKBlockIODevice_t *psDevice ) {
    switch ( psDevice->m_nCommand ) {
    case LUCIDIO_RESET:
        return true;

    case LUCIDIO_FETCHBLOCK:
        return true;
    }

    // Return with error
    return false;
}

void RAMFSDevice_Worker() {
    while ( 1 ) {
        Kg_pConsoleVideo[ 0 ] = '2';
        //        Scheduler_Sleep( Kg_sKernel.m_psRAMFSDeviceThread, 10 );
        //	  Scheduler_Switch();
    }
}

