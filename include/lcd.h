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
#include "timers.h"
#include "HG24016001G.h"

// Command locations
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

enum {
	DATA = 0, COMMAND = 1
};

/* DELAYCONST x nop() = 1uS */
#define DELAYCONST 3	// todo: calibrate nop time
/* Init function taken from datasheet */
void initLCD(void);

/* Writes instruction or data to I/O ports connected to LCD. */
void write(uint8 type, uint8 instruction);

/* Write unstructured data to LCD */
void testDisplay(void);

void nothing (void);

#endif /* LCD_H_ */