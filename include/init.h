/*
 * init.h
 *
 *  Initialisation functions for AT91SAM7 microcontroller.
 *  Sourced from Wolfgang Wieser's AT91SAM7 hello world
 *  example program.
 *
 *      John Howe	2010
 */

#ifndef INIT_H
#define INIT_H

#include "config.h"
#include "timers.h"

// Endless loop of LED_A (PA0) blinks for error diagnosis.
// Will blink code-many times and then make a longer delay.
void PanicBlinker(uint8 code);
// Hardware initialisation function.
void InitController(void);

#endif
