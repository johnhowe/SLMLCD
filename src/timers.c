/*
 * timers.c
 *
 * Timer functions to be used on the ARM7
 */

#include "timers.h"

/* Configure timers */
void initTimers(void) {
    AT91F_PMC_EnablePeriphClock(AT91C_BASE_PMC, 1 << AT91C_ID_TC0);// Enable TC0
    *AT91C_TC0_CMR = AT91C_TC_CLKS_TIMER_DIV5_CLOCK; // DIV1 = MCK/2 clock speed (MCK = 18.432 KHz?)
    *AT91C_TC0_CCR = AT91C_TC_CLKEN; // Enable clock
    *AT91C_TC0_CCR = AT91C_TC_SWTRG; // Reset clock
}

/* Delay for a period time */
void busyWait(uint32 delay) {
    // todo: something isn't right here
    //while (*AT91C_TC0_CV <= delay)
        //continue;
    //*AT91C_TC0_CCR = AT91C_TC_SWTRG;
    uint32 j;
    for (j = 0; j < delay; j++) {
        nop();
    }
}
