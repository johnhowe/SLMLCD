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


int main(void)
{
    InitController();
    initLCD ();
    eraseDisplay();

    uint8 baseColour = WHITE;
    uint8 fadeOut = TRUE;
    for(;;)
    {
        stripe (baseColour);
        if (fadeOut)
        {
            baseColour -= 1<<3;
            if (baseColour == WHITE)
                fadeOut = FALSE;
        }
        else
        {
            baseColour += 1<<3;
            if (baseColour == BLACK)
                fadeOut = TRUE;
        }
    }
    return(0);
}
