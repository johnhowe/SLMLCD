/*
 * lcd.h
 *
 * Functions for communicating with LCD module
 *
 * John Howe 2010
 */

#ifndef LCD_H
#define LCD_H

#include <stdlib.h>
#include "AT91SAM7S256.h"
#include "slimLib.h"
#include "config.h"
#include "timers.h"
#include "HG24016001G.h"

enum {
    DATA = 0, COMMAND = 1
};

/* DELAYCONST x nop() = 1uS */
#define DELAYCONST 3 // todo: calibrate nop time


/* Init function taken from datasheet */
void initLCD(void);

/* Lookup to speed write() time */
int32* generateLookupTable (void);
/* Manages table, creating it when it is first needed otherwise storing its
 * location */
int32* tableButler (void);

/* Writes instruction or data to I/O ports connected to LCD. */
void write(uint8 type, uint8 instruction);

/* Write unstructured data to LCD */
void testDisplay(void);
void testWrite(void);
void volUp(void);
void volDown(void);

#endif
