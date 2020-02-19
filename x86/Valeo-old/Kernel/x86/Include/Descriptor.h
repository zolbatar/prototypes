#ifndef __X86_DESCRIPTOR_H__
#define __X86_DESCRIPTOR_H__

// IDT structure
typedef struct {
    uint16 m_nBaseLow;
    uint16 m_nSelector;
    uint16 m_nFlags;
    uint16 m_nBaseHigh;
}
sIDT_t;

// GDT Structure
typedef struct {
    uint16 m_nLimitLow;
    uint16 m_nBaseLow;
    uint8 m_nBaseMiddle;
    uint8 m_nAttributes;
    uint8 m_nLimitHigh;
    uint8 m_nBaseHigh;
}
sGDT_t;

void Descriptor_SetInterruptGate( uint32 nInterrupt, void *pHandler );
void Descriptor_SetTaskGate( uint32 nInterrupt, void *pHandler );
void Descriptor_SetCallGate( uint32 nInterrupt, void *pHandler );
void Descriptor_SetBase( uint16 nDescriptor, uint32 nBase );
void Descriptor_SetLimit( uint16 nDescriptor, uint32 nLimit );
void Descriptor_SetAccess( uint16 nDescriptor, uint8 nAccess );

#endif // __X86_DESCRIPTOR_H__


