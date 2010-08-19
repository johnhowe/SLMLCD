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

#define APPATURE 32 // multiple of 32
#define MAX_STEPS 32 // number of shades of grey

void slideLoop (void)
{
    uint8 steps = 0; 
    while (TRUE)
    {
        for (uint16 t = 0; t < DURATION; t++)
        {
            // Draw slide at `steps' gradient for `duration' frames 
            // TODO animate
        }
        steps ++;
        steps %= MAX_STEPS;
    }
}


int main(void)
{
    InitController();
    initLCD ();
    eraseDisplay();

    slideLoop();

    return(0);
}
