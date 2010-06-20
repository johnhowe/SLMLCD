/*
 * main.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */

#include "AT91SAM7.h"
#include "config.h"
#include "init.h"

int main(void)
{
	Initialise();

	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;

	for(;;)
	{
		pPIO->PIO_CODR = LED_A;
		for(int j=0; j<60000; j++) { nop(); }
		pPIO->PIO_SODR = LED_A;
		for(int j=0; j<2500000; j++) { nop(); }
	}
	return(0);
}
