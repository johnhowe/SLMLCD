/*
 * timers.h
 *
 *	Timer functions to be used on the ARM7
 */

#ifndef TIMERS_H
#define TIMERS_H

#include "config.h"
#include "slimLib.h"

void initTimers(void);


/* Delay for a period of time in microseconds */
void busyWait(uint32 delay);

#endif
