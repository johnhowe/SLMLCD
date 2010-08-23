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

#define APERTURE 32
#define MAX_STEPS 32 // number of shades of grey
#define DISPLAY_TIME 20000000
#define TRANSITION_TIME 10000000


// Waves moving down the display
void wavesLoop (void);

// Switching between gradient one direction to the other
void seesawLoop (void);

// Gradually increasing gradient
void slideLoop (void);

