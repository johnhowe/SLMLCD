/*
 * animate.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */


#include "animate.h"


void slide (uint8 aperture, uint8 steps, uint8 front, uint8 direction);
void drawWaves (uint8 wavelength, uint8 wavefront, uint8 direction);
void shiftFront (colour_t *colour, uint8 steps);

void wavesLoop (void)
{
    uint16 front = 0;
    uint16 wavelength = 64;
    for(;;)
    {
        drawWaves (wavelength, front, rising);
        front++;
        if (front == wavelength)
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
        drawWaves (APERTURE, 0, rising);
        busyWait (10000000);
        eraseDisplay ();
        drawWaves (APERTURE, 0, falling);
        busyWait (10000000);
    }
}

void slideLoop (void)
{
    uint8 steps = 0; 
    while (TRUE)
    {
        steps ++;
        slide (APERTURE, steps, 0, 0);
        busyWait (DISPLAY_TIME);
      //  eraseDisplay ();
        if (steps == MAX_STEPS)
        {
            steps = 0;
            eraseDisplay ();
            busyWait (2*DISPLAY_TIME);
        }
    }
}


/*********************
 * Private functions *
 *********************/

/* Draws a single frame on the display at a given gradient */
// aperture - number of lines for one wavelength to cover
// steps - number of colour levels per aperture
// front - line number to start on
// direction - increasing or decreasing gradient
void slide (uint8 aperture, uint8 steps, uint8 front, uint8 direction)
{
    colour_t colour;
    colour.shade = WHITE>>3; // be careful with colours being <<3'd
    colour.direction = direction;

    uint16 pix = prepDisplay(1, 1, LCD_WIDTH, LCD_HEIGHT);

    // For determining where to change colour
    uint16 colourLength = aperture * (LCD_WIDTH/3) / steps;
    uint16 shiftPx = pix - colourLength;

    //TODO this needs to shift lines, not colours
    for (int i = 0; i < front; i++)
        shiftFront (&colour, steps);

    while (pix--)
    {
        write (DATA, colour.shade<<3);
        write (DATA, colour.shade<<3);
        write (DATA, colour.shade<<3);

        if (pix == shiftPx) // shifts colour at each row
        {
            shiftFront (&colour, steps);
            shiftPx -= colourLength;
        }
    }
}

void drawWaves (uint8 wavelength, uint8 wavefront, uint8 direction)
{
    // Legacy support ;)
    slide (wavelength, 32, wavefront, direction);
}

void shiftFront (colour_t *colour, uint8 steps)
{
    if (colour->direction == rising) // white -> black
    {
        colour->shade++;
        if (colour->shade == steps)
            colour->direction = falling;
    }
    else // black -> white
    {
        colour->shade--;
        if (colour->shade == (WHITE >> 3))
            colour->direction = rising;
    }
}

