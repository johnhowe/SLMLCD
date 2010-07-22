/* File:   target.h
   Author: M. P. Hayes, UCECE
   Date:   02 June 2007
   Descr: 
*/
#ifndef TARGET_H
#define TARGET_H

#include "AT91SAM7S256.h"

#define F_XTAL 18432000.0
#define CPU_PLL_MUL (72 + 1)
#define CPU_PLL_DIV 14
#define F_PLL (F_XTAL / CPU_PLL_DIV * CPU_PLL_MUL)
#define F_CPU (F_PLL / 2)

#define LED1_PORT PORT_A
#define LED1_BIT 8


#endif /* TARGET_H  */
