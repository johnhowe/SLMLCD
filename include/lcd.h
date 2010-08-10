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
#include "waves.h"

enum { DATA, COMMAND };
enum { RISING, FALLING };

/* Contains start and end coordinates to be used whith
 * prepDisplay */
typedef enum { 
    startCol,
    endCol,
    startRow,
    endRow
} window_t;



/* Init function taken from datasheet */
void initLCD(void);

/* Writes instruction or data to I/O ports connected to LCD. */
void write(uint8 type, uint8 instruction);

/* Prepares the LCD module to accept a stream of data to be
 * displayed. Accepts coordinates for the window and returns the
 * number of pixels to be written to. */
uint16 prepDisplay (window_t window);

/* Sets all pixels -> 0 */
void eraseDisplay (void);

#endif
