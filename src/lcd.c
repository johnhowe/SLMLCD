/*
 * lcd.c
 *
 *  Functions for communicating with LCD module
 *
 *      John Howe	2010
 */

#include "lcd.h"
#include "HG24016001G.h"

void initLCD (void)
{
	writeInstruction(EXTIN);
	writeInstruction(SLPOUT);
	writeInstruction(OSCON);
	writeInstruction(PWRCTR);
	writeData(0x08);		// booster must be on first
	nop(); nop(); nop();	// delay (should be 1ms)
	writeInstruction(PWRCTR);
	writeData(0x0b);		// booster, regulator, follower on
	writeInstruction(VOLCTR);
	writeData(0x32);		// DL38
	writeData(0x04);		// DH,Vop = 15.5v, normal display
	writeInstruction(DISCTL);
	writeData(0x04);		// CLD = 0, not divide
	writeData(0x27);		// 1/160 duty 39
	writeData(0x00);		// FR
	writeInstruction(DISINV);
	writeInstruction(COMSCN);
	writeData(0x01);		// 0->79  159->80
	writeInstruction(DATSDR);
	writeData(0x00);		// normal
	writeData(0x00);		// RGB arrangement
	writeData(0x02);		// 32 gray-scale 3byte 3pixel mode
	writeInstruction(LASET);
	writeData(0x00);		// start line = 0
	writeData(0x9f);		// end line = 159
	writeInstruction(CASET);
	writeData(0x00);		// start column = 0
	writeData(0xf4);		// end column = 79

	writeInstruction(EXTOUT);
	writeInstruction(ANASET);
	writeData(0x07);		// oscillator frequency = 12.7KHz
	writeData(0x02);		// Booter frequency = 6KHz
	writeData(0x03);		// bias = 1/11
	writeInstruction(SWINT);
	writeInstruction(EXTIN);
	writeInstruction(DISON);
}

/* Writes instruction to I/O ports connected to LCD. */
void writeInstruction (uint8 instruction)
{
	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;  // (PIOA) Base Address
	uint32 PIOmask;

	// Moves bits to correct locations for IO port. Probably need to modify
	// PCB to make this more efficient.
	if (bitRead (instruction, CD0)) { PIOmask |= PD0; }
	if (bitRead (instruction, CD1)) { PIOmask |= PD1; }
	if (bitRead (instruction, CD2)) { PIOmask |= PD2; }
	if (bitRead (instruction, CD3)) { PIOmask |= PD3; }
	if (bitRead (instruction, CD4)) { PIOmask |= PD4; }
	if (bitRead (instruction, CD5)) { PIOmask |= PD5; }
	if (bitRead (instruction, CD6)) { PIOmask |= PD6; }
	if (bitRead (instruction, CD7)) { PIOmask |= PD7; }
	PIOmask |= PRD;

	// Overwrites all ports on port A
	pPIO -> PIO_SODR = PIOmask;
}

void writeData (uint8 instruction)
{

}
