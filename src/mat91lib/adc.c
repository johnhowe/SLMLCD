/** @file   adc.c
    @author 
    @date   12 February 2008
    @brief  Analogue to digital converter routines for AT91SAM7 processors
*/

#include "adc.h"
#include "bits.h"

/* On reset the the PIO pins are configured as inputs with pullups.
   To make a PIO pin an ADC pin requires programming ADC_CHER.
   
   The ADC is 10 bit successive approximation so requires 10 ADC clock
   cycles plus some clock cycles for the sample/hold.  The ADC clock
   ranges from MCK/2 to MCK/128 depending on the prescale value.

   Each channel has its own channel data register ADC_CDR and an end
   of conversion (EOC) bit in the ADC status register ADC_SR.  When a
   conversion is finished the ADC_CDR is written as well as the last
   converted data register ADC_LCDR.

   The ADC peripheral is designed so that multiple channels can be
   enabled at once.  When it gets a trigger it samples each enabled
   channel in turn and writes to the corresponding ADC_CDR registers.
   It then waits for the next trigger.

   The minimum impedance (ohms) driving the ADC is given by:
   
   ZOUT <= (SHTIM - 470) x 10 in 8-bit resolution mode
   ZOUT <= (SHTIM - 589) x 7.69 in 10-bit resolution mode
   
   where SHTIM is the sample/hold time in ns.
*/


#define ADC_8BIT_CLOCK_MAX 8e6
#define ADC_10BIT_CLOCK_MAX 5e6
#define ADC_STARTUP_TIME_MIN 20e-6
#define ADC_SAMPLE_TIME_MIN 600e-9


#ifndef ADC_8BIT_CLOCK
#define ADC_8BIT_CLOCK ADC_8BIT_CLOCK_MAX
#endif


#ifndef ADC_10BIT_CLOCK
#define ADC_10BIT_CLOCK ADC_10BIT_CLOCK_MAX
#endif


#ifndef ADC_STARTUP_TIME
#define ADC_STARTUP_TIME ADC_STARTUP_TIME_MIN
#endif


#ifndef ADC_SAMPLE_TIME
#define ADC_SAMPLE_TIME ADC_SAMPLE_TIME_MIN
#endif


#define ADC_8BIT_PRESCALE ((uint8_t)(F_CPU / (2 * ADC_8BIT_CLOCK) + 0.5 - 1))
#define ADC_10BIT_PRESCALE ((uint8_t)(F_CPU / (2 * ADC_10BIT_CLOCK) + 0.5 - 1))


/* Determine actual ADC clock.  */
#define ADC_8BIT_CLOCK1 (F_CPU / ((ADC_8BIT_PRESCALE + 1) * 2))
#define ADC_10BIT_CLOCK1 (F_CPU / ((ADC_10BIT_PRESCALE + 1) * 2))

#define ADC_8BIT_STARTUP ((uint8_t)(ADC_STARTUP_TIME * ADC_8BIT_CLOCK1 / 8 + 0.5 - 1))
#define ADC_10BIT_STARTUP ((uint8_t)(ADC_STARTUP_TIME * ADC_10BIT_CLOCK1 / 8 +0.5 - 1))

#define ADC_8BIT_SHTIM ((uint8_t)(ADC_SAMPLE_TIME * ADC_8BIT_CLOCK1 + 0.5 - 1))
#define ADC_10BIT_SHTIM ((uint8_t)(ADC_SAMPLE_TIME * ADC_10BIT_CLOCK1 + 0.5 - 1))



/* Resets ADC.  */
static void
adc_reset (void)
{
    AT91C_BASE_ADC->ADC_CR = AT91C_ADC_SWRST;
}


/* Puts ADC into sleep mode.  */
/* Should wake up on next trigger.  */
void
adc_sleep (void)
{
    AT91C_BASE_ADC->ADC_MR |= AT91C_ADC_SLEEP;
}


/* Set ADC resolution (10 bits by default).  */
static bool
adc_resolution_set (uint8_t resolution)
{
    switch (resolution)
    {
        /* ADC clock has to be 5MHz in high resolution mode, a prescale of 4.  */
        case 10:

            AT91C_BASE_ADC->ADC_MR &= ~AT91C_ADC_LOWRES;

            /* ADC clock.  */
            BITS_INSERT (AT91C_BASE_ADC->ADC_MR, ADC_10BIT_PRESCALE, 8, 13);
            /* Startup time.  */
            BITS_INSERT (AT91C_BASE_ADC->ADC_MR, ADC_10BIT_STARTUP, 16, 20);
            /* Sample and hold time.  */
            BITS_INSERT (AT91C_BASE_ADC->ADC_MR, ADC_10BIT_SHTIM, 24, 27);
            break;

        /* ADC clock has to be 8MHz in low resolution mode, a prescale of 2.  */
        case 8:
            AT91C_BASE_ADC->ADC_MR |= AT91C_ADC_LOWRES;

            /* ADC clock.  */
            BITS_INSERT (AT91C_BASE_ADC->ADC_MR, ADC_8BIT_PRESCALE, 8, 13);
            /* Startup time.  */
            BITS_INSERT (AT91C_BASE_ADC->ADC_MR, ADC_8BIT_STARTUP, 16, 20);
            /* Sample and hold time.  */
            BITS_INSERT (AT91C_BASE_ADC->ADC_MR, ADC_8BIT_SHTIM, 24, 27);
            break;

        default:
            return 0;
            break;
    }
    return resolution;
}


static void
adc_start (void)
{
    AT91C_BASE_ADC->ADC_CR = AT91C_ADC_START;
}


/** Select ADC reference mode.  */
void 
adc_reference_select (adc_ref_mode_t mode __UNUSED__)
{
}


/** Initalises the ADC registers for polling operation.  */
void 
adc_init (uint8_t channels __UNUSED__)
{
    adc_sample_t dummy;

    adc_reset ();
    adc_resolution_set (10);
    // adc_sleep ();
    adc_read_wait (0, &dummy);
}


/** Starts a conversion in the ADC on the specified channel.  */
bool
adc_conversion_start (adc_channel_t channel)
{
    if (channel >= ADC_CHANNEL_NUM)
	return 0;

    AT91C_BASE_ADC->ADC_CHER = BIT (channel);

#if 0
    /* Check if conversion already in progress.  */
    if (!adc_ready_p ())
	return 0;
#endif

    /* Start conversion.  */
    adc_start ();
    return 1;
}


/** Returns true if a conversion has finished.  */
bool
adc_ready_p (void)
{
    return (AT91C_BASE_ADC->ADC_SR & AT91C_ADC_DRDY) != 0;
}


/** Returns 1 if valid sample read.  */
int8_t
adc_read (adc_sample_t *pvalue)
{
    if (!adc_ready_p ())
        return 0;

    *pvalue = AT91C_BASE_ADC->ADC_LCDR;
    
    /* Disable channel.  */
    AT91C_BASE_ADC->ADC_CHDR = ~0;
    return 1;
}


/** Start conversion on selected channel, wait until conversion finished.  */
int8_t
adc_read_wait (adc_channel_t channel, adc_sample_t *pvalue)
{
    if (!adc_conversion_start (channel))
        return 0;

    /* Should have timeout.  */
    while (!adc_ready_p ())
        continue;

    return adc_read (pvalue);
}


/** Halts any currently running conversion.  */
void 
adc_stop (void)
{
}


/** Disables the ADC from doing anything.  */
void
adc_disable (void)
{
}
