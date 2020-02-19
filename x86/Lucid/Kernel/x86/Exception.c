// (C) Daryl Dudey 2002

#include <OSCalls.h>
#include <x86.h>
#include <Core.h>

// Fault 1
void Exception_Debug( K_sCallStack_t *psStack ) {

    // Debug fault: caused by trap bit in TSS
    KPrint( KDEBUG, "EXCEPTION", "Debug Fault from 0x%X:0x%X - Halting\n" , psStack->cs, psStack->eip );
}

// Fault 6
void Exception_InvalidOpCode( K_sCallStack_t *psStack ) {

    // Page fault: Need to map in page from VM
    KPrint( KDEBUG, "EXCEPTION", "Invalid Opcode from 0x%X:0x%X - Halting\n", psStack->cs, psStack->eip );
}

// Fault 8
void Exception_Double( K_sCallStack_t *psStack ) {

    // Page fault: Need to map in page from VM
    KPrint( KDEBUG, "EXCEPTION", "Double Fault from 0x%X:0x%X - Halting\n", psStack->cs, psStack->eip );
}

// Fault 12
void Exception_StackFault( K_sCallStack_t *psStack ) {

    // Debug fault: caused by trap bit in TSS
    KPrint( KDEBUG, "EXCEPTION", "Stack Fault from 0x%X:0x%X - Halting\n" , psStack->cs, psStack->eip );
}

// Fault 13
void Exception_Page( K_sCallStackWithErrorCode_t *psStack ) {

    // Get flags for page
    uint32 nCR2 = PAGE_ALIGN( GetCR2() );
    uint32 nPT = MemoryManager_GetPTAddress ( nCR2 );
    uint32 nPTOffset = ( nCR2 - nPT ) >> K_MM_PAGESIZESHIFT;
    nPT = nPT >> K_MM_PAGESIZESHIFT;
    uint32 nFlags = Kg_sKernel.m_pnPageTables[ nPT + nPTOffset ] & 0xE00;

    // What do we need to do?
    switch ( nFlags ) {
    case K_MM_PAGETYPE_ZEROFILL:
        MemoryManager_Page_Allocate( nCR2, true );
        break;
    default:
        KPrint( KSEVERE, "EXCEPTION", "Unhandled Page Fault at 0x%X from 0x%X:0x%X (Error 0x%X, Flags 0x%X)\n", nCR2, psStack->cs, psStack->eip, psStack->error, nFlags );
        halt();
        break;
    }
}

// Fault 14
void Exception_GPF( K_sCallStackWithErrorCode_t *psStack ) {

    // General protection fault: Serious error
    KPrint( KDEBUG, "EXCEPTION", "GPF from 0x%X:0x%X - Halting\n", psStack->cs, psStack->eip );
}


