/*
 * timers.h
 *
 *	Timer functions to be used on the ARM7
 */

#include "config.h"

void initTimers(void);

/* Delay for a period of time in microseconds */
void busyWait(uint32 delay);
