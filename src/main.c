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

    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;

    initLCD ();


    testDisplay ();
    for(;;)
    {
        //        busyWait(10000000);
        //busyWait(100);
        //pPIO->PIO_CODR |= LED_A; // LED_A on D2 pin
        //testWrite ();
        //volUp ();
        //testDisplay();

        //pPIO->PIO_SODR |= LED_A;

        busyWait(100000);
        busyWait(100);

    }
    return(0);
}
