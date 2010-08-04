/*
 * lcd.h
 *
 * Functions for communicating with LCD module
 *
 * John Howe 2010
 */

#ifndef LCD_H
#define LCD_H

#include "AT91SAM7S256.h"
#include "slimLib.h"
#include "config.h"
#include "timers.h"
#include "HG24016001G.h"

enum { DATA, COMMAND };

/* DELAYCONST x nop() = 1uS */
#define DELAYCONST 3 // todo: calibrate nop time
/* Init function taken from datasheet */
void initLCD(void);

/* Writes instruction or data to I/O ports connected to LCD. */
void write(uint8 type, uint8 instruction);

/* Write unstructured data to LCD */
void testDisplay(void);
void testWrite(void);
void volUp(void);
void volDown(void);

uint16 prepDisplay (uint8 startC, uint8 startR, uint8 endC, uint8 endR);
void drawVertGradient (uint8 origin);
void drawLine (uint8 line, uint8 colour);
void eraseDisplay (void);

#endif
