/* 
 * Inline functions taken from lib_AT91SAM7S256.h
 *
 */

#ifndef SLIMLIB_H
#define SLIMLIB_H

#include "AT91SAM7S256.h"

//*----------------------------------------------------------------------------
//* \fn    AT91F_PIO_CfgOutput
//* \brief Enable PIO in output mode
//*----------------------------------------------------------------------------
static inline void AT91F_PIO_CfgOutput(
        AT91PS_PIO pPio,             // \arg pointer to a PIO controller
        unsigned int pioEnable)      // \arg PIO to be enabled
{
    pPio->PIO_PER = pioEnable; // Set in PIO mode
    pPio->PIO_OER = pioEnable; // Configure in Output
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_PIO_ClearOutput
//* \brief Set to 0 output PIO
//*----------------------------------------------------------------------------
static inline void AT91F_PIO_ClearOutput(
        AT91PS_PIO pPio,   // \arg  pointer to a PIO controller
        unsigned int flag) // \arg  output to be cleared
{
    pPio->PIO_CODR = flag;
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_PIO_SetOutput
//* \brief Set to 1 output PIO
//*----------------------------------------------------------------------------
static inline void AT91F_PIO_SetOutput(
        AT91PS_PIO pPio,   // \arg  pointer to a PIO controller
        unsigned int flag) // \arg  output to be set
{
    pPio->PIO_SODR = flag;
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_PMC_EnablePeriphClock
//* \brief Enable peripheral clock
//*----------------------------------------------------------------------------
static inline void AT91F_PMC_EnablePeriphClock (
	AT91PS_PMC pPMC, // \arg pointer to PMC controller
	unsigned int periphIds)  // \arg IDs of peripherals
{
	pPMC->PMC_PCER = periphIds;
}

#endif
