/*
 * pio.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */


/* Read position of switch */
uint8 readSwitch(void)
{
    return WAVES;
}

/* Set output pin high */
static inline pio_output_high (pio_t pio)
{
    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
    pPIO -> PIO_SODR = pio;
}

/* Set output pin low */
static inline pio_output_low (pio_t pio)
{
    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
    pPIO -> PIO_CODR = pio;
}

