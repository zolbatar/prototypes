#include <All.h>

#define K_FDC_STANDARDCONTROLLER 0x1
#define K_FDC_ENHANCEDCONTROLLER 0x2

#define K_FDC_DOR	       0x3F2 // Digital output register
#define K_FDC_MSR	       0x3F4 // Main status register (input)
#define K_FDC_DSR	       0x3F4 // Data select register (output)
#define K_FDC_PORTDATA 	       0x3F5 // Data port
#define K_FDC_DIR  	       0x3F7 // Digital Input Register (input)

#define K_FDC_CMD_SPECIFY      0x03  // Specify drive timings
#define K_FDC_CMD_VERSION      0x10  // FDC Version
#define K_FDC_CMD_RECAL        0x07  // Recalibrate
#define K_FDC_CMD_SENSEI       0x08  // Sense interrupt status
#define K_FDC_CMD_SEEK         0x0F  // Seek track

int Kg_bEnhancedController;
int Kg_bFloppyInterrupt;
static uchar cStatus[ 7 ] = { 0 };
static uint32 nStatusPos = 0;
static uchar nSr0 = 0;
uint32 nCylinder = 0;
static uint32 nTimeOut = 0;
static uint32 nMotorTick = 0;
bool bMotorOn = false;
char *pcDMABuffer;

// Prototypes
bool Floppy_Interrupt();
bool Floppy_TimerInterrupt();
bool FloppyController_Handler( K_sKBlockIOController_t *psController );
void FloppyController_Reset();
bool Floppy_Handler( K_sKBlockIODevice_t *psDevice );
void Floppy_Reset( uint32 nDrive );
bool Floppy_Seek( uint32 nDrive, uint32 nGetCylinder );
void Floppy_Recalibrate( uint32 nDrive );
bool Floppy_WaitFDC( bool nSenseInterrupt );
void Floppy_MotorOn( uint32 nDrive );
void Floppy_MotorOff();
uchar Floppy_GetByte();
void Floppy_SendByte( uchar nByte );

void Floppy_Init() {

    // Figure out if we have a standard or enhanced controller
    Floppy_SendByte( K_FDC_CMD_VERSION );
    uchar cType = Floppy_GetByte();
    if ( cType == 0x80 ) {
        Kg_bEnhancedController = K_FDC_STANDARDCONTROLLER;
        Console_Print( K_CIO_DEBUG, "FLOPPY", "NEC765 Controller found\n" );
    } else {
        Kg_bEnhancedController = K_FDC_ENHANCEDCONTROLLER;
        Console_Print( K_CIO_DEBUG, "FLOPPY", "Enhanced controller found\n" );
    }

    // Set DMA Buffer area
    pcDMABuffer = ( char * ) 0;
    Console_Print( K_CIO_DEBUG, "FLOPPY", "512 Byte DMA buffer at 0x%x\n", pcDMABuffer );

    // Create controller struct
    K_sKBlockIOController_t *psController = ( K_sKBlockIOController_t * ) MemoryManager_KAlloc( sizeof( K_sKBlockIOController_t ) );
    psController->m_nType = K_BLOCKIO_TYPE_FLOPPY;
    psController->m_pHandler = FloppyController_Handler;
    snprintf( psController->m_szName, 32, ":FDC:" );
    snprintf( psController->m_szDescription, 32, "Floppy drive controller" );

    // Now attach the device to the block IO interface
    BlockIO_AttachController( psController );

    // Read number and types of floppy drives from cmos
    uchar nFloppyies = CMOS_Read( 0x10 );
    uchar nFloppy[ 2 ];
    nFloppy[ 0 ] = ( nFloppyies & 0xF0 ) >> 4;
    nFloppy[ 1 ] = nFloppyies & 0xF;

    // Analyse both floppy drives
    K_sKBlockIODevice_t *psFloppy;
    int i;
    for ( i = 0;i < 2;i++ ) {
        if ( nFloppy[ i ] != 0x0 ) {
            psFloppy = ( K_sKBlockIODevice_t * ) MemoryManager_KAlloc( sizeof( K_sKBlockIODevice_t ) );
            psFloppy->m_pHandler = Floppy_Handler;
            psFloppy->m_psController = psController;
            psFloppy->m_nType = K_BLOCKIO_TYPE_FLOPPY;
            psFloppy->m_nDrive = i;
            psFloppy->m_nVolume = 0;
            psFloppy->m_nLBA = 0;
            psFloppy->m_nSectorSize = 512;
            psFloppy->m_bRemoveable = true;
            snprintf( psFloppy->m_szName, 32, ":FD%d:", i );
            snprintf( psFloppy->m_szDescription, 32, "Floppy Drive %d", i );

            // Set sectors/track/etc according to dimensions
            switch ( nFloppy[ i ] ) {
            case 1:                                                                              // 5.25 360K
                psFloppy->m_nTotalHeads = 2;
                psFloppy->m_nTotalCylinders = 40;
                psFloppy->m_nSectorsPerCylinder = 9;
                Console_Print( K_CIO_SEVERE, "FLOPPY", "FATAL: Floppy :FD%d: is 5.25\" 360Kb (not supported) - Halting\n" );
                halt();

            case 2:                                                                              // 5.25 1.2Mb
                psFloppy->m_nTotalHeads = 2;
                psFloppy->m_nTotalCylinders = 80;
                psFloppy->m_nSectorsPerCylinder = 15;
                Console_Print( K_CIO_SEVERE, "FLOPPY", "FATAL: Floppy :FD%d: is 5.25\" 1.2Mb is unsupported - Halting\n" );
                halt();

            case 3:                                                                              // 3.5 720K
                psFloppy->m_nTotalHeads = 2;
                psFloppy->m_nTotalCylinders = 80;
                psFloppy->m_nSectorsPerCylinder = 9;
                Console_Print( K_CIO_SEVERE, "FLOPPY", "FATAL: Floppy :FD%d: is 3.5\" 720Kb is unsupported - Halting\n" );
                halt();

            case 4:                                                                              // 3.5 1.44Mb
                psFloppy->m_nTotalHeads = 2;
                psFloppy->m_nTotalCylinders = 80;
                psFloppy->m_nSectorsPerCylinder = 18;
#ifdef DEBUG

                Console_Print( K_CIO_DEBUG, "FLOPPY", "Floppy :FD%d: is 3.5\" 1.44Mb\n", i );
#endif

                break;

            case 5:                                                                              // 3.5 2.88Mb
                psFloppy->m_nTotalHeads = 2;
                psFloppy->m_nTotalCylinders = 80;
                psFloppy->m_nSectorsPerCylinder = 36;
                Console_Print( K_CIO_SEVERE, "FLOPPY", "FATAL: Floppy :FD%d: is 3.5\" 2.88Mb is unsupported - Halting\n" );
                halt();
            }

            // Now attach the device to the block IO interface
            BlockIO_AttachDevice( psFloppy );

        }
    }

    // Attach fdc to IRQ 0x6
    Interrupt_AttachHandler( 0x6, Floppy_Interrupt );

    // Enable IRQ 6
    PIC_EnableIRQ( 0x6 );

    // Attach our floppy driver to the PIT to time events
    Interrupt_AttachHandler( 0x0, Floppy_TimerInterrupt );

    // Clear floppy interrupt flag
    Kg_bFloppyInterrupt = false;

}

bool Floppy_Interrupt() {

    // Set floppy interrupt flag
    Kg_bFloppyInterrupt = true;

    // Return that we have handled it
    return true;
}

bool Floppy_TimerInterrupt() {

    // Decrement timeout
    if ( nTimeOut )
        --nTimeOut;

    // Decrement motor tick
    if ( nMotorTick > 0 )
        --nMotorTick;

    else if ( !nMotorTick && bMotorOn ) {

        // Turn off floppy motor
        outb( 0x0C, K_FDC_DOR );

        bMotorOn = false;
    }

    // Return that we haven't handled it so the interrupt handler can go onto the next timer
    return false;
}

bool FloppyController_Handler( K_sKBlockIOController_t *psController ) {

    switch ( psController->m_nCommand ) {
    case K_BLOCKIO_CMD_NONE:
        return true;

    case K_BLOCKIO_CONTROLLERCMD_RESET:
        FloppyController_Reset();
        return true;

    }

    // Return with error
    return false;
}

void FloppyController_Reset() {
    // Stop the motors and disable IRQ/DMA
    outb( 0x0, K_FDC_DOR );

    // Program data rate to 500K/s
    outb( 0x0, K_FDC_DSR );

    // Re-enable interrupts
    outb( 0x0C, K_FDC_DOR );

    // Interrupt will be triggered by reset, so clear flah
    Kg_bFloppyInterrupt = false;

    // Specify drive timings
    Floppy_SendByte( K_FDC_CMD_SPECIFY );
    Floppy_SendByte( 0xDF );                  // SRT = 3ms, HUT = 240ms
    Floppy_SendByte( 0x02 );                  // HLT = 16ms, ND = 0
}

bool Floppy_Handler( K_sKBlockIODevice_t *psDevice ) {

    switch ( psDevice->m_nCommand ) {
    case K_BLOCKIO_CMD_NONE:
        return true;

    case K_BLOCKIO_DEVICECMD_RESET:
        Floppy_Reset( psDevice->m_nDrive );
        return true;

    case K_BLOCKIO_DEVICECMD_SEEK:
        return Floppy_Seek( psDevice->m_nDrive, psDevice->m_nCylinder );
    }

    // Return with error
    return false;
}

bool Floppy_Seek( uint32 nDrive, uint32 nGetCylinder ) {

    // Already there?
    if ( nCylinder == nGetCylinder )
        return true;

    Console_Print( K_CIO_VERBOSE, "FLOPPY", "MSR %d\n", inb( K_FDC_MSR ) );


    // Turn motor on
    Floppy_MotorOn( nDrive );
    Console_Print( K_CIO_VERBOSE, "FLOPPY", "Motor on\n" );

    // Send command bytes
    Floppy_SendByte( K_FDC_CMD_SEEK );
    Floppy_SendByte( 0 );
    Floppy_SendByte( nGetCylinder );
    Console_Print( K_CIO_VERBOSE, "FLOPPY", "Seek sent\n" );

    // Wait until seek finished or timeout
    if ( !Floppy_WaitFDC( true ) )
        return false;
    Console_Print( K_CIO_VERBOSE, "FLOPPY", "Seek finished\n" );

    // Now let head settle for 15ms
    //    PIT_Pause( 15 );

    // Turn motor off
    //    Floppy_MotorOff();
    Console_Print( K_CIO_VERBOSE, "FLOPPY", "Motor off\n" );

    // Check that seek worked
    if ( ( nSr0 != 0x20 ) || ( nCylinder != nGetCylinder ) ) {
        return false;
    } else {
        return true;
    }
}

bool Floppy_WaitFDC( bool nSenseInterrupt ) {

    // Wait for interrupt signal to be handled (wait max one second)
    nTimeOut = 1000;
    while ( Kg_bFloppyInterrupt && nTimeOut )
        ;

    // Read in command result bytes
    nStatusPos = 0;
    while ( ( nStatusPos < 7 ) && ( inb( K_FDC_MSR ) & ( 1 << 4 ) ) ) {
        cStatus[ nStatusPos++ ] = Floppy_GetByte();
    }

    // See if we need to send a "sense interrupt status" command
    if ( nSenseInterrupt ) {
        Floppy_SendByte( K_FDC_CMD_SENSEI );
        nSr0 = Floppy_GetByte();
        nCylinder = Floppy_GetByte();
    }
    Kg_bFloppyInterrupt = false;

    // See if we timed out
    if ( !nTimeOut ) {
        // Timed out
        return false;
    } else
        return true;
}

void Floppy_Reset( uint32 nDrive ) {

    // Seek to start
    Floppy_Seek( nDrive, 1 );
    Floppy_Recalibrate( nDrive );
}

void Floppy_Recalibrate( uint32 nDrive ) {

    // Turn the motor on
    Floppy_MotorOn( nDrive );

    // Send actual command bytes
    Floppy_SendByte( K_FDC_CMD_RECAL );
    Floppy_SendByte( 0 );

    // Wait until seek finished
    Floppy_WaitFDC( true );

    // Turn the motor off
    Floppy_MotorOff();
}

void Floppy_MotorOn( uint32 nDrive ) {

    // If motor not already on turn it on
    if ( !bMotorOn ) {

        // Stop motor kill countdown
        nMotorTick = -1;

        // Send motor start command
        outb( ( nDrive << 0x10 ) & 0x0C, K_FDC_DOR );

        // Delay 500ms for motor to spin up
        //        PIT_Pause( 500 );

        // Mark as running
        bMotorOn = true;
    }
}

void Floppy_MotorOff( void ) {

    // Set motor stop countdown
    if ( bMotorOn ) {

        // start motor kill countdown: 2000 ticks ~ 2s
        nMotorTick = 2000;

    }
}

uchar Floppy_GetByte() {
    volatile int nMSR;
    int i;

    for ( i = 0;i < 128;i++ ) {
        nMSR = inb( K_FDC_MSR );
        if ( ( nMSR & 0xd0 ) == 0xd0 ) {
            return inb( K_FDC_PORTDATA );
        }
        inb( 0x80 );
    }

    return -1;
}

void Floppy_SendByte( uchar nByte ) {
    volatile int nMSR;

    int i;
    for ( i = 0;i < 128;i++ ) {
        nMSR = inb( K_FDC_MSR );
        if ( ( nMSR & 0xc0 ) == 0x80 ) {
            outb( nByte, K_FDC_PORTDATA );
            return ;
        }
        inb( 0x80 );
    }
}


void BlockIO_GetLBA( K_sKBlockIODevice_t *pData ) {
    // Converts a Head/Cylinder/Sector
    pData->m_nHead = ( pData->m_nBlock % ( pData->m_nSectorsPerCylinder * pData->m_nTotalHeads ) ) / ( pData->m_nSectorsPerCylinder );
    pData->m_nCylinder = pData->m_nBlock / ( pData->m_nSectorsPerCylinder * pData->m_nTotalHeads );
    pData->m_nSector = pData->m_nBlock % pData->m_nSectorsPerCylinder + 1;
}
