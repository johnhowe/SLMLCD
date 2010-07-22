/** @file   spi.c
    @author Michael Hayes
    @date   30 July 2007
    @brief  Routines for interfacing to the SPI bus.
*/

#include "config.h"
#include "spi.h"
#include "bits.h"

/* The AT91 SPI peripheral can transmit either 8 or 16 bit data.  It
   has 4 separate chip select registers and can control 4 different
   types of SPI peripheral using the separate chip select registers.
   Each peripheral can have its own chip select that is automatically
   driven for each transfer.

   The AT91 SPI peripheral has been designed so that blocks of a data
   can be streamed using DMA to multiple devices on the bus (Variable
   Peripheral Selection).  It achieves this by using 32 bits to
   specify the 8 or 16 bit data plus a bit mask specifying which
   peripheral to write to.

   There are 4 control status registers (CSRs); one associated with
   each of the four SPI chip select (CS) signals.  These configure the
   number of bits per transfer and the CS timing for each of the 4
   channels.  The SPI controller choses one of these 4 CSRs on the
   basis of the channel select mask in the master register (fixed
   peripheral mode) or in the data (variable peripheral mode).  Now
   this is all fine and dandy if we have 4 SPI devices.  What if we
   want more?  Well one option is to decode the 4 CS signals to
   provide 15 channels; with four per group.  This requires external
   hardware so is not much use.  The alternative is to bit bash
   additional output ports.  To do this we flog one of the 4 SPI
   channels (SPI_CHANNEL_DEFAULT) and to disable its CS pin.

   Simpler SPI peripherals usually only support 8 bit transfers and do not
   automatically strobe the CS signals; maybe 1 but not multiple channels.


   Perhaps could add the following functions:
     spi_write (channel, buffer, size, flags);
     spi_read (channel, buffer, size, flags);
     spi_transfer (channel, txbuffer, rxbuffer, size, flags);
*/

/* Define the default channel to use for bit-bashed SPI channels.  */
#ifndef SPI_CHANNEL_DEFAULT
#define SPI_CHANNEL_DEFAULT SPI_CHANNEL0
#endif

static uint8_t spi_channel = SPI_CHANNEL_DEFAULT;
static uint8_t spi_init_count = 0;


#ifndef HOSTED
#define HOSTED 0
#endif


/* Bit masks for the SPI mode settings.  */
enum {SPI_NCPHA_MASK = 0x02, 
      SPI_CPOL_MASK = 0x01};


/* Macros.  */


/* Read SPI and then send new data.  Blocks while the new data is
   being sent by the spi.  */
#define SPI_XFER(txdata, rxdata)                                       \
    do                                                                  \
    {                                                                   \
        AT91S_SPI *pSPI = AT91C_BASE_SPI;                               \
                                                                        \
        /* Write data to TDR.  */                                       \
        pSPI->SPI_TDR = (txdata);                                       \
                                                                        \
        /* Wait until spi port finishes transmitting/receiving.  */     \
        while (!SPI_READY_P())                                          \
            continue;                                                   \
                                                                        \
        /* Read new data from RDR (this clears RDRF).  */               \
        (rxdata) = pSPI->SPI_RDR;                                       \
                                                                        \
    } while (0)


static inline uint32_t
spi_channel_csr_get (spi_channel_t channel)
{
    AT91S_SPI *pSPI = AT91C_BASE_SPI;

    return pSPI->SPI_CSR[channel];
}


static inline void
spi_channel_csr_set (spi_channel_t channel, uint32_t csr)
{
    AT91S_SPI *pSPI = AT91C_BASE_SPI;

    pSPI->SPI_CSR[channel] = csr;
}


/** Set the delay (in clocks * 32) before starting a transmission on
    same SPI channel.  The default is 0.  */
static void
spi_channel_delay_set (spi_channel_t channel, uint16_t delay)
{
    uint32_t csr;

    csr = spi_channel_csr_get (channel);

    /* Set the DLYBCT (delay between consecutive transfers).  */
    BITS_INSERT (csr, delay, 24, 31);

    spi_channel_csr_set (channel, csr);
}


/** Set the delay (in clocks) before the clock starts.  */
static void
spi_channel_clock_delay_set (spi_channel_t channel, uint16_t delay)
{
    uint32_t csr;

    csr = spi_channel_csr_get (channel);

    /* Set the DLYBS (delay before SPCK).  */
    BITS_INSERT (csr, delay, 16, 23);

    spi_channel_csr_set (channel, csr);
}


/** The minimum divisor value is 1, this gives the maximum rate of MCK.  */
static void
spi_channel_divisor_set (spi_channel_t channel,
                         spi_clock_divisor_t clock_divisor)
{
    uint32_t csr;

    csr = spi_channel_csr_get (channel);

    BITS_INSERT (csr, clock_divisor, 8, 15);

    spi_channel_csr_set (channel, csr);
}


/* Set number of bits in transfer 8--16.  */
static void
spi_channel_bits_set (spi_channel_t channel, uint8_t bits)
{
    uint32_t csr;

    csr = spi_channel_csr_get (channel);

    BITS_INSERT (csr, bits - 8, 4, 7);

    spi_channel_csr_set (channel, csr);
}


static void
spi_channel_mode_set (spi_channel_t channel, spi_mode_t mode)
{
    uint32_t csr;

    csr = spi_channel_csr_get (channel);

    csr &= ~(SPI_CPOL_MASK | SPI_NCPHA_MASK);

    switch (mode)
    {
    case SPI_MODE_0:
        /* CPOL = 0, NCPHA = 1.  */
        csr |= SPI_NCPHA_MASK;
        break;

    case SPI_MODE_1:
        /* CPOL = 0, NCPHA = 0.  */
        break;

    case SPI_MODE_2:
        /* CPOL = 1, NCPHA = 1.  */
        csr |= SPI_CPOL_MASK;
        csr |= SPI_NCPHA_MASK;
        break;

    case SPI_MODE_3:
        /* CPOL = 1, NCPHA = 0.  */
        csr |= SPI_CPOL_MASK;
        break;
    }

    spi_channel_csr_set (channel, csr);
}


static bool
spi_channel_cs_enable (spi_channel_t channel)
{
    switch (channel)
    {
#ifdef SPI_CHANNEL0_CS_BIT
    case 0:
#if SPI_CHANNEL0_CS_BIT == 11
        /* There is no choice for the NPCS0.  */
        *AT91C_PIOA_ASR = AT91C_PA11_NPCS0;
        *AT91C_PIOA_PDR = AT91C_PA11_NPCS0;
#endif
        break;
#endif

#ifdef SPI_CHANNEL1_CS_BIT
    case 1:
        /* Can't use AT91C_PA31_NPCS1 in condition since has bloody cast
           in definition.  */
#if SPI_CHANNEL1_CS_BIT == 31
        *AT91C_PIOA_ASR = AT91C_PA31_NPCS1;
        *AT91C_PIOA_PDR = AT91C_PA31_NPCS1;
#elif SPI_CHANNEL1_CS_BIT == 9
        *AT91C_PIOA_BSR = AT91C_PA9_NPCS1;
        *AT91C_PIOA_PDR = AT91C_PA9_NPCS1;
#endif
        break;
#endif


#ifdef SPI_CHANNEL2_CS_BIT
    case 2:
#if SPI_CHANNEL2_CS_BIT == 10
        *AT91C_PIOA_BSR = AT91C_PA10_NPCS2;
        *AT91C_PIOA_PDR = AT91C_PA10_NPCS2;
#elif SPI_CHANNEL2_CS_BIT == 30
        *AT91C_PIOA_BSR = AT91C_PA30_NPCS2;
        *AT91C_PIOA_PDR = AT91C_PA30_NPCS2;
#endif
        break;
#endif


#ifdef SPI_CHANNEL3_CS_BIT
    case 3:
#if SPI_CHANNEL3_CS_BIT == 3
        *AT91C_PIOA_BSR = AT91C_PA3_NPCS3;
        *AT91C_PIOA_PDR = AT91C_PA3_NPCS3;
#elif SPI_CHANNEL3_CS_BIT == 5
        *AT91C_PIOA_BSR = AT91C_PA5_NPCS3;
        *AT91C_PIOA_PDR = AT91C_PA5_NPCS3;
#elif SPI_CHANNEL3_CS_BIT == 22
        *AT91C_PIOA_BSR = AT91C_PA22_NPCS3;
        *AT91C_PIOA_PDR = AT91C_PA22_NPCS3;
#endif
        break;
#endif

    default:
        return 0;
    }
    return 1;
}


static bool
spi_channel_cs_disable (spi_channel_t channel)
{
    switch (channel)
    {
    case 0:
        *AT91C_PIOA_PER = AT91C_PA11_NPCS0;
        break;

#ifdef SPI_CHANNEL1_CS_BIT
    case 1:
#if SPI_CHANNEL1_CS_BIT == 31
        *AT91C_PIOA_PER = AT91C_PA31_NPCS1;
#elif SPI_CHANNEL1_CS_BIT == 9
        *AT91C_PIOA_PER = AT91C_PA9_NPCS1;
#endif
        break;
#endif


#ifdef SPI_CHANNEL2_CS_BIT
    case 2:
#if SPI_CHANNEL2_CS_BIT == 10
        *AT91C_PIOA_PER = AT91C_PA10_NPCS2;
#elif SPI_CHANNEL2_CS_BIT == 30
        *AT91C_PIOA_PER = AT91C_PA30_NPCS2;
#endif
        break;
#endif


#ifdef SPI_CHANNEL3_CS_BIT
    case 3:
#if SPI_CHANNEL3_CS_BIT == 3
        *AT91C_PIOA_PER = AT91C_PA3_NPCS3;
#elif SPI_CHANNEL3_CS_BIT == 5
        *AT91C_PIOA_PER = AT91C_PA5_NPCS3;
#elif SPI_CHANNEL3_CS_BIT == 22
        *AT91C_PIOA_PER = AT91C_PA22_NPCS3;
#endif
        break;
#endif

    default:
        return 0;
    }
    return 1;
}


/** Set the delay (in clocks * 32) before starting a transmission on
    same SPI channel.  The default is 0.  */
void
spi_delay_set (uint16_t clock_divisor)
{
    spi_channel_delay_set (spi_channel, clock_divisor);
}


void
spi_divisor_set (spi_clock_divisor_t clock_divisor)
{
    spi_channel_divisor_set (spi_channel, clock_divisor);
}


/** Set the delay (in clocks) before the clock starts.  */
void
spi_clock_delay_set (uint16_t delay)
{
    spi_channel_clock_delay_set (spi_channel, delay);
}


static inline void
spi_csr_set (uint32_t csr)
{
    spi_channel_csr_set (spi_channel, csr);
}


static inline uint32_t
spi_csr_get (void)
{
    return spi_channel_csr_get (spi_channel);
}


void
spi_bits_set (uint8_t bits)
{
    spi_channel_bits_set (spi_channel, bits);
}



/* This performs a software reset.  It puts the peripheral in slave mode.  */
void
spi_reset (void)
{
    AT91S_SPI *pSPI = AT91C_BASE_SPI;

    pSPI->SPI_CR = AT91C_SPI_SWRST;
}


void
spi_enable (void)
{
    AT91S_SPI *pSPI = AT91C_BASE_SPI;

    pSPI->SPI_CR = AT91C_SPI_SPIEN;
}


void 
spi_disable (void)
{
    AT91S_SPI *pSPI = AT91C_BASE_SPI;

    pSPI->SPI_CR = AT91C_SPI_SPIDIS;
}


void
spi_mode_set (spi_mode_t mode)
{
    spi_channel_mode_set (spi_channel, mode);
}


/** Enable variable peripheral select.  */
void
spi_multichannel_select (void)
{
    AT91S_SPI *pSPI = AT91C_BASE_SPI;

    pSPI->SPI_MR |= AT91C_SPI_PS_VARIABLE;
}


/** Enable fixed peripheral select and switch to default channel.  */
void
spi_multichannel_deselect (void)
{
    spi_channel_select (SPI_CHANNEL_DEFAULT);
}


void
spi_channel_select (spi_channel_t channel)
{
    AT91S_SPI *pSPI = AT91C_BASE_SPI;

    pSPI->SPI_MR &= ~AT91C_SPI_PS_VARIABLE;

    BITS_INSERT (pSPI->SPI_MR, SPI_CHANNEL_MASK (channel), 16, 19);
    spi_channel = channel;
}


void
spi_channel_deselect (spi_channel_t channel __UNUSED__)
{
    /* Could check that channel being deselected is currently selected.  */
    spi_channel_select (SPI_CHANNEL_DEFAULT);
}


bool
spi_cs_enable (void)
{
    return spi_channel_cs_enable (spi_channel);
}


bool
spi_cs_disable (void)
{
    return spi_channel_cs_disable (spi_channel);
}


/** Initialise SPI for master mode.  */
void
spi_init (void)
{
    AT91S_SPI *pSPI = AT91C_BASE_SPI;

    spi_init_count++;

    /* Make this idempotent.  */
    if (spi_init_count != 1)
        return;

    /* Configure PIO for MISO, MOSI, SPCK, NPCS[3:0] (chip selects).
       There is a choice of which pins to use for some of these signals:
       MISO  PA12(A)
       MOSI  PA13(A)
       SPCK  PA14(A)
       NPCS0 PA11(A)
       NPCS1 PA9(B)  PA31(A)
       NPCS2 PA10(B) PA30(B)
       NPCS3 PA3(B)  PA5(B)  PA22(B)
       
       We need to make these user configurable somehow.  The main SPI
       signals are fixed but the chip selects have several options.
       Here we should keep things simple and expect the user to drive
       the chip selects.  This will limit performance but we could
       have a more swish driver at a later stage to augment this
       simple driver. 
       
       AT91C_PA11_NPCS0 (A)
       AT91C_PA31_NPCS1 (A)
       AT91C_PA9_NPCS1  (B)
       AT91C_PA10_NPCS2 (B)
       AT91C_PA30_NPCS2 (B)
       AT91C_PA3_NPCS3  (B)
       AT91C_PA5_NPCS3  (B)
       AT91C_PA22_NPCS3 (B)
    */

    *AT91C_PIOA_ASR = AT91C_PA13_MOSI | AT91C_PA12_MISO | AT91C_PA14_SPCK; 

    /* Disable pins as GPIO.  */
    *AT91C_PIOA_PDR = AT91C_PA13_MOSI | AT91C_PA12_MISO | AT91C_PA14_SPCK;

    /* Disable pullups.  */
    *AT91C_PIOA_PPUDR = AT91C_PA13_MOSI | AT91C_PA12_MISO | AT91C_PA14_SPCK;

    /* Enable SPI peripheral clock.  */
    AT91C_BASE_PMC->PMC_PCER = BIT (AT91C_ID_SPI);


    /* Reset the SPI (it is possible to reset the SPI even if disabled).  */
    spi_reset ();

    /* Set chip select register to defaults.  */
    spi_channel_select (SPI_CHANNEL_DEFAULT);

    spi_csr_set (0);

    spi_mode_set (SPI_MODE_0);
    spi_bits_set (8);
    spi_divisor_set (128);

    /* Desire PS = 0 (fixed peripheral select)
       PCSDEC = 0 (no decoding of chip selects)
       MSTR = 1 (master mode)
       MODFDIS = 1 (mode fault detection disabled)
       CSAAT = 0 (chip select rises after transmission)
    */

    pSPI->SPI_MR = AT91C_SPI_MSTR + AT91C_SPI_MODFDIS;

    spi_enable ();
}


void
spi_shutdown (void)
{
    if (!spi_init_count)
        return;

    spi_init_count--;

    if (spi_init_count)
        return;

    spi_disable ();

    /* Make SPI pins GPIO.  */
    *AT91C_PIOA_PER = AT91C_PA13_MOSI | AT91C_PA14_SPCK;

    /* Disable pullups (they should be disabled anyway).  */
    *AT91C_PIOA_PPUDR = AT91C_PA13_MOSI | AT91C_PA12_MISO | AT91C_PA14_SPCK;

    /* Force lines low to prevent powering devices.  */
    *AT91C_PIOA_CODR = AT91C_PA13_MOSI | AT91C_PA14_SPCK;

    /* Disable SPI peripheral clock.  */
    AT91C_BASE_PMC->PMC_PCDR = BIT (AT91C_ID_SPI);
}


/* Return non-zero if there is a character ready to be read.  */
bool
spi_read_ready_p (void)
{
#if HOSTED
    return 1;
#else
    return SPI_READY_P ();
#endif
}


/* Read character from SPI by sending a dummy word.  */
uint8_t spi_getc (void)
{
    uint8_t rxdata;

    SPI_XFER (0, rxdata);
    return rxdata;
}


/* Return non-zero if a character can be written without blocking.  */
bool
spi_write_ready_p (void)
{
    return SPI_READY_P ();
}


/* Write character to SPI, ignore received character.  */
void
spi_putc (char ch)
{
    uint8_t rxdata;

    SPI_XFER (ch, rxdata);
}


/* Write character to SPI, return received character.  */
uint8_t
spi_xferc (char ch)
{
    uint8_t rxdata;

    SPI_XFER (ch, rxdata);
    return rxdata;
}


/* Write string to SPI, ignoring received data.  */
void 
spi_puts (const char *str)
{
    uint8_t rxdata;

    while (*str)
        SPI_XFER (*str++, rxdata);
}


/* Read 16-bit word from SPI by sending a dummy word.  */
uint16_t spi_get16 (void)
{
    uint16_t rxdata;

    SPI_XFER (0, rxdata);
    return rxdata;
}


/* Write 16-bit word to SPI, ignore received character.
   Note only 16 LSBs are interpreted as data; the MSBs
   select the channel.  */
void
spi_put16 (uint16_t data)
{
    uint16_t rxdata;

    SPI_XFER (data, rxdata);
}


/* Write character to SPI, return received data.  */
uint16_t
spi_xfer16 (uint16_t data)
{
    uint16_t rxdata;

    SPI_XFER (data, rxdata);
    return rxdata;
}


/* Read 32-bit word from SPI by sending a dummy word.  */
uint32_t spi_get32 (void)
{
    uint32_t rxdata;

    SPI_XFER (0, rxdata);
    return rxdata;
}


/* Write 32-bit word to SPI, ignore received character.
   Note only 16 LSBs are interpreted as data; the MSBs
   select the channel.  */
void
spi_put32 (uint32_t data)
{
    uint32_t rxdata;

    SPI_XFER (data, rxdata);
}


/* Write character to SPI, return received data.  */
uint32_t
spi_xfer32 (uint32_t data)
{
    uint32_t rxdata;

    SPI_XFER (data, rxdata);
    return rxdata;
}
