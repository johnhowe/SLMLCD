/*
 * main.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */


#include "config.h"
#include "init.h"
#include "lcd.h"
#include "animate.h"





int main(void)
{
    InitController();
    initLCD ();

    slideLoop();
    //wavesLoop();
    //seesawLoop();

    return(0);
}
