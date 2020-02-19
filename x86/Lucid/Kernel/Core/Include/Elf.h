#ifndef __K_ELF_H__
#define __K_ELF_H__

#include <Types.h>

#define K_ELF_NIDENT 16
#define K_ELF_TYPE_RELATIVE 1

typedef struct {
    uchar m_szIdent[ K_ELF_NIDENT ];
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
K_sElfHeader_t;

#endif // __K_ELF_H__
