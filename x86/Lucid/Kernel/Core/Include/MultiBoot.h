#ifndef __K_MULTIBOOT_H__
#define __K_MULTIBOOT_H__

#include <Types.h>

typedef struct {
    uint32 m_nMagic;
    uint32 m_nFlags;
    uint32 m_nChecksum;
    uint32 m_nHeaderAddr;
    uint32 m_nLoadAddr;
    uint32 m_nLoadEndAddr;
    uint32 m_nBSSEndAddr;
    uint32 m_nEntryAddr;
}
K_sMBHeader_t;

// The symbol table for a.out
typedef struct {
    uint32 m_nTabSize;
    uint32 m_nStrSize;
    uint32 m_nAddr;
    uint32 m_nReserved;
}
K_sMBAOUTHeader_t;

// The section header table for ELF
typedef struct {
    uint32 m_nNum;
    uint32 m_nSize;
    uint32 m_nAddr;
    uint32 m_nShndx;
}
K_sMBELFHeader_t;

// The Multiboot information
typedef struct {
    uint32 m_nFlags;
    uint32 m_nMemLower;
    uint32 m_nMemUpper;
    uint32 m_nBootDevice;
    uint32 m_nCmdLine;
    uint32 m_nModsCount;
    uint32 m_nModsAddr;
    union
    {
        K_sMBAOUTHeader_t m_nAoutSym;
        K_sMBELFHeader_t m_nElfSec;
    } u;
    uint32 m_nMMAPLength;
    uint32 m_nMMAPAddr;
}
K_sMBInfo_t;

// The module structure
typedef struct {
    uint32 m_nStart;
    uint32 m_nEnd;
    uint32 m_nString;
    uint32 m_nReserved;
}
K_sMBModule_t;

// The memory map
typedef struct {
    uint32 m_nSize;
    uint32 m_nBaseAddrLow;
    uint32 m_nBaseAddrHigh;
    uint32 m_nLengthLow;
    uint32 m_nLengthHigh;
    uint32 m_nType;
}
K_sMBMemoryMap_t;

#endif // __K_MULTIBOOT_H__

