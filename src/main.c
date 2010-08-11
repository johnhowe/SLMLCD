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

#define WAVELENGTH 62

int main(void)
{
    InitController();
    initLCD ();

    animateWaves(); // loops forever

    return(0);
}

