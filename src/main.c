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

int main(void)
{
	InitController();

	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;

	initLCD ();
	writeInstruction (DISOFF);

	for(;;)
	{
		pPIO->PIO_CODR |= LED_A;
		for(int j=0; j<10000; j++) { nop(); }
		pPIO->PIO_SODR |= LED_A;
		for(int j=0; j<5000; j++) { nop(); }
                writeInstruction (EXTIN);
		for(int j=0; j<5000; j++) { nop(); }
                writeInstruction (EXTOUT);
		for(int j=0; j<5000; j++) { nop(); }
	}
	return(0);
}
