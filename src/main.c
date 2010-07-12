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

	for (;;) {
		// Testing function for the timer calibrations
		busyWait(1000);
		setTestLed(on);
		busyWait(1000);
		setTestLed(off);
		//fuckAll();
	}
	return (0);
}
