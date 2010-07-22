/** @file   spi.h
    @author Michael Hayes
    @date   30 July 2007
    @brief  Routines for interfacing to the SPI bus.
*/

#ifndef SPI_H
#define SPI_H

#include "config.h"


typedef uint8_t spi_channel_t;

typedef uint16_t spi_clock_divisor_t;


enum {SPI_CHANNEL0 = 0, SPI_CHANNEL1, SPI_CHANNEL2, SPI_CHANNEL3};


/* SPI Mode Settings.  */
typedef enum {SPI_MODE_0 = 0,
              SPI_MODE_1 = 1,
              SPI_MODE_2 = 2,
              SPI_MODE_3 = 3
} spi_mode_t;


/* Data order settings.  */
typedef enum {SPI_DATA_MSB_FIRST = 0,
              SPI_DATA_LSB_FIRST = 1
} spi_data_order_t;


/* Macros.  */
#ifdef HOSTED
#define SPI_READY_P() (HOSTED || (AT91C_BASE_SPI->SPI_SR & AT91C_SPI_RDRF))
#else
#define SPI_READY_P() (AT91C_BASE_SPI->SPI_SR & AT91C_SPI_RDRF)
#endif

#define SPI_TXEMPTY_P() (AT91C_BASE_SPI->SPI_SR & AT91C_SPI_TXEMPTY)

#define SPI_CHANNEL_MASK(channel) (0x0f ^ BIT (channel))


/* Function Prototypes.  */

/* spi_init() will initialise the SPI port to the following settings:
   SPI Mode 0
   SPI Master
   Clock speed of system clock / 128
   Data order of MSB first
   SPI interrupts disabled
   SPI enabled
   NCPSx pins set to general purpose outputs
   These settings can then be altered as required using the provided functions.  
*/
extern void
spi_init (void);


extern void
spi_shutdown (void);


/** Enable the chip select; this does not drive it. 
    SPI_CSX_BIT needs to be defined to use channel X, X = 0..3
    SPI_CHANNEL0_CS_BIT 11 
    SPI_CHANNEL1_CS_BIT 9 or 31
    SPI_CHANNEL2_CS_BIT 10 or 30
    SPI_CHANNEL3_CS_BIT 3, 5, or 22  */
extern bool
spi_cs_enable (void);


/** Disable the chip select; this does not drive it.  */
extern bool
spi_cs_disable (void);


/* Return non-zero if there is a character ready to be read.  */
extern bool
spi_read_ready_p (void); 


/* Read character from SPI.  This blocks if nothing
   is available to read.  It sends a dummy word 0.  */
extern uint8_t
spi_getc (void); 


/* Return non-zero if a character can be written without blocking.  */
extern bool
spi_write_ready_p (void); 


/* Write character to SPI.  Ignore received character.  */
extern void 
spi_putc (char ch);


/* Write character to SPI.  This returns the character just read.  */
extern uint8_t
spi_xferc (char ch);


/* Write string to SPI.  */
extern void 
spi_puts (const char *str);


extern void
spi_bits_set (uint8_t bits);


extern void
spi_mode_set (spi_mode_t spi_mode);


extern
void spi_multichannel_select (void);


extern
void spi_multichannel_deselect (void);


extern void
spi_channel_select (spi_channel_t channel);


extern void
spi_channel_deselect (spi_channel_t channel);


/** Set the delay (in clocks) before the clock starts.  */
extern void
spi_clock_delay_set (uint16_t delay);


/** Set the delay (in clocks * 32) before starting a transmission on
    same SPI channel.  The default is 0.  */
extern void
spi_delay_set (uint16_t delay);


/* This cannot be set.  */
#define spi_data_order_set(data_order)


extern void
spi_divisor_set (spi_clock_divisor_t clock_divisor);


extern
uint16_t spi_get16 (void);


extern void
spi_put16 (uint16_t data);


/* Write character to SPI, return received data.  */
extern uint16_t
spi_xfer16 (uint16_t data);


extern
uint32_t spi_get32 (void);


extern void
spi_put32 (uint32_t data);


/* Write character to SPI, return received data.  */
extern uint32_t
spi_xfer32 (uint32_t data);



#endif
