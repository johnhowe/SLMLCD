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

    initLCD ();  // causes uC to freeze
    write(COMMAND,DISOFF);

    for(;;)
    {
        pPIO->PIO_CODR |= LED_A;
        busyWait(10000000);
        //busyWait(1000);

        testDisplay ();

        pPIO->PIO_SODR |= LED_A;
        busyWait(10000000);
        //busyWait(1000);

    }
    return(0);
}
