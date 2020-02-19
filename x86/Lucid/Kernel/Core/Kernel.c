#include <OSCalls.h>
#include <x86.h>
#include <Core.h>

// Globals from Boot.S
extern uint32 KernelSize;
extern uint32 *PageDirectory;
extern uint32 *PageTables;
extern K_sIDT_t *idt;
extern K_sGDT_t *gdt;

// Globals
K_sKernel_t Kg_sKernel;
volatile uint32 Kg_nLocksHeld = 0;

// Prototypes
void Kernel_ParseParameters( char *pszParameters );
void Kernel_ParseBootModules( K_sMBInfo_t *psMBInfo );
void Kernel_LoadBootModules();
void Kernel_ExecuteBootModules();

void Kernel_Main ( K_sMBInfo_t *psMBInfo ) {

    // Copy values from Boot.S and put in the Kg_sKernel struct
    Kg_sKernel.m_nKernelSize = KernelSize;
    Kg_sKernel.m_nKernelEnd = ( void * ) ( K_MM_KERNELADDRPAGED + ( ( KernelSize + K_MM_KERNELSTACK + 2 ) << K_MM_PAGESIZESHIFT ) );
    Kg_sKernel.m_pnPageDirectory = PageDirectory;
    Kg_sKernel.m_pnPageTables = ( uint32 * ) K_MM_PAGETABLES;
    Kg_sKernel.m_pnPageTablePointers = PageTables;
    Kg_sKernel.m_sIDT = ( K_sIDT_t * ) & idt;
    Kg_sKernel.m_sGDT = ( K_sGDT_t * ) & gdt;

    // Set debugging settings
    Kg_sKernel.m_ShowDebug = false;
    Kg_sKernel.m_ShowVerbose = false;

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
    DeviceManager_Init( );				// Init device manager
    PIC_Init();		  				// Init PIC
    PIT_Init();						// Init PIT
    TimerManager_Init();				// Init timer interface
    ProcessManager_Init();				// Init process manager
    MessageManager_Init();	  	      	    	// Init message manager
    IOManager_Init();					// Volume/FS/IO manager
    FS_Init();                                          // Initialise VFS

    // End of core initialistion, now load boot modules
    DMMFileIO_Init();
    Kernel_LoadBootModules();
    InterruptManager_Start();				// Start interrupts
    //    Kernel_ExecuteBootModules();

    // Main loop, this will eventually sleep until awakened by a shutdown request
    while ( 1 ) {
        asm volatile ( "nop;" );
    }

    // Shutdown
    KPrint( KDEBUG, "KERNEL", "Halted now.\n" );
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
            if ( strcmp( "debug", &pszParameters[ i ] ) == 0 ) {
                Kg_sKernel.m_ShowDebug = true;
            } else if ( strcmp( "verbose", &pszParameters[ i ] ) == 0 ) {
                Kg_sKernel.m_ShowDebug = true;
                Kg_sKernel.m_ShowVerbose = true;
            }
            i = nEnd;
        } while ( bLast == false );
    }
}

void Kernel_ParseBootModules( K_sMBInfo_t *psMBInfo ) {

    // Init kernel variables
    Kg_sKernel.m_nBootModuleCount = psMBInfo->m_nModsCount;
    Kg_sKernel.m_nBootModuleEnd = 0;

    // Too many boot modules?
    if ( Kg_sKernel.m_nBootModuleCount > K_BOOTMODULES_MAX ) {
        KPrint( KSEVERE, "KERNEL", "Too many boot modules - Halting\n" );
        halt();
    }

    // Show how many modules
    KPrint( KVERBOSE, "KERNEL", "[%lu] boot module(s) found\n", Kg_sKernel.m_nBootModuleCount );

    // Now move modules out the way, we will come back to them later and load them in
    uint32 i;
    K_sMBModule_t *psModule = ( K_sMBModule_t * ) psMBInfo->m_nModsAddr;
    for ( i = 0; i < Kg_sKernel.m_nBootModuleCount; i++ ) {

        // Get position etc and save for later
        K_sBootModule_t *psKernelModule = &Kg_sKernel.m_pBootModules[ i ];
        psKernelModule->m_pStart = ( void * ) psModule->m_nStart;
        psKernelModule->m_pEnd = ( void * ) psModule->m_nEnd;
        psKernelModule->m_nLength = psModule->m_nEnd - psModule->m_nStart;

        // Move end of modules in physical memory pointer along
        Kg_sKernel.m_nBootModuleEnd = ( void * ) ( PAGE_ALIGN( psKernelModule->m_pEnd ) + K_MM_PAGESIZE );

        // Debug prompt
        KPrint( KVERBOSE, "KERNEL", "Boot module found at [0x%X-0x%X] (%lu bytes)\n",
                psKernelModule->m_pStart, psKernelModule->m_pEnd, psKernelModule->m_nLength, Kg_sKernel.m_nBootModuleEnd );

        // Next module
        psModule = ( K_sMBModule_t * ) ( ( uint32 ) psModule + ( uint32 ) sizeof( K_sMBModule_t ) );
    }
}

void Kernel_LoadBootModules() {

    // Loop through all modules and map them into the virtual address space
    uint32 i;
    for ( i = 0; i < 1 /*Kg_sKernel.m_nBootModuleCount*/; i++ ) {
        K_sBootModule_t *psKernelModule = &Kg_sKernel.m_pBootModules[ i ];

        // Debug prompt
        uint32 nPageCount = ( psKernelModule->m_nLength + 4095 ) >> K_MM_PAGESIZESHIFT;

        // Construct mount data command
        char szData[ 64 ];
        snprintf( ( char * ) & szData, 64, "0x%X/0x%X", ( uint32 ) psKernelModule->m_pStart, nPageCount );

        // Mount boot modules as DMM volume
        FS_Mount( "DMM:", "DMMBlockIO", "DMMFS", ( char * ) & szData );
        ModuleManager_Load( "DMM:/FILE" );

        KPrint( KVERBOSE, "KERNEL", "Boot module mapped at [0x%X] from [0x%X] (%lu pages)\n", Kg_sKernel.m_pModuleAreaEnd, psKernelModule->m_pStart, nPageCount );
        // Map into module area
        //        uint32 nPageCount = ( psKernelModule->m_nLength + 4095 ) >> K_MM_PAGESIZESHIFT;
        //        MemoryManager_Page_Map( ( uint32 ) psKernelModule->m_pStart, ( uint32 ) Kg_sKernel.m_pModuleAreaEnd, nPageCount, K_MM_FLAGS_KERNEL | K_MM_FLAGS_READWRITE );
        //        psKernelModule->pEntry = ( ModuleEntry * ) Kg_sKernel.m_pModuleAreaEnd;

        // Move module area pointer along
        //        Kg_sKernel.m_pModuleAreaEnd = ( void * ) ( ( uint32 ) Kg_sKernel.m_pModuleAreaEnd + ( nPageCount << K_MM_PAGESIZESHIFT ) );
    }
}

void Kernel_ExecuteBootModules() {

    // Loop through all modules and execute them (now in virtual address space)
    uint32 i;
    for ( i = 0; i < Kg_sKernel.m_nBootModuleCount; i++ ) {
        K_sBootModule_t *psKernelModule = &Kg_sKernel.m_pBootModules[ i ];
        psKernelModule->pEntry();
    }
}

