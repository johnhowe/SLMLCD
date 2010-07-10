/*
 * lcd.c
 *
 *  Functions for communicating with LCD module
 *
 *      John Howe	2010
 */

#include "lcd.h"
#include "timers.h"
#include "HG24016001G.h"

/* Init function taken from datasheet */
void initLCD(void) {
	busyWait(10000); // 10ms
	write(COMMAND, EXTIN);
	write(COMMAND, SLPOUT);
	write(COMMAND, OSCON);
	write(COMMAND, PWRCTR);
	write(DATA, 0x08); // booster must be on first
	busyWait(1000); // wait one millisecond
	write(COMMAND, PWRCTR);
	write(DATA, 0x0b); // booster, regulator, follower on
	write(COMMAND, VOLCTR);
	write(DATA, 0x32); // DL38
	write(DATA, 0x04); // DH,Vop = 15.5v, normal display
	write(COMMAND, DISCTL);
	write(DATA, 0x04); // CLD = 0, not divide
	write(DATA, 0x27); // 1/160 duty 39
	write(DATA, 0x00); // FR
	write(COMMAND, DISINV);
	write(COMMAND, COMSCN);
	write(DATA, 0x01); // 0->79  159->80
	write(COMMAND, DATSDR);
	write(DATA, 0x00); // normal
	write(DATA, 0x00); // RGB arrangement
	write(DATA, 0x02); // 32 gray-scale 3byte 3pixel mode
	write(COMMAND, LASET);
	write(DATA, 0x00); // start line = 0
	write(DATA, 0x9f); // end line = 159
	write(COMMAND, CASET);
	write(DATA, 0x00); // start column = 0
	write(DATA, 0xf4); // end column = 79 -> (79+1)*3=240

	write(COMMAND, EXTOUT);
	write(COMMAND, ANASET);
	write(DATA, 0x07); // oscillator frequency = 12.7KHz
	write(DATA, 0x02); // Booter frequency = 6KHz
	write(DATA, 0x03); // bias = 1/11
	write(COMMAND, SWINT);
	write(COMMAND, EXTIN);
	write(COMMAND, DISON);
	busyWait(10000); // 10ms
}

/* Writes instruction or data to I/O ports connected to LCD. */
void write(uint8 type, uint8 instruction) {
	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA; // (PIOA) Base Address
	uint32 PIOmask = 0;

	/* Set first 3 bits according to data or command type */
	if (type == COMMAND) {
		PIOmask |= PRD;
	} else if (type == DATA) {
		PIOmask |= PA0;
		PIOmask |= PRD;
	} else {
		//todo: write() type error
	}

	// Moves bits to correct locations for IO port. Probably need to modify
	// PCB to make this more efficient.
	if (bitRead (instruction, CD0))
		PIOmask |= PD0;
	if (bitRead (instruction, CD1))
		PIOmask |= PD1;
	if (bitRead (instruction, CD2))
		PIOmask |= PD2;
	if (bitRead (instruction, CD3))
		PIOmask |= PD3;
	if (bitRead (instruction, CD4))
		PIOmask |= PD4;
	if (bitRead (instruction, CD5))
		PIOmask |= PD5;
	if (bitRead (instruction, CD6))
		PIOmask |= PD6;
	if (bitRead (instruction, CD7))
		PIOmask |= PD7;

	// Overwrites _all_ pins on port A according to PIOmask
	pPIO -> PIO_SODR = PIOmask;
}

/* Write unstructured data to LCD */
void testDisplay(void) {
	uint8 j, k;
	write(COMMAND, EXTIN);
	write(COMMAND, CASET);
	write(DATA, 0x00);
	write(DATA, 0xf4);
	write(COMMAND, LASET);
	write(DATA, 0x00);
	write(DATA, 0x9f);
	write(COMMAND, RAMWR);
	for (j = 0; j < 160; j++) {
		for (k = 0; k < 80; k++) {
			write(DATA, 0xff);
		}
	}
	//	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
	////	busyWait(1000);
	//	pPIO->PIO_CODR |= LED_A;
	////	busyWait(1000);
	//	write(DATA, 0xff);
	////	busyWait(1000);
	//	write(DATA, 0x00);
	////	busyWait(1000);
	//	pPIO->PIO_SODR |= LED_A;
}
