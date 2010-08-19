/*
 * animate.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */


#include "animate.h"

void wavesLoop (void)
{
    uint16 front = 0;
    for(;;)
    {
        drawWaves (WAVELENGTH, front);
        front++;
        if (front == WAVELENGTH)
        {
            front = 0;
        }
    }
}

