/*
 * pio.h
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */

enum { WAVES, NOISE };

typedef unsigned long pio_t; 

/* Read position of switch */
uint8 readSwitch(void);

/* Set output pin high */
static inline pio_output_high (pio_t pio);

/* Set output pin low */
static inline pio_output_low (pio_t pio);
