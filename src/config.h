/*
 * config.h
 *
 *  Configuration of Spatial Light Modulator board
 *      John Howe	2010
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "AT91SAM7.h"

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed long int32;
typedef unsigned long uint32;

#define nop()  __asm__ __volatile__("nop")
#define LED_A	(1U<<8)			// Status LED
#define PANIC_RATE	300000		// Delay time used in panic function

// Pin definitions
#define A0		AT91C_PIO_PA30
#define WR		AT91C_PIO_PA4
#define RD		AT91C_PIO_PA28
#define D0		AT91C_PIO_PA6
#define D1		AT91C_PIO_PA26
#define D2		AT91C_PIO_PA8
#define D3		AT91C_PIO_PA24
#define D4		AT91C_PIO_PA10
#define D5		AT91C_PIO_PA22
#define D6		AT91C_PIO_PA12
#define D7		AT91C_PIO_PA20
#define XCS		AT91C_PIO_PA14
#define RST		AT91C_PIO_PA21

#endif
