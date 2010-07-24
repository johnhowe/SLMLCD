/*
 * lcd.h
 *
 *  Functions for communicating with LCD module
 *
 *      John Howe	2010
 */


#ifndef LCD_H_
#define LCD_H_

#include "config.h"

// Command syntax
// A0 RD WR D7 D6 D5 D4 D3 D2 D1 D0
#define CD0		0
#define CD1		1
#define CD2		2
#define CD3		3
#define CD4		4
#define CD5		5
#define CD6		6
#define CD7		7
#define CWR		8
#define CRD		9
#define CA0		10


void initLCD (void);

/* Writes instruction to I/O ports connected to LCD.
 * Assumes EXT is set correctly.  */
void writeInstruction (uint8 instruction);

void writeData (uint8 instruction);


#endif /* LCD_H_ */
