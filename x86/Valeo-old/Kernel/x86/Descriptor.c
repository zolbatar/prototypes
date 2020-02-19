#include <Kernel.h>

void Descriptor_SetInterruptGate( uint32 nInterrupt, void *pHandler ) {
    g_sKernel.m_sIDT[ nInterrupt ].m_nSelector = 0x08;
    g_sKernel.m_sIDT[ nInterrupt ].m_nBaseLow = ( ( uint32 ) pHandler ) & 0xFFFF;
    g_sKernel.m_sIDT[ nInterrupt ].m_nBaseHigh = ( ( uint32 ) pHandler ) >> 16;
    g_sKernel.m_sIDT[ nInterrupt ].m_nFlags = 0x8E00;
}

void Descriptor_SetTaskGate( uint32 nInterrupt, void *pHandler ) {
    g_sKernel.m_sIDT[ nInterrupt ].m_nSelector = 0x08;
    g_sKernel.m_sIDT[ nInterrupt ].m_nBaseLow = ( ( uint32 ) pHandler ) & 0xFFFF;
    g_sKernel.m_sIDT[ nInterrupt ].m_nBaseHigh = ( ( uint32 ) pHandler ) >> 16;
    g_sKernel.m_sIDT[ nInterrupt ].m_nFlags = 0x8500;
}

void Descriptor_SetCallGate( uint32 nInterrupt, void *pHandler ) {
    g_sKernel.m_sIDT[ nInterrupt ].m_nSelector = 0x08;
    g_sKernel.m_sIDT[ nInterrupt ].m_nBaseLow = ( ( uint32 ) pHandler ) & 0xFFFF;
    g_sKernel.m_sIDT[ nInterrupt ].m_nBaseHigh = ( ( uint32 ) pHandler ) >> 16;
    g_sKernel.m_sIDT[ nInterrupt ].m_nFlags = 0x8C00;
}

void Descriptor_SetBase( uint16 nDescriptor, uint32 nBase ) {
    nDescriptor >>= 3;
    g_sKernel.m_sGDT[ nDescriptor ].m_nBaseLow = nBase & 0xffff;
    g_sKernel.m_sGDT[ nDescriptor ].m_nBaseMiddle = ( nBase >> 16 ) & 0xff;
    g_sKernel.m_sGDT[ nDescriptor ].m_nBaseHigh = ( nBase >> 24 ) & 0xff;
}

void Descriptor_SetLimit( uint16 nDescriptor, uint32 nLimit ) {
    nDescriptor >>= 3;
    g_sKernel.m_sGDT[ nDescriptor ].m_nLimitHigh = 0x40;

    // See if we need 4K granularity
    if ( nLimit > 0x000fffff ) {
        g_sKernel.m_sGDT[ nDescriptor ].m_nLimitHigh |= 0x80;	// 4K granularity
        nLimit >>= 12;
    }

    g_sKernel.m_sGDT[ nDescriptor ].m_nLimitLow = nLimit & 0xffff;
    g_sKernel.m_sGDT[ nDescriptor ].m_nLimitHigh |= ( nLimit >> 16 ) & 0x0f;
}

void Descriptor_SetAccess( uint16 nDescriptor, uint8 nAccess ) {
    nDescriptor >>= 3;
    g_sKernel.m_sGDT[ nDescriptor ].m_nAttributes = nAccess;
}

