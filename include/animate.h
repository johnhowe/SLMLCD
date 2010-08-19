/*
 * animate.h
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */


#include "config.h"
#include "init.h"
#include "lcd.h"
#include "HG24016001G.h"
#include "timers.h"

#define WAVELENGTH 62

// Waves moving down the display
void wavesLoop (void);

void seesawLoop (void);
