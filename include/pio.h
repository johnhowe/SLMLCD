/*
 * pio.h
 *
 *  Spatial Light Modulator
 *      John Howe	2010
 */

enum { WAVES, NOISE };

typedef AT91S_PIO *pio_port_t;
typedef uint32 pio_mask_t;

typedef struct 
{
    pio_port_t port;
    pio_mask_t mask;
} pio_t;

/* Read position of switch */
uint8 readSwitch(void);

/* Set output pin high */
static inline pio_output_high (pio_t pio);

/* Set output pin low */
static inline pio_output_low (pio_t pio);

/* Configure port as output */
void pio_init_output (pio_t pio);

/* Configure port as input */
void pio_init_input (pio_t pio);

/* Set input port pullup */
void pio_init_set_pullup (pio_t pio);

/* Disable input port pullup */
void pio_init_disable_pullup (pio_t pio);

