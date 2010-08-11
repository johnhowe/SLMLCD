/*
 * pio.c
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */

/* Read position of switch */
uint8 readSwitch(void)
{
    // TODO: add switch and set this up
    return WAVES;
}

/* Set output pin high */
static inline pio_output_high (pio_t pio)
{
    pio.port -> PIO_SODR = pio;
}

/* Set output pin low */
static inline pio_output_low (pio_t pio)
{
    pio.port -> PIO_CODR = pio;
}

/* Configure port as output */
void pio_init_output (pio_t pio)
{
    pio.port -> PIO_SODR = pio.mask;
    pio.port -> PIO_PER = pio.mask;
}

/* Configure port as input */
void pio_init_input (pio_t pio)
{
    pio.port -> PIO_ODR = pio.mask;
    pio.port -> PIO_PER = pio.mask;
    pio.port -> PIO_PPUDR = pio.mask;
}

/* Set input port pullup */
void pio_init_set_pullup (pio_t pio)
{
    pio.port -> PIO_PPUER = pio.mask;
}

/* Disable input port pullup */
void pio_init_disable_pullup (pio_t pio)
{
    pio.port -> PIO_PPUDR = poo.mask;
}

