/*
 * init.c
 *
 *  Initialisation functions for AT91SAM7 microcontroller.
 *  Sourced from Wolfgang Wieser's AT91SAM7 hello world
 *  example program.
 *
 *      John Howe	2010
 */

#include "init.h"

void DefaultInterruptHandler(void) {
	// Do nothing.
}

void SpuriousInterruptHandler(void) {
	// Never do anything; just return as quickly as possible.
}

// Endless loop of LED_A (PA0) blinks for error diagnosis.
// Will blink code-many times and then make a longer delay.
void PanicBlinker(uint8 code) {
	// Be sure to enable the output so that we can also diagnose
	// crashes which happen early.
	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
	pPIO->PIO_PER |= LED_A;
	pPIO->PIO_OER |= LED_A;
	pPIO->PIO_SODR = LED_A;

	for (;;) {
		uint8 i;
		unsigned int j;
		for (i = 0; i < code; i++) {
			pPIO->PIO_CODR = LED_A; // LOW = turn LED on.
			for (j = PANIC_RATE; j; j--)
				nop();
			pPIO->PIO_SODR = LED_A; // HIGH = turn LED off.
			for (j = PANIC_RATE; j; j--)
				nop();
		}
		for (j = PANIC_RATE * 3; j; j--)
			nop();
	}
}

// Hardware initialisation function.
void initController(void) {
	// Set Flash Wait sate
	// Single Cycle Access at Up to 30 MHz, above (up to 55MHz):
	//   at least 1 flash wait state.
	// FMCN: flash microsecond cycle number: Number of MCLK cycles in one usec.
	//   For 20 MHz, this is 20. Value must be rounded up.
	AT91C_BASE_MC->MC_FMR = ((AT91C_MC_FMCN) & (22 << 16)) | AT91C_MC_FWS_0FWS;

	// Disable watchdog.
	AT91C_BASE_WDTC->WDTC_WDMR = AT91C_WDTC_WDDIS;

	AT91PS_PMC pPMC = AT91C_BASE_PMC;
	// After reset, CPU runs on slow clock (32kHz).
	// Enable main oscillator running on crystal by setting AT91C_CKGR_MOSCEN bit in PMC_MOR.
	// Furthermore, specify OSCOUNT in number of slow clock cycles divided by 8.
	// Hence, start up time = 8 * OSCOUNT / 32768 ; result in seconds.
	// OSCOUNT = 6 -> 1.46 ms.
	pPMC->PMC_MOR = ((AT91C_CKGR_OSCOUNT & (6U << 8)) | AT91C_CKGR_MOSCEN);
	// Wait the startup time...
	while (!(pPMC->PMC_SR & AT91C_PMC_MOSCS))
		continue;

	// Phase-locked loop (PLL) initialisation could be inserted here.
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
	while (!(pPMC->PMC_SR & AT91C_PMC_MCKRDY))
		continue;
	// STEP 2:
	pPMC->PMC_MCKR = AT91C_PMC_CSS_MAIN_CLK | AT91C_PMC_PRES_CLK;
	// Wait for MCKRDY.
	while (!(pPMC->PMC_SR & AT91C_PMC_MCKRDY))
		continue;

	// Enable user reset, i.e. allow the controller to be reset by
	// pulling the NRST pin LOW. This aids in debugging.
	AT91C_BASE_RSTC->RSTC_RMR = 0xa5000400U | AT91C_RSTC_URSTEN;

	// Set up the default interrupt handlers for all interrupts.
	// 0 = FIQ, 1 = SYS.
	for (int i = 0; i < 31; i++) {
		AT91C_BASE_AIC->AIC_SVR[i] = (unsigned) &DefaultInterruptHandler;
	}
	// Set spurious interrupt handler. This does nothing and just returns
	// quickly.
	AT91C_BASE_AIC->AIC_SPU = (unsigned) &SpuriousInterruptHandler;

	// NOW, we can enable peripheral clocks if needed (PMC_PCER).
	// ...


}

void initPIO(void) {
	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
	// Allow PIO to control pins.
	pPIO->PIO_PER = LED_A | PA0 | PWR | PRD | PD0 | PD1 | PD2 | PD3 | PD4 | PD5
			| PD6 | PD7 | PXCS | PRST;
	// Enable outputs.
	pPIO->PIO_OER = LED_A | PA0 | PWR | PRD | PD0 | PD1 | PD2 | PD3 | PD4 | PD5
			| PD6 | PD7 | PXCS | PRST;
	// Set outputs HIGH to turn LEDs off.
	pPIO->PIO_SODR = LED_A;
}

