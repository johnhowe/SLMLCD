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
    testDisplay ();
    //drawVertGradient (0);
    //for (int i = 0; i < 100; i++)
    //int i = 10;   
    //{
        //static uint8 colour = WHITE;
        //drawLine (i, BLACK);
        //colour += 1<<3;
        //if (colour > BLACK) colour = WHITE;
    //}
    for(;;)
    {
        busyWait(1000000);
    }
    return(0);
}
