/*
 * timers.c
 *
 *	Timer functions to be used on the ARM7
 */

#include "timers.h"


/* Configure timers */
void initTimers(void) {
	volatile AT91PS_PMC pPMC = AT91C_BASE_PMC; // Power Management Controller (PMC) base address
	pPMC->PMC_PCER = 1 << AT91C_ID_TC0; // Enable TC0
	*AT91C_TC0_CMR = AT91C_TC_CLKS_TIMER_DIV5_CLOCK; // DIV1 = MCK/2 clock speed (MCK = 18.432 KHz?)
	*AT91C_TC0_CCR = AT91C_TC_CLKEN; // Enable clock
	*AT91C_TC0_CCR = AT91C_TC_SWTRG; // Reset clock
}

/* Delay for a period time */
void busyWait(uint16 delay) {
	while (*AT91C_TC0_CV <= delay)
		continue;
	*AT91C_TC0_CCR = AT91C_TC_SWTRG;
}

