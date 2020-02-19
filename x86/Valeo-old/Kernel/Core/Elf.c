#include <Kernel.h>

// ELF Magic
uchar ELF_MAGIC[ 4 ] = { 0x7F, 0x45, 0x4C, 0x46 };

bool FS_CheckELFHeader( sElfHeader_t *psHeader, char *pszFilename ) {

    // Do some checks on the ELF header
    if ( strncmp( ( char * ) & psHeader->m_szIdent, ( char * ) & ELF_MAGIC, 4 ) != 0 ) {
        KPrint( "FS", "[%s] is not a valid ELF file\n", pszFilename );
        return false;
    }
    if ( psHeader->m_szIdent[ ELF_EI_CLASS ] != ELF_CLASS_32 ) {
        KPrint( "FS", "[%s] is not a valid ELF file : Not 32bit class\n", pszFilename );
        return false;
    }
    if ( psHeader->m_nType != ELF_TYPE_RELATIVE ) {
        KPrint( "FS", "[%s] is not a valid ELF file : Not relative\n", pszFilename );
        return false;
    }
    if ( psHeader->m_nMachine != ELF_MACHINE_386 ) {
        KPrint( "FS", "[%s] is not a valid ELF file : Not for x86\n", pszFilename );
        return false;
    }
    if ( psHeader->m_nVersion != ELF_VERSION_CURRENT ) {
        KPrint( "FS", "[%s] is not a valid ELF file : Not current version\n", pszFilename );
        return false;
    }

    return true;
}

KStatus FS_LoadElf( char *pszFilename, void **pAddress, void **pEntry ) {

    uint32 i, j;

    // Open the file
    uint32 nHandle;
    if ( FS_Open( pszFilename, FS_READONLY, &nHandle ) != NULL ) {
        return FS_ERROROPENINGFILE;
    }

    // Read in header
    sElfHeader_t sHeader;
    uint32 nBytesRead;
    if ( FS_Read( nHandle, &sHeader, sizeof( sElfHeader_t ), &nBytesRead ) ) {
        return FS_ERRORREADINGFROMFILE;
    }

    // Check header
    if ( FS_CheckELFHeader( &sHeader, pszFilename ) == false ) {
        return FS_INVALIDELFFILE;
    }

    // Load in all section headers
    void *psSections = MemoryManager_KAlloc( sHeader.m_nSectionHeaderNumEntries * sHeader.m_nSectionHeaderEntrySize );
    FS_Seek( nHandle, sHeader.m_nSectionHeaderOffset );
    if ( FS_Read( nHandle, psSections, sHeader.m_nSectionHeaderNumEntries * sHeader.m_nSectionHeaderEntrySize, &nBytesRead ) ) {
        MemoryManager_KFree( psSections );
        return FS_ERRORREADINGFROMFILE;
    }

    // Set aside space for string tables etc for each section header
    void *psSectionsData = MemoryManager_KAlloc( sizeof( sElfSectionHeaderData_t ) * sHeader.m_nSectionHeaderNumEntries );

    // First pass, read in string/symbol/relocation tables
    char *pszCodeStringDescs = NULL;
    for ( i = 0; i < sHeader.m_nSectionHeaderNumEntries; i++ ) {

        sElfSectionHeader_t *psSection = ( sElfSectionHeader_t * ) ( psSections + ( i * sHeader.m_nSectionHeaderEntrySize ) );
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
            MemoryManager_Lock();
            psSectionData->m_pData = MemoryManager_KAlloc( psSection->m_nSize );
            if ( psSection->m_nType == ELF_SECTION_TYPE_SYMTAB ) {
                psSectionData->m_pSymbolsAddresses = ( uint32 * ) MemoryManager_KAlloc( sizeof( uint32 ) * ( psSection->m_nSize / sizeof( sElfSymbolTable_t ) ) );
                memset( psSectionData->m_pSymbolsAddresses, 0, sizeof( uint32 ) * ( psSection->m_nSize / sizeof( sElfSymbolTable_t ) ) );
            }
            MemoryManager_Unlock();

            // And load data
            FS_Seek( nHandle, psSection->m_nOffset );
            if ( FS_Read( nHandle, psSectionData->m_pData, psSection->m_nSize, &nBytesRead ) ) {
                goto ErrorReadingFromFile;
            }
            if ( psSection->m_nType == ELF_SECTION_TYPE_STRTAB && pszCodeStringDescs == NULL ) {
                pszCodeStringDescs = ( char * ) psSectionData->m_pData;
            }
            break;
        }
    }

    // Second pass, load binary into RAM
    uint32 pCurrentAddressPtr = ( uint32 ) * pAddress;
    for ( i = 0; i < sHeader.m_nSectionHeaderNumEntries; i++ ) {
        sElfSectionHeader_t *psSection = ( sElfSectionHeader_t * ) ( psSections + ( i * sHeader.m_nSectionHeaderEntrySize ) );
        sElfSectionHeaderData_t *psSectionData = ( sElfSectionHeaderData_t * ) ( psSectionsData + ( i * sizeof( sElfSectionHeaderData_t ) ) );

        // Process section
        switch ( psSection->m_nType ) {
        case ELF_SECTION_TYPE_PROGBITS:

            // Align memory pointer first (if needed)
            if ( psSection->m_nAddrAlign > 1 ) {
                if ( ( pCurrentAddressPtr % psSection->m_nAddrAlign ) > 0 ) {
                    pCurrentAddressPtr &= ~( psSection->m_nAddrAlign - 1 );
                    pCurrentAddressPtr += psSection->m_nAddrAlign;
                }
            }

            // Load into memory
            FS_Seek( nHandle, psSection->m_nOffset );
            if ( FS_Read( nHandle, ( void * ) pCurrentAddressPtr, psSection->m_nSize, &nBytesRead ) ) {
                goto ErrorReadingFromFile;
            }

            // Move memory pointer along and save address for later relocation use
            psSectionData->m_pAddress = ( void * ) pCurrentAddressPtr;
            pCurrentAddressPtr += psSection->m_nSize;
            break;
        case ELF_SECTION_TYPE_NOBITS:

            // Align memory pointer first (if needed)
            if ( psSection->m_nAddrAlign > 1 ) {
                if ( ( pCurrentAddressPtr % psSection->m_nAddrAlign ) > 0 ) {
                    pCurrentAddressPtr &= ~( psSection->m_nAddrAlign - 1 );
                    pCurrentAddressPtr += psSection->m_nAddrAlign;
                }
            }

            // Zero memory
            memset( ( void * ) pCurrentAddressPtr, 0, psSection->m_nSize );

            // Move memory pointer along and save address for later relocation use
            psSectionData->m_pAddress = ( void * ) pCurrentAddressPtr;
            pCurrentAddressPtr += psSection->m_nSize;
            break;
        }
    }

    // Align to 16 bytes
    if ( ( pCurrentAddressPtr % 16 ) > 0 ) {
        pCurrentAddressPtr &= ~( 15 );
        pCurrentAddressPtr += 16;
    }

    // Set GOT to this address
    uint32 pGot = pCurrentAddressPtr;
    uint32 pGotIndex = 0;
    uint32 *pGotCurrent = ( uint32 * ) pGot;

    // Third pass, handle relocations
    for ( i = 0; i < sHeader.m_nSectionHeaderNumEntries; i++ ) {
        sElfSectionHeader_t *psSection = ( sElfSectionHeader_t * ) ( psSections + ( i * sHeader.m_nSectionHeaderEntrySize ) );
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
                    *pRelAddress += ( uint32 ) psLinkSectionData->m_pAddress + psSymbol->m_nValue;
                    //		    KPrint("FS", "32: 0x%X = 0x%X (0x%X)\n", pRelAddress, *pRelAddress, psSymbol->m_nValue);
                    break;
                case ELF_RTYPE_PC32:
                    *pRelAddress += ( ( uint32 ) psLinkSectionData->m_pAddress + psSymbol->m_nValue ) - ( uint32 ) pRelAddress;
                    //		    KPrint("FS", "PC32: 0x%X = 0x%X\n", pRelAddress, *pRelAddress);
                    break;
                case ELF_RTYPE_GOT32:
                    if ( psSymbolSectionData->m_pSymbolsAddresses[ nRelSym ] == 0 ) {
                        psSymbolSectionData->m_pSymbolsAddresses[ nRelSym ] = pCurrentAddressPtr;
                        pCurrentAddressPtr += psSymbol->m_nSize;

                        // Align to 4 bytes
                        if ( ( pCurrentAddressPtr % 4 ) > 0 ) {
                            pCurrentAddressPtr &= ~( 3 );
                            pCurrentAddressPtr += 4;
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
                    *pRelAddress += ( ( ( uint32 ) * pAddress + psSymbol->m_nValue ) - ( uint32 ) pRelAddress );
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

    // Close the file
    if ( FS_Close( nHandle ) != NULL ) {
        return FS_ERRORCLOSINGFILE;
    }


    // Move along after GOT
    pCurrentAddressPtr = ( uint32 ) pGotCurrent;

    // Align to 4096 bytes
    if ( ( pCurrentAddressPtr % 4096 ) > 0 ) {
        pCurrentAddressPtr &= ~( 4095 );
        pCurrentAddressPtr += 4096;
    }

    // Return entry point
    *pEntry = sHeader.m_nEntry + *pAddress;

    // Return new pointer address
    *pAddress = ( void * ) pCurrentAddressPtr;

    // Free memory used
    for ( i = 0; i < sHeader.m_nSectionHeaderNumEntries; i++ ) {
        sElfSectionHeaderData_t *psSectionData = ( sElfSectionHeaderData_t * ) ( psSectionsData + ( i * sizeof( sElfSectionHeaderData_t ) ) );

        if ( psSectionData->m_pData != NULL )
            MemoryManager_KFree( psSectionData->m_pData );
        if ( psSectionData->m_pSymbolsAddresses != NULL )
            MemoryManager_KFree( psSectionData->m_pSymbolsAddresses );
    }
    MemoryManager_KFree( psSectionsData );
    MemoryManager_KFree( psSections );

    return NULL;
ErrorReadingFromFile:

    // Free memory used
    for ( i = 0; i < sHeader.m_nSectionHeaderNumEntries; i++ ) {
        sElfSectionHeaderData_t *psSectionData = ( sElfSectionHeaderData_t * ) ( psSectionsData + ( i * sizeof( sElfSectionHeaderData_t ) ) );

        if ( psSectionData->m_pData != NULL )
            MemoryManager_KFree( psSectionData->m_pData );
        if ( psSectionData->m_pSymbolsAddresses != NULL )
            MemoryManager_KFree( psSectionData->m_pSymbolsAddresses );
    }
    MemoryManager_KFree( psSectionsData );
    MemoryManager_KFree( psSections );

    return FS_ERRORREADINGFROMFILE;
}
