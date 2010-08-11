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
    initController();
    initLCD ();
    eraseDisplay();

    uint16 front = 0;
    for(;;)
    {
        drawWaves (WAVELENGTH, front);
        front++;
        if (front == WAVELENGTH)
        {
            front = 0;
        }
    }
    return(0);
}
