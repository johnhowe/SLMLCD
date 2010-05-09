/*
 * main.c - AT91SAM7 hello world example program.
 *
 * Copyright (c) 2007 by Wolfgang Wieser ] wwieser (a) gmx <*> de [
 *
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation. (See COPYING.GPL for details.)
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 */

#include "AT91SAM7.h"

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed long int32;
typedef unsigned long uint32;

#define nop()  __asm__ __volatile__("nop")

#define LED_A      (1U<<8)   /* STAT LED */


// NOTE! Must be compiled in ARM mode as it is directly called from ISR.
static void DefaultInterruptHandler(void)
{
	// Do nothing.
}

// NOTE! Must be compiled in ARM mode as it is directly called from ISR.
static void SpuriousInterruptHandler(void)
{
	// Never do anything; just return as quickly as possible.
}


// Endless loop of LED_A (PA0) blinks for error diagnosis.
// Will blink code-many times and then make a longer delay.
// NOTE: Must be compiled in ARM mode.
extern void PanicBlinker(uint8 code);
void PanicBlinker(uint8 code)
{
	// Be sure to enable the output so that we can also diagnose
	// crashes which happen early.
	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
	pPIO->PIO_PER |= LED_A;
	pPIO->PIO_OER |= LED_A;
	pPIO->PIO_SODR = LED_A;

	for(;;)
	{
		uint8 i;
		unsigned int j;
		for(i=0; i<code; i++)
		{
			pPIO->PIO_CODR = LED_A;  // LOW = turn LED on.
			for(j=300000; j; j--)  nop();
			pPIO->PIO_SODR = LED_A;  // HIGH = turn LED off.
			for(j=300000; j; j--)  nop();
		}

		for(j=300000*3; j; j--)  nop();
	}
}


// Hardware initialization function.
static void Initialize(void)
{
	// Set Flash Wait sate
	// Single Cycle Access at Up to 30 MHz, above (up to 55MHz):
	//   at least 1 flash wait state.
	// FMCN: flash microsecond cycle number: Number of MCLK cycles in one usec.
	//   For 20 MHz, this is 20. Value must be rounded up.
	AT91C_BASE_MC->MC_FMR = ((AT91C_MC_FMCN)&(22 <<16)) | AT91C_MC_FWS_0FWS;

	// Disable watchdog.
	AT91C_BASE_WDTC->WDTC_WDMR= AT91C_WDTC_WDDIS;

	AT91PS_PMC pPMC = AT91C_BASE_PMC;
	// After reset, CPU runs on slow clock (32kHz).
	// Enable main oscillator running on crystal by setting AT91C_CKGR_MOSCEN bit in PMC_MOR.
	// Furthermore, specify OSCOUNT in number of slow clock cycles divided by 8.
	// Hence, start up time = 8 * OSCOUNT / 32768 ; result in seconds.
	// OSCOUNT = 6 -> 1.46 ms.
	pPMC->PMC_MOR = (( AT91C_CKGR_OSCOUNT & (6U <<8)) | AT91C_CKGR_MOSCEN );
	// Wait the startup time...
	while(!(pPMC->PMC_SR & AT91C_PMC_MOSCS));

	// PLL initialisation could be inserted here.
	// Currently, PLL is not used.

	// Select master clock (MCK).
	// Bit 0,1: clock source (CSS):
	//    AT91C_PMC_CSS_SLOW_CLK (0) -> slow clock
	//    AT91C_PMC_CSS_MAIN_CLK (1) -> main clock
	//                            2  -> res
	//    AT91C_PMC_CSS_PLL_CLK  (3) -> PLL clock
	// Bit 2..4: Processor clock prescaler: Divide selected clock by 1,2,4,8,16,32,64:
	//    AT91C_PMC_PRES_CLK, AT91C_PMC_PRES_CLK_2, AT91C_PMC_PRES_CLK_4,...
	// We need to do this in 2 steps conforming to data sheet p.217.
	// STEP 1:
	pPMC->PMC_MCKR = AT91C_PMC_CSS_MAIN_CLK;
	// Wait for MCKRDY.
	while(!(pPMC->PMC_SR & AT91C_PMC_MCKRDY));
	// STEP 2:
	pPMC->PMC_MCKR = AT91C_PMC_CSS_MAIN_CLK | AT91C_PMC_PRES_CLK;
	// Wait for MCKRDY.
	while(!(pPMC->PMC_SR & AT91C_PMC_MCKRDY));

	// Enable user reset, i.e. allow the controller to be reset by
	// pulling the NRST pin LOW. This aids in debugging.
	AT91C_BASE_RSTC->RSTC_RMR = 0xa5000400U | AT91C_RSTC_URSTEN;

	// Set up the default interrupt handlers for all interrupts.
	// 0 = FIQ, 1 = SYS.
	int i;
	for(i=0; i<31; i++)
	{  AT91C_BASE_AIC->AIC_SVR[i] = (unsigned)&DefaultInterruptHandler;  }
	// Set spurious interrupt handler. This does nothing and just returns
	// quickly.
	AT91C_BASE_AIC->AIC_SPU = (unsigned)&SpuriousInterruptHandler;

	// NOW, we can enable peripheral clocks if needed (PMC_PCER).
	// ...

	// Set up the IOs.
	volatile AT91PS_PIO	pPIO = AT91C_BASE_PIOA;
	// Allow PIO to control LEDs.
	pPIO->PIO_PER = LED_A;
	// Enable outputs for LED pins.
	pPIO->PIO_OER = LED_A;
	// Set outputs HIGH to turn LEDs off.
	pPIO->PIO_SODR = LED_A;
}


int main(void)
{
	// Initialize the AT91SAM7...
	Initialize();

	// *(int*)0x800000=177;             // <-- Causes data abort.
	// (*((void(*)(void))0x800000))();  // <-- Causes prefetch abort.


	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
	unsigned int j;
	for(;;)
	{
		// Toggle...
		pPIO->PIO_CODR = LED_A;
		for(j=300000; j; j--)  nop();
		pPIO->PIO_SODR = LED_A;
		for(j=1800000; j; j--)  nop();
		// Toggle again...
		pPIO->PIO_CODR = LED_A;
		for(j=900000; j; j--)  nop();
		pPIO->PIO_SODR = LED_A;
		for(j=300000; j; j--)  nop();

		// Wait a bit...
		int i;
		for(i=0; i<10; i++) nop();
	}
	return(0);
}
