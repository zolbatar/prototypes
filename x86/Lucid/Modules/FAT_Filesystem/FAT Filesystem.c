// Lucid - Operating System Project
// (C) Daryl Dudey 2002

#include <All.h>

void RAMFilesystem_Init() {

    // Create file system and attach
    Kg_sKernel.m_psRAMFilesystem = ( K_sFilesystem_t * ) MemoryManager_KAlloc( sizeof( K_sFilesystem_t ) );
    Kg_sKernel.m_psRAMFilesystem->m_pHandler = RAMFilesystem_FSHandler;
    snprintf( Kg_sKernel.m_psRAMFilesystem->m_szName, 32, "RAMFS" );
    snprintf( Kg_sKernel.m_psRAMFilesystem->m_szDescription, 32, "RAM File system" );
    VolumeManager_AttachFSSupport( Kg_sKernel.m_psRAMFilesystem );

    // Create worker thread
    Kg_sKernel.m_psRAMFilesystemThread = ( K_sThread_t * ) MemoryManager_KAlloc( sizeof( K_sThread_t ) );
    snprintf( Kg_sKernel.m_psRAMFilesystemThread->m_szName, 32, "RAM Filesystem Worker" );
    K_sCallStack_t *psStack = &Kg_sKernel.m_psRAMFilesystemThread->m_sStack;
    psStack->eip = ( uint32 ) & RAMFilesystem_Worker;
    Scheduler_AttachThread( Kg_sKernel.m_psKernelProcess, Kg_sKernel.m_psRAMFilesystemThread );

    Console_Print( K_CIO_DEBUG, "RAMFS", "RAM Filesystem initialised\n" );
}

bool RAMFilesystem_FSHandler( K_sKBlockIODevice_t *psDevice ) {
    switch ( psDevice->m_nCommand ) {}

    // Return with error
    return false;
}

void RAMFilesystem_Worker() {
    while ( 1 ) {
        Kg_pConsoleVideo[ 0 ] = '0';
        //        Scheduler_Sleep( Kg_sKernel.m_psRAMFilesystemThread, 10 );
        //	Scheduler_Switch();
    }
}


