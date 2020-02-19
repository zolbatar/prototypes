#include <Kernel.h>

static inline void TraceDumpStackWithError( sCallStackWithErrorCode_t *psStack ) {

    // Dump registers
    Syslog_Entry( NULL, "EAX: 0x%X  EBX: 0x%X  ECX: 0x%X  EDX: 0x%X\n", psStack->eax, psStack->ebx, psStack->ecx, psStack->edx );
    Syslog_Entry( NULL, "EBP: 0x%X  ESP: 0x%X  ESI: 0x%X  EDI: 0x%X\n\n", psStack->ebp, psStack->esp, psStack->esi, psStack->edi );

    // Do a stack trace
    uint32 *pStack = ( uint32 * ) psStack->esp;
    uint32 n, i;
    for ( i = 0;i < 32; i++ ) {
        n = pStack[ i ];
        Syslog_Entry( NULL, "0x%08X: 0x%08X", i * 4, n );
        n = pStack[ i++ ];
        Syslog_Entry( NULL, " 0x%08X", n );
        n = pStack[ i++ ];
        Syslog_Entry( NULL, " 0x%08X", n );
        n = pStack[ i++ ];
        Syslog_Entry( NULL, " 0x%08X\n", n );
    }
}

// Fault 1
void Exception_Debug( sCallStack_t *psStack ) {

    // Debug fault: caused by trap bit in TSS
    Syslog_Entry( "EXCEPTION", "Debug Fault from 0x%X:0x%X - Halting\n" , psStack->cs, psStack->eip );
}

// Fault 6
void Exception_InvalidOpCode( sCallStack_t *psStack ) {

    // Page fault: Need to map in page from VM
    Syslog_Entry( "EXCEPTION", "Invalid Opcode from 0x%X:0x%X - Halting\n", psStack->cs, psStack->eip );
}

// Fault 8
void Exception_Double( sCallStack_t *psStack ) {

    // Page fault: Need to map in page from VM
    Syslog_Entry( "EXCEPTION", "Double Fault from 0x%X:0x%X - Halting\n", psStack->cs, psStack->eip );
}

// Fault 12
void Exception_StackFault( sCallStack_t *psStack ) {

    // Debug fault: caused by trap bit in TSS
    Syslog_Entry( "EXCEPTION", "Stack Fault from 0x%X:0x%X - Halting\n" , psStack->cs, psStack->eip );
}

// Fault 13
void Exception_Page( sCallStackWithErrorCode_t *psStack ) {

    // Get flags for page
    uint32 nCR2 = MM_PAGEALIGN( GetCR2() );
    uint32 nPT = MM_GetPTAddress ( nCR2 );
    uint32 nPTOffset = ( nCR2 - nPT ) >> MM_PAGESIZESHIFT;
    nPT = nPT >> MM_PAGESIZESHIFT;
    uint32 nFlags = MM_PAGETYPE_GET( g_sKernel.m_pnPageTables[ nPT + nPTOffset ] );

    // What do we need to do?
    switch ( nFlags ) {
    case MM_PAGETYPE_ZEROFILL:
        MM_Page_Allocate( nCR2, true );
        break;
    case MM_PAGETYPE_UNDEFINED:
        MM_Page_Allocate( nCR2, true );
        break;
    default:
        Syslog_Entry( "EXCEPTION", "Unhandled Page Fault at 0x%X from 0x%X:0x%X (Error 0x%X, Flags 0x%X)\n", nCR2, psStack->cs, psStack->eip, psStack->error, nFlags );
        halt();
        break;
    }
}

// Fault 14
void Exception_GPF( sCallStackWithErrorCode_t *psStack ) {

    // General protection fault: Serious error
    Syslog_Entry( "EXCEPTION", "GPF from 0x%X:0x%X - Halting\n", psStack->cs, psStack->eip );
    halt();
}


