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

int main(void) {
	initController();
	initPIO();

	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
	//	initLCD();
	//
	//	testDisplay();
	//
	for (;;) {
		pPIO->PIO_CODR |= PD7;//LED_A;
		busyWait(1000);
		pPIO->PIO_SODR |= PD7;//LED_A;
		busyWait(1000);
	}
	return (0);
}
