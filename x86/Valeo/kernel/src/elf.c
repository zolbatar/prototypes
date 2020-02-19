#include <Kernel.h>

// ELF Magic
uchar ELF_MAGIC[ 4 ] = { 0x7F, 0x45, 0x4C, 0x46 };

bool CheckELFHeader( sElfHeader_t *psHeader ) {

    // Do some checks on the ELF header
    if ( strncmp( ( char * ) & psHeader->m_szIdent, ( char * ) & ELF_MAGIC, 4 ) != 0 ) {
#ifdef DEBUG
        Syslog_Lock();
        Syslog_Entry( "MODULE", "Not a valid ELF file\n" );
        Syslog_Unlock();
#endif

        return false;
    }
    if ( psHeader->m_szIdent[ ELF_EI_CLASS ] != ELF_CLASS_32 ) {
#ifdef DEBUG
        Syslog_Lock();
        Syslog_Entry( "MODULE", "Not a valid ELF file : Not 32bit class\n" );
        Syslog_Unlock();
#endif

        return false;
    }
    if ( psHeader->m_nType != ELF_TYPE_RELATIVE ) {
#ifdef DEBUG
        Syslog_Lock();
        Syslog_Entry( "MODULE", "Not a valid ELF file : Not relative\n" );
        Syslog_Unlock();
#endif

        return false;
    }
    if ( psHeader->m_nMachine != ELF_MACHINE_386 ) {
#ifdef DEBUG
        Syslog_Lock();
        Syslog_Entry( "MODULE", "Not a valid ELF file : Not for x86\n" );
        Syslog_Unlock();
#endif

        return false;
    }
    if ( psHeader->m_nVersion != ELF_VERSION_CURRENT ) {
#ifdef DEBUG
        Syslog_Lock();
        Syslog_Entry( "MODULE", "Not a valid ELF file : Not current version\n" );
        Syslog_Unlock();
#endif

        return false;
    }

    return true;
}

bool LoadELFBootModule( sBootModule_t *psBootModule, uint32 nModuleIndex, void **pEntry ) {

    uint32 i, j;

    // First task is to map the module from >1MB area into scratch space so we can use it
    uint32 nPageCount = ( psBootModule->m_nLength + ( MM_PAGESIZE - 1 ) ) >> MM_PAGESIZESHIFT;
    MM_Page_Map( ( uint32 ) psBootModule->m_pStart, ( uint32 ) g_sKernel.m_pPhysicalMemMapArea, nPageCount, MM_FLAGS_KERNEL | MM_FLAGS_READWRITE );

    // Set file (mem) pos to 0
    void *pMemPos = g_sKernel.m_pPhysicalMemMapArea;
    uint32 nPos = 0;

    // Check header
    sElfHeader_t sHeader;
    memcpy( &sHeader, pMemPos + nPos, sizeof( sElfHeader_t ) );
    nPos += sizeof( sElfHeader_t );
    if ( CheckELFHeader( &sHeader ) == false ) {
        Syslog_Lock();
        Syslog_Entry( "MODULE", "Module %lu has invalid ELF Header\n", nModuleIndex );
        Syslog_Unlock();
        return false;

    }

    // Load in all section headers
    MM_Lock();
    void *psSections = MM_KAlloc( sHeader.m_nSectionHeaderNumEntries * sHeader.m_nSectionHeaderEntrySize );
    MM_Unlock();
    nPos = sHeader.m_nSectionHeaderOffset;
    memcpy( psSections, pMemPos + nPos, sHeader.m_nSectionHeaderNumEntries * sHeader.m_nSectionHeaderEntrySize );

    // Set aside space for string tables etc for each section header
    void *psSectionsData = MM_KAlloc( sizeof( sElfSectionHeaderData_t ) * sHeader.m_nSectionHeaderNumEntries );

    // First pass, read in string/symbol/relocation tables
    char *pszCodeStringDescs = NULL;
    for ( i = 0; i < sHeader.m_nSectionHeaderNumEntries; i++ ) {


        sElfSectionHeader_t *psSection = ( sElfSectionHeader_t * )
                                         ( psSections + ( i * sHeader.m_nSectionHeaderEntrySize ) );
        sElfSectionHeaderData_t *psSectionData = ( sElfSectionHeaderData_t * ) ( psSectionsData + ( i * sizeof( sElfSectionHeaderData_t ) ) );
        psSectionData->m_pData = NULL;
        psSectionData->m_pSymbolsAddresses = NULL;
        psSectionData->m_pAddress = 0;

        // Process section
        switch ( psSection->m_nType ) {
        case ELF_SECTION_TYPE_STRTAB:
        case ELF_SECTION_TYPE_SYMTAB:
        case ELF_SECTION_TYPE_REL:

            // Allocate space
            MM_Lock();
            psSectionData->m_pData = MM_KAlloc( psSection->m_nSize );
            if ( psSection->m_nType == ELF_SECTION_TYPE_SYMTAB ) {
                psSectionData->m_pSymbolsAddresses = ( uint32 * ) MM_KAlloc( sizeof( uint32 ) * ( psSection->m_nSize / sizeof( sElfSymbolTable_t ) ) );
                memset( psSectionData->m_pSymbolsAddresses, 0, sizeof( uint32 ) * ( psSection->m_nSize / sizeof( sElfSymbolTable_t ) ) );
            }
            MM_Unlock();

            // And load data
            nPos = psSection->m_nOffset;
            memcpy( psSectionData->m_pData, pMemPos + nPos, psSection->m_nSize );
            if ( psSection->m_nType == ELF_SECTION_TYPE_STRTAB && pszCodeStringDescs == NULL ) {
                pszCodeStringDescs = ( char * ) psSectionData->m_pData;
            }
            break;
        }
    }

    // Second pass, load binary into RAM
    void *pCurrentAddressPtr = g_sKernel.m_pModuleArea;
    for ( i = 0; i < sHeader.m_nSectionHeaderNumEntries; i++ ) {
        sElfSectionHeader_t *psSection = ( sElfSectionHeader_t * )
                                         ( psSections + ( i * sHeader.m_nSectionHeaderEntrySize ) );
        sElfSectionHeaderData_t *psSectionData = ( sElfSectionHeaderData_t * ) ( psSectionsData + ( i * sizeof( sElfSectionHeaderData_t ) ) );

        // Process section
        switch ( psSection->m_nType ) {
        case ELF_SECTION_TYPE_PROGBITS:

            // Align memory pointer first (if needed)
            if ( psSection->m_nAddrAlign > 1 ) {
                if ( ( ( uint32 ) pCurrentAddressPtr % psSection->m_nAddrAlign ) > 0 ) {
                    ( uint32 ) pCurrentAddressPtr &= ~( psSection->m_nAddrAlign - 1 );
                    ( uint32 ) pCurrentAddressPtr += psSection->m_nAddrAlign;
                }
            }

            // Load into memory
            nPos = psSection->m_nOffset;
            memcpy( pCurrentAddressPtr, pMemPos + nPos, psSection->m_nSize );

            // Move memory pointer along and save address for later relocation use
            psSectionData->m_pAddress = ( void * ) pCurrentAddressPtr;
            pCurrentAddressPtr += psSection->m_nSize;
            break;
        case ELF_SECTION_TYPE_NOBITS:

            // Align memory pointer first (if needed)
            if ( psSection->m_nAddrAlign > 1 ) {
                if ( ( ( uint32 ) pCurrentAddressPtr % psSection->m_nAddrAlign ) > 0 ) {
                    pCurrentAddressPtr = ( void * ) ( ( uint32 ) pCurrentAddressPtr & ~( psSection->m_nAddrAlign - 1 ) );
                    pCurrentAddressPtr = ( void * ) ( ( uint32 ) pCurrentAddressPtr + psSection->m_nAddrAlign );
                }
            }

            // Zero memory
            memset( pCurrentAddressPtr, 0, psSection->m_nSize );

            // Move memory pointer along and save address for later relocation use
            psSectionData->m_pAddress = pCurrentAddressPtr;
            pCurrentAddressPtr += psSection->m_nSize;
            break;
        }
    }
    // Align to 16 bytes
    if ( ( ( uint32 ) pCurrentAddressPtr % 16 ) > 0 ) {
        pCurrentAddressPtr = ( void * ) ( ( uint32 ) pCurrentAddressPtr & ~( 15 ) );
        pCurrentAddressPtr = ( void * ) ( ( uint32 ) pCurrentAddressPtr + 16 );
    }

    // Set GOT to this address
    uint32 pGot = ( uint32 ) pCurrentAddressPtr;
    uint32 pGotIndex = 0;
    uint32 *pGotCurrent = ( uint32 * ) pGot;

    // Third pass, handle relocations
    for ( i = 0; i < sHeader.m_nSectionHeaderNumEntries; i++ ) {
        sElfSectionHeader_t *psSection = ( sElfSectionHeader_t * )
                                         ( psSections + ( i * sHeader.m_nSectionHeaderEntrySize ) );
        sElfSectionHeaderData_t *psSectionData = ( sElfSectionHeaderData_t * ) ( psSectionsData + ( i * sizeof( sElfSectionHeaderData_t ) ) );

        // Process section
        switch ( psSection->m_nType ) {

        case ELF_SECTION_TYPE_REL:

            // Process relocations
            for ( j = 0; j < psSection->m_nSize / sizeof( sElfRelocation_t ); j++ ) {

                // Get relocation entry
                sElfRelocation_t *psRelocate = ( sElfRelocation_t * ) ( psSectionData->m_pData + ( j * sizeof( sElfRelocation_t ) ) );
                uint32 nRelSym = ELF_R_SYM( psRelocate->m_nInfo );
                uint32 nRelType = ELF_R_TYPE( psRelocate->m_nInfo );

                // Get symbol table
                sElfSectionHeaderData_t *psSymbolSectionData = ( sElfSectionHeaderData_t * ) ( psSectionsData + ( psSection->m_nLink * sizeof( sElfSectionHeaderData_t ) ) );
                sElfSymbolTable_t *psSymbol = ( sElfSymbolTable_t * ) ( psSymbolSectionData->m_pData + ( nRelSym * sizeof( sElfSymbolTable_t ) ) );

                // Get offset in memory of entry
                sElfSectionHeaderData_t *psTextSectionData = ( sElfSectionHeaderData_t * ) ( psSectionsData + ( psSection->m_nInfo * sizeof( sElfSectionHeaderData_t ) ) );
                uint32 *pRelAddress = psTextSectionData->m_pAddress + psRelocate->m_nAddrOffset;

                // Get link to section
                sElfSectionHeaderData_t *psLinkSectionData = ( sElfSectionHeaderData_t * ) ( psSectionsData + ( psSymbol->m_nSectionHeaderIndex * sizeof( sElfSectionHeaderData_t ) ) );

                switch ( nRelType ) {
                case ELF_RTYPE_32:
                    //                     Syslog_Entry("MODULE", "32 0x%X 0x%X 0x%X 0x%X\n", *pRelAddress, psLinkSectionData->m_pAddress, psSymbol->m_nValue, pRelAddress);
                    *pRelAddress += ( uint32 ) psLinkSectionData->m_pAddress + psSymbol->m_nValue;
                    break;
                case ELF_RTYPE_PC32:
                    //                     Syslog_Entry("MODULE", "PC32 0x%X 0x%X 0x%X 0x%X\n", *pRelAddress, psLinkSectionData->m_pAddress, psSymbol->m_nValue, pRelAddress);
                    *pRelAddress += ( uint32 ) ( psSymbol->m_nValue - ( ( uint32 ) pRelAddress - ( uint32 ) psLinkSectionData->m_pAddress ) );
                    break;
                case ELF_RTYPE_GOT32:
                    if ( psSymbolSectionData->m_pSymbolsAddresses[ nRelSym ] == 0 ) {
                        psSymbolSectionData->m_pSymbolsAddresses[ nRelSym ] = ( uint32 ) pCurrentAddressPtr;
                        pCurrentAddressPtr += psSymbol->m_nSize;

                        // Align to 4 bytes
                        if ( ( ( uint32 ) pCurrentAddressPtr % 4 ) > 0 ) {
                            pCurrentAddressPtr = ( void* ) ( ( uint32 ) pCurrentAddressPtr & ~( 3 ) );
                            pCurrentAddressPtr = ( void* ) ( ( uint32 ) pCurrentAddressPtr + 4 );
                        }
                    }

                    // Get base address of linked .text header and set GOT entry
                    *pGotCurrent = ( uint32 ) psLinkSectionData->m_pAddress + psSymbol->m_nValue;

                    // Point this instruction to the got entry
                    *pRelAddress = pGotIndex;

                    // Move GOT pointer along
                    pGotIndex += 4;
                    pGotCurrent++;

                    break;
                case ELF_RTYPE_PLT32:
                    *pRelAddress += ( ( ( uint32 ) g_sKernel.m_pModuleArea + psSymbol->m_nValue ) - ( uint32 ) pRelAddress );
                    break;
                case ELF_RTYPE_GOTOFF:
                    *pRelAddress = ( uint32 ) psLinkSectionData->m_pAddress;
                    break;
                case ELF_RTYPE_GOTPC:
                    *pRelAddress += pGot - ( uint32 ) pRelAddress;
                    break;
                default:
                    break;
                }
            }
            break;
        }
    }

    // Move along after GOT
    pCurrentAddressPtr = pGotCurrent;

    // Align to 4096 bytes
    if ( ( ( uint32 ) pCurrentAddressPtr % 4096 ) > 0 ) {
        pCurrentAddressPtr = ( void * ) ( ( uint32 ) pCurrentAddressPtr & ( ~4095 ) );
        pCurrentAddressPtr = ( void * ) ( ( uint32 ) pCurrentAddressPtr + 4096 );
    }

    // Return entry address
    *pEntry = sHeader.m_nEntry + g_sKernel.m_pModuleArea;

    // Set new pointer address
    psBootModule->m_pLoadedAddress = g_sKernel.m_pModuleArea;
    psBootModule->m_pLoadedAddressEnd = ( void * ) ( ( uint32 ) pCurrentAddressPtr );
    psBootModule->m_nLoadedAddressPages = ( ( uint32 ) psBootModule->m_pLoadedAddressEnd - ( uint32 ) psBootModule->m_pLoadedAddress ) >> MM_PAGESIZESHIFT;
    g_sKernel.m_pModuleArea = ( void * ) pCurrentAddressPtr;

    // Unmap from physical memory
    MM_Page_Unmap( ( uint32 ) g_sKernel.m_pPhysicalMemMapArea, nPageCount );

    // Free memory used
    for ( i = 0; i < sHeader.m_nSectionHeaderNumEntries; i++ ) {
        sElfSectionHeaderData_t *psSectionData = ( sElfSectionHeaderData_t * )
                ( psSectionsData + ( i * sizeof( sElfSectionHeaderData_t ) ) );

        if ( psSectionData->m_pData != NULL )
            MM_KFree( psSectionData->m_pData );
        if ( psSectionData->m_pSymbolsAddresses != NULL )
            MM_KFree( psSectionData->m_pSymbolsAddresses );
    }
    MM_KFree( psSectionsData );
    MM_KFree( psSections );

    return true;
}
