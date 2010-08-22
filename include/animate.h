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
#define DISPLAY_TIME 50000000
#define TRANSITION_TIME 5000000


// Waves moving down the display
void wavesLoop (void);

void seesawLoop (void);

void slideLoop (void);

