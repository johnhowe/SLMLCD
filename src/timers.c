/*
 * timers.c
 *
 *	Timer functions to be used on the ARM7
 */

#include "timers.h"

/* Configure timers */
void initTimers(void) {
}

/* Delay for a period of time in microseconds */
void busyWait(uint32 delay) {
	while (delay--)
		nop ();
}
