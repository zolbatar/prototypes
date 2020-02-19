#ifndef __ELF_H__
#define __ELF_H__

#include <Kernel.h>

#define ELF_NIDENT 16
#define ELF_EI_CLASS 4
#define ELF_CLASS_32 1
#define ELF_TYPE_RELATIVE 1
#define ELF_MACHINE_386 3
#define ELF_VERSION_CURRENT 1
#define ELF_SECTION_TYPE_NULL 0
#define ELF_SECTION_TYPE_PROGBITS 1
#define ELF_SECTION_TYPE_SYMTAB 2
#define ELF_SECTION_TYPE_STRTAB 3
#define ELF_SECTION_TYPE_RELA 4
#define ELF_SECTION_TYPE_NOBITS 8
#define ELF_SECTION_TYPE_REL 9

#define ELF_R_SYM(i) ((i)>>8)
#define ELF_R_TYPE(i) ((uchar)(i))

#define ELF_RTYPE_32 1
#define ELF_RTYPE_PC32 2
#define ELF_RTYPE_GOT32 3
#define ELF_RTYPE_PLT32 4
#define ELF_RTYPE_GOTOFF 9
#define ELF_RTYPE_GOTPC 10

typedef struct {
    uchar m_szIdent[ ELF_NIDENT ];
    uint16 m_nType;
    uint16 m_nMachine;
    uint32 m_nVersion;
    uint32 m_nEntry;
    uint32 m_nProgramHeaderOffset;
    uint32 m_nSectionHeaderOffset;
    uint32 m_nFlags;
    uint16 m_nElfHeaderSize;
    uint16 m_nProgramHeaderEntrySize;
    uint16 m_nProgramHeaderNumEntries;
    uint16 m_nSectionHeaderEntrySize;
    uint16 m_nSectionHeaderNumEntries;
    uint16 m_nSectionHeaderStringIndex;
}
sElfHeader_t;

typedef struct {
    uint32 m_nName;
    uint32 m_nType;
    uint32 m_nFlags;
    uint32 m_nAddress;
    uint32 m_nOffset;
    uint32 m_nSize;
    uint32 m_nLink;
    uint32 m_nInfo;
    uint32 m_nAddrAlign;
    uint32 m_EntrySize;
}
sElfSectionHeader_t;

typedef struct {
    uint32 m_nName;
    uint32 m_nValue;
    uint32 m_nSize;
    uchar m_nInfo;
    uchar m_nOther;
    uint16 m_nSectionHeaderIndex;
}
sElfSymbolTable_t;

typedef struct {
    uint32 m_nAddrOffset;
    uint32 m_nInfo;
}
sElfRelocation_t;

typedef struct {
    uint32 *m_pSymbolsAddresses;
    void *m_pData;
    uint32 m_nCount;
    void *m_pAddress;
}
sElfSectionHeaderData_t;

bool LoadELFBootModule( sBootModule_t *psBootModule, uint32 nModuleIndex, void **pEntry );

#endif // __ELF_H__
