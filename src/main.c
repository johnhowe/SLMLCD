/*
 * main.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */


#include "config.h"
#include "init.h"
#include "lcd.h"
#include "HG24016001G.h"
#include "timers.h"
#include "waves.h"

const uint8 wavelength = 62;

int main(void)
{
    InitController();
    initLCD ();

    window_t window;
    window.startCol = 0;
    window.endCol = 240;
    window.startRow = 0;
    window.endRow = 160;
    animateWaves(wavelength, &window); // loops forever

    return(0);
}

