/*
 * config.h
 *
 *  Configuration of Spatial Light Modulator board
 *      John Howe	2010
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "AT91SAM7S256.h"

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed long int32;
typedef unsigned long uint32;

#define TRUE 1
#define FALSE 0

#define nop()  __asm__ __volatile__("nop")
#define LED_A	(1U<<8)			// Status LED
#define PANIC_RATE	300000		// Delay time used in panic function

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))

// Pin definitions
#define PA0		AT91C_PIO_PA30
#define PWR		AT91C_PIO_PA4
#define PRD		AT91C_PIO_PA28
#define PD0		AT91C_PIO_PA6
#define PD1		AT91C_PIO_PA26
#define PD2		AT91C_PIO_PA8
#define PD3		AT91C_PIO_PA24
#define PD4		AT91C_PIO_PA10
#define PD5		AT91C_PIO_PA22
#define PD6		AT91C_PIO_PA12
#define PD7		AT91C_PIO_PA20
#define PXCS	        AT91C_PIO_PA14
#define PRST	        AT91C_PIO_PA21

#define PD  PD0|PD1|PD2|PD3|PD4|PD5|PD6|PD7

#endif
