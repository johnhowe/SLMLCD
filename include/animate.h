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

#define APPATURE 32 // multiple of 32
#define MAX_STEPS 32 // number of shades of grey
#define DURATION 20 // number of frames to show before switchin gradient

// Waves moving down the display
void wavesLoop (void);

void seesawLoop (void);
