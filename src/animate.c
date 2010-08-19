/*
 * animate.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */


#include "animate.h"

void drawWaves (uint8 wavelength, uint8 wavefront, uint8 direction);
void shiftFront (colour_t *colour);

void wavesLoop (void)
{
    uint16 front = 0;
    for(;;)
    {
        drawWaves (WAVELENGTH, front, rising);
        front++;
        if (front == WAVELENGTH)
        {
            front = 0;
        }
    }
}

void seesawLoop(void)
{
    for (;;)
    {
        eraseDisplay ();
        drawWaves (WAVELENGTH, 0, rising);
        busyWait (10000000);
        eraseDisplay ();
        drawWaves (WAVELENGTH, 0, falling);
        busyWait (10000000);
    }
}


void drawWaves (uint8 wavelength, uint8 wavefront, uint8 direction)
{
    colour_t colour;
    colour.shade = WHITE>>3; // be careful with colours being <<3'd
    colour.direction = direction;

    for (int i = 0; i < wavefront; i++)
        shiftFront (&colour);

    uint16 pix = prepDisplay(1, 1, LCD_WIDTH, LCD_HEIGHT);

    // For determining where to change colour
    uint16 shiftWidth = LCD_WIDTH/3; // TODO wavelength should be in here.
    uint16 shiftPx = pix - shiftWidth;
    while (pix--)
    {
        write (DATA, colour.shade<<3);
        write (DATA, colour.shade<<3);
        write (DATA, colour.shade<<3);

        if (pix == shiftPx) // shifts colour at each row
        {
            shiftFront (&colour);
            shiftFront (&colour);
            shiftPx -= shiftWidth;
        }
        //busyWait(10000);
    }
}

void shiftFront (colour_t *colour)
{
    if (colour->direction == rising) // white -> black
    {
        colour->shade++;
        if (colour->shade == (BLACK >> 3))
            colour->direction = falling;
    }
    else // black -> white
    {
        colour->shade--;
        if (colour->shade == (WHITE >> 3))
            colour->direction = rising;
    }
}

