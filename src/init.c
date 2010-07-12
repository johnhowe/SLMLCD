/*
 * init.c
 *
 *  Initialisation functions for AT91SAM7 microcontroller.
 *  Based on Wolfgang Wieser's AT91SAM7 hello world
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

	AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, LED_A);
	AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LED_A);

	for (;;) {
		uint8 i;
		unsigned int j;
		for (i = 0; i < code; i++) {
			AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, LED_A);
			for (j = PANIC_RATE; j; j--)
				nop();
			AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LED_A);
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
	AT91F_MC_EFC_CfgModeReg(AT91C_BASE_MC, ((AT91C_MC_FMCN) & (22 << 16))
			| AT91C_MC_FWS_0FWS);
	// Disable watchdog.
	AT91F_WDTSetMode(AT91C_BASE_WDTC, AT91C_WDTC_WDDIS);

	//todo: REMOVE THIS
	AT91PS_PMC pPMC = AT91C_BASE_PMC; // Power Management Controller (PMC) base address

	// After reset, CPU runs on slow clock (32kHz).
	// Enable main oscillator running on crystal by setting AT91C_CKGR_MOSCEN bit in PMC_MOR.
	// Furthermore, specify OSCOUNT in number of slow clock cycles divided by 8.
	// Hence, start up time = 8 * OSCOUNT / 32768 ; result in seconds.
	// OSCOUNT = 6 -> 1.46 ms.
	pPMC->PMC_MOR = ((AT91C_CKGR_OSCOUNT & (6U << 8)) | AT91C_CKGR_MOSCEN); //todo
	// Wait the startup time...
	while (!(AT91F_PMC_GetStatus(AT91C_BASE_PMC) & AT91C_PMC_MOSCS))
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
	AT91F_PMC_CfgMCKReg(AT91C_BASE_PMC, AT91C_PMC_CSS_MAIN_CLK);
	// Wait for MCKRDY.
	while (!(AT91F_PMC_GetStatus(AT91C_BASE_PMC) & AT91C_PMC_MCKRDY))
		continue;
	// STEP 2:
	AT91F_PMC_CfgMCKReg(AT91C_BASE_PMC, AT91C_PMC_CSS_MAIN_CLK
			| AT91C_PMC_PRES_CLK);
	// Wait for MCKRDY.
	while (!(AT91F_PMC_GetStatus(AT91C_BASE_PMC) & AT91C_PMC_MCKRDY))
		continue;

	// Enable user reset, i.e. allow the controller to be reset by
	// pulling the NRST pin LOW. This aids in debugging.
	AT91F_RSTSetMode(AT91C_BASE_RSTC, 0xa5000400U | AT91C_RSTC_URSTEN);

	// Set up the default interrupt handlers for all interrupts.
	AT91F_AIC_Open(AT91C_BASE_AIC, // \arg pointer to the AIC registers
			(void*) &DefaultInterruptHandler, // \arg Default IRQ vector exception
			(void*) &DefaultInterruptHandler, // \arg Default FIQ vector exception
			(void*) &DefaultInterruptHandler, // \arg Default Handler set in ISR
			(void*) &SpuriousInterruptHandler, // \arg Default Spurious Handler
			AT91C_AIC_DCR_GMSK); // \arg Debug Control Register);
}

void initPIO(void) {
	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
	// Enable PIO in output mode
	AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, LED_A | PA0 | PWR | PRD | PXCS | PRST
			| PD0 | PD1 | PD2 | PD3 | PD4 | PD5 | PD6 | PD7);

	// Set all pins LOW
	AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, LED_A | PA0 | PWR | PRD | PXCS | PRST
			| PD0 | PD1 | PD2 | PD3 | PD4 | PD5 | PD6 | PD7);
}
