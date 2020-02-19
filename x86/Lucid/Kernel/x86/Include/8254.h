// (C) Daryl Dudey 2002

#ifndef __K_X86_PIT_H__
#define __K_X86_PIT_H__

// TICKSPERSEC is a dividor because the PIT ticks at 1,193,181Hz
#define PIT_TICKSPERSEC	 0x1234DDL

// We want the timer to tick at 1000Hz, to give us a nice responsive system
#define	PIT_FREQ	 1000

// Calculate value to send to PIT
#define PIT_SPEED		 (PIT_TICKSPERSEC / PIT_FREQ)

void PIT_Init( void );
void PIT_StopTimer( void );

#endif // __K_X86_PIT_H__
