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

    testDisplay ();
    //drawVertGradient (0);
    for(;;)
    {
        busyWait(1000000);
    }
    return(0);
}
