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
    busyWait(1000000);
    drawVertGradient (0);
    for(;;)
    {
        //        busyWait(10000000);
        //busyWait(100);
        //pPIO->PIO_CODR |= LED_A; // LED_A on D2 pin
        //testWrite ();
        //volUp ();
        //testDisplay();

        //pPIO->PIO_SODR |= LED_A;

        busyWait(100);

    }
    return(0);
}
