/*
 * waves.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */

#include "waves.h"

void drawWaves (uint8 wavelength, uint8 wavefront, window_t *window);
void shiftFront (colour_t *colour);

/* Draw a series of frames of waves to create an animation */
void animateWaves (uint8 wavelength, window_t *window)
{
    uint16 front = 0;
    for(;;)
    {
        drawWaves (wavelength, front, window);
        front++;
        if (front == wavelength)
        {
            front = 0;
        }
    }
}

/* Draw a single frame of waves on the LCD */
// wavelength is the separation between peaks FIXME: needs to be a multiple of 32 
// front is an offset for the first wave 
void drawWaves (uint8 wavelength, uint8 wavefront, window_t *window)
{
    colour_t colour;
    colour.shade = WHITE>>3; // care as colours <<3'd
    colour.direction = RISING;

    for (int i = 0; i < wavefront; i++) 
    {
        shiftFront (&colour);
    }

    uint16 pix = prepDisplay(window);

    // For determining where to change colour
    uint16 shiftWidth = (wavelength * (window->endCol - window->startCol)/3) / 64;
    uint16 shiftPx = pix - shiftWidth;
    while (pix--)
    {
        write (DATA, colour.shade<<3);
        write (DATA, colour.shade<<3);
        write (DATA, colour.shade<<3);

        if (pix == shiftPx) 
        {
            shiftFront (&colour);
            shiftPx -= shiftWidth;
        }
    }
}

/* Moves the colour according to its direction */
void shiftFront (colour_t *colour)
{
    if (colour->direction == RISING) // white -> black
    {
        colour->shade++;
        if (colour->shade == (BLACK >> 3))
            colour->direction = FALLING;
    }
    else // black -> white
    {
        colour->shade--;
        if (colour->shade == (WHITE >> 3))
            colour->direction = RISING;
    }
}

