/*
 * main.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */

#include "config.h"
#include "init.h"
#include "lcd.h"
#include "timers.h"
#include "HG24016001G.h"

void setTestLed(int state) {
    if (state == on)
        AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LED_A);
    if (state == off)
        AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, LED_A);
}

int main(void) {
    initController();
    initPIO();
    initTimers();
    initLCD();

    testDisplay ();

    for (;;) {
        busyWait(5000);
        setTestLed(on);
        busyWait(5000);
        setTestLed(off);
    }
    return (0);
}
