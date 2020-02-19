#include <Kernel.h>

// Globals from Boot.S
extern uint32 KernelSize;
extern uint32 *PageDirectory;
extern uint32 *PageTables;
extern sIDT_t *idt;
extern sGDT_t *gdt;

// Globals
sKernel_t g_sKernel;
uint32 g_nLocksHeld = 0;
bool g_bKernelInitDone = false;

// Prototypes
void Kernel_ParseParameters( char *pszParameters );
void Kernel_ParseBootModules( sMBInfo_t *psMBInfo );
void Kernel_LoadBootModules();

void Kernel_Main ( sMBInfo_t *psMBInfo ) {

    // Copy values from Boot.S and put in the g_sKernel struct
    g_sKernel.m_nKernelSize = KernelSize;
    g_sKernel.m_nKernelEnd = ( void * ) ( MM_KERNELADDRPAGED + ( ( KernelSize + MM_KERNELSTACK + 2 ) << MM_PAGESIZESHIFT ) );
    g_sKernel.m_pnPageDirectory = PageDirectory;
    g_sKernel.m_pnPageTables = ( uint32 * ) MM_PAGETABLES;
    g_sKernel.m_pnPageTablePointers = PageTables;
    g_sKernel.m_sIDT = ( sIDT_t * ) & idt;
    g_sKernel.m_sGDT = ( sGDT_t * ) & gdt;

    // Save kernel parameters and parse
    Kernel_ParseParameters( ( char * ) psMBInfo->m_nCmdLine );

    // Setup console for debugging
    Console_Init();

    // Setup boot modules
    Kernel_ParseBootModules( psMBInfo );

    InterruptManager_Init();				// Init interrupt manager
    MemoryManager_Init( psMBInfo );			// Memory manager
    ModuleManager_Init();	 			// Module manager
    ObjectManager_Init();				// Object manager
    InterruptManager_CreateModuleInterface();		// Setup interrupt manager module calls
    MemoryManager_CreateModuleInterface();		// Setup memory manager module calls
    Console_CreateModuleInterface();			// Setup console module calls
    ModuleManager_CreateModuleInterface();		// Setup module manager calls
    DeviceManager_Init( );				// Init device manager
    PIC_Init();		  				// Init PIC
    PIT_Init();						// Init PIT
    TimerManager_Init();				// Init timer interface
    ProcessManager_Init();				// Init process manager
    MessageManager_Init();	  	      	    	// Init message manager
    IOManager_Init();					// Volume/FS/IO manager
    FS_Init();                                          // Initialise VFS

    // Now start interrupts and enable multi-tasking etc
    g_bKernelInitDone = true;

    // Load boot modules
    DMMFileIO_Init();                                   // Setup DMM to process boot modules
    Kernel_LoadBootModules();
    asm volatile ( "sti;" );

    // Kernel idle loop, basically to burn cycles if nothing to run
    while ( 1 ) {}

    // Shutdown
    KPrint( "KERNEL", "Halted now.\n" );
}

void Kernel_ParseParameters( char *pszParameters ) {

    // First off, scan until either the end or first space (get rid of kernel filename)
    uint32 i = 0;
    while ( pszParameters[ i ] != '\0' && !isspace( pszParameters[ i ] ) )
        i++;

    // If no parameters exit
    if ( pszParameters[ i ] == '\0' ) {
        // No parameters
    } else {

        bool bLast = false;
        uint32 nEnd;
        do {
            // Dump leading spaces
            while ( isspace( pszParameters[ i ] ) )
                i++;

            // Scan for end of command
            nEnd = i;
            while ( pszParameters[ nEnd ] != '\0' && !isspace( pszParameters[ nEnd ] ) )
                nEnd++;
            if ( pszParameters[ nEnd ] == '\0' ) {
                bLast = true;
            }

            // Now process command

            // Next
            i = nEnd;
        } while ( bLast == false );
    }
}

void Kernel_ParseBootModules( sMBInfo_t *psMBInfo ) {

    // Init kernel variables
    g_sKernel.m_nBootModuleCount = psMBInfo->m_nModsCount;
    g_sKernel.m_nBootModuleEnd = 0;

    // Too many boot modules?
    if ( g_sKernel.m_nBootModuleCount > K_BOOTMODULES_MAX ) {
        KPrint( "KERNEL", "Too many boot modules - Halting\n" );
        halt();
    }

    // Show how many modules
    KPrint( "KERNEL", "[%lu] boot module(s) found\n", g_sKernel.m_nBootModuleCount );

    // Now move modules out the way, we will come back to them later and load them in
    uint32 i;
    sMBModule_t *psModule = ( sMBModule_t * ) psMBInfo->m_nModsAddr;
    for ( i = 0; i < g_sKernel.m_nBootModuleCount; i++ ) {

        // Get position etc and save for later
        sBootModule_t *psKernelModule = &g_sKernel.m_pBootModules[ i ];
        psKernelModule->m_pStart = ( void * ) psModule->m_nStart;
        psKernelModule->m_pEnd = ( void * ) psModule->m_nEnd;
        psKernelModule->m_nLength = psModule->m_nEnd - psModule->m_nStart;

        // Move end of modules in physical memory pointer along
        g_sKernel.m_nBootModuleEnd = ( void * ) ( MM_PAGEALIGN( psKernelModule->m_pEnd ) + MM_PAGESIZE );

        // Debug prompt
        KPrint( "KERNEL", "Boot module found at [0x%X-0x%X] (%lu bytes)\n",
                psKernelModule->m_pStart, psKernelModule->m_pEnd, psKernelModule->m_nLength, g_sKernel.m_nBootModuleEnd );

        // Next module
        psModule = ( sMBModule_t * ) ( ( uint32 ) psModule + ( uint32 ) sizeof( sMBModule_t ) );
    }
}

void Kernel_LoadBootModules() {

    // Loop through all modules and map them into the virtual address space
    uint32 i;
    for ( i = 0; i < g_sKernel.m_nBootModuleCount; i++ ) {
        sBootModule_t *psKernelModule = &g_sKernel.m_pBootModules[ i ];

        // Debug prompt
        uint32 nPageCount = ( psKernelModule->m_nLength + 4095 ) >> MM_PAGESIZESHIFT;

        // Construct mount data command
        char szData[ 64 ];
        snprintf( ( char * ) & szData, 64, "0x%X/0x%X", ( uint32 ) psKernelModule->m_pStart, nPageCount );

        // Mount boot modules as DMM volume
        FS_Mount( "DMM:", "DMMBlockIO", "DMMFS", ( char * ) & szData );
        ModuleManager_Load( "DMM:/FILE" );
        FS_Unmount( "DMM:" );
    }
}

