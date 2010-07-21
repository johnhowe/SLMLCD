/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

//------------------------------------------------------------------------------
/// \dir "basic adc project"
///
/// !!!Purpose
///
/// This project demonstrates the ADC (Analog-to-Digital Converter).
///
/// !!!Requirements
///
/// The following evaluation kits are supported by this project:
/// - AT91SAM7A3-EK
/// - AT91SAM7L-EK
/// - AT91SAM7S-EK
/// - AT91SAM7SE-EK
/// - AT91SAM7X-EK
/// - AT91SAM7XC-EK
/// - AT91SAM9260-EK
/// - AT91SAM9G20-EK
/// - AT91SAM9XE-EK
/// - AT91CAP9-DK
/// - AT91CAP9-STK
///
/// !!!Description
///
/// After launching the program, the device will display the voltage on four
/// of his ADC pins. Somes boards have more than four accessible pins, so the 
/// software can be easily update for that.
///
/// !!!Usage
/// -# For AT91SAM7A3-EK board:
/// The measured pins are J6 pins 1 and 2, and J9 pins B15 and B16
///
/// -# For AT91SAM7L-EK board:
/// The measured pins are J205 pins 1, 3, 5 and 7
///
/// -# For AT91SAM7S-EK board:
/// The measured pins are J7, J8, J9 and J10
/// 
/// -# For AT91SAM7SE-EK board:
/// The measured pins are J17 pins 29, 30, 31 and 32
///
/// -# For AT91SAM7X-EK board:
/// The measured pins are J16 pins C29 and C30, and J26 pins 1 and 2
/// 
/// -# For AT91SAM7XC-EK board:
/// The measured pins are J16 pins C29 and C30, and J26 pins 1 and 2
///
/// -# For AT91SAM9260-EK board:
/// The measured pins are J24 pins 1, 2, 3 and 4
///
/// -# For AT91SAM9G20-EK board:
/// The measured pins are J24 pins 1, 2, 3 and 4
///
/// -# For AT91SAM9XE-EK board:
/// The measured pins are J24 pins 1, 2, 3 and 4
///
/// -# For AT91CAP9-DK board:
/// The ADC jumpers are on position 1 (J3)
///
/// -# For AT91CAP9-STK board:
/// The ADC jumpers are on position 3 (J53-3, J54-3, J55-3, J56-3)
///
/// -# Compile the application.
/// -# Connect the DBGU port of the evaluation board to the computer and open
/// it in a terminal.
///    - Settings: 115200 bauds, 8 bits, 1 stop bit, no parity, no flow control.
/// -# Download the program inside the evaluation board and run it. Please refer to
///    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6132.pdf">
///    the SAM-BA User Guide,
///    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
///    the GNU-Based Software Development</a> application note or to the
///    <a href="http://www.iar.se/website1/1.0.1.0/78/1/index.php?">
///    IAR EWARM User Guide</a>,
///    depending on your chosen solution.
/// -# Upon startup, the application will output the following line on the DBGU:
///    \code
///    -- Basic ADC Project xxx --
///    -- AT91xxxxxx-xx
///    -- Compiled: xxx xx xxxx xx:xx:xx --
///    -I- Press any key to perform a measurement on the ADC ...
///    \endcode
/// -# And then, after press a key:
///    \code
///    Channel 4 : 2332 mV
///    Channel 5 : 25 mV
///    Channel 6 : 1454 mV
///    Channel 7 : 1303 mV
///    \endcode
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <pio/pio.h>
#include <dbgu/dbgu.h>
#include <aic/aic.h>
#include <utility/trace.h>
#include <adc/adc.h>

#include <stdio.h>


#define BOARD_ADC_FREQ 5000000
#define ADC_VREF       3300  // 3.3 * 1000
//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

/// Pio pins to configure.
#ifdef PINS_ADC
static const Pin pinsADC[] = {PINS_ADC};
#endif

#if defined(at91sam7a3)
#define AT91C_ID_ADC AT91C_ID_ADC0
#define AT91C_BASE_ADC AT91C_BASE_ADC0
#endif

/// Indicates that the conversion is finished.
static volatile unsigned char conversionDone;

#if defined(at91sam7s16) || defined(at91sam7s161) || defined(at91sam7s32)\
    || defined(at91sam7s321) || defined(at91sam7s64) || defined(at91sam7s128)\
    || defined(at91sam7s256) || defined(at91sam7s512)
#define ADC_NUM_1  ADC_CHANNEL_0
#define ADC_NUM_2  ADC_CHANNEL_1
#define ADC_NUM_3  ADC_CHANNEL_4
#define ADC_NUM_4  ADC_CHANNEL_5
#endif
#if defined(at91sam7x128) || defined(at91sam7x256) || defined(at91sam7x512)\
   || defined(at91sam7xc128) || defined(at91sam7xc256) || defined(at91sam7xc512)
#define ADC_NUM_1  ADC_CHANNEL_4
#define ADC_NUM_2  ADC_CHANNEL_5
#define ADC_NUM_3  ADC_CHANNEL_6
#define ADC_NUM_4  ADC_CHANNEL_7
#endif
#if defined(at91sam7a3)\
    || defined(at91sam7l64) || defined(at91sam7l128)\
    || defined(at91sam9260)\
    || defined(at91sam9g20)\
    || defined(at91sam9rl64)\
    || defined(at91sam9xe128) || defined(at91sam9xe256) || defined(at91sam9xe512) \
    || defined(at91cap9)
#define ADC_NUM_1  ADC_CHANNEL_0
#define ADC_NUM_2  ADC_CHANNEL_1
#define ADC_NUM_3  ADC_CHANNEL_2
#define ADC_NUM_4  ADC_CHANNEL_3
#endif

#if defined(at91sam7se32) || defined(at91sam7se256) ||defined(at91sam7se512)
#define ADC_NUM_1  ADC_CHANNEL_4
#define ADC_NUM_2  ADC_CHANNEL_5
#define ADC_NUM_3  ADC_CHANNEL_6
#define ADC_NUM_4  ADC_CHANNEL_7
#endif

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Convert a digital value in milivolt
/// /param valueToconvert Value to convert in milivolt
//-----------------------------------------------------------------------------
static unsigned int ConvHex2mV( unsigned int valueToConvert )
{
    return( (ADC_VREF * valueToConvert)/0x3FF);
}

//------------------------------------------------------------------------------
/// Interrupt handler for the ADC. Signals that the conversion is finished by
/// setting a flag variable.
//------------------------------------------------------------------------------
static void ISR_Adc(void)
{
    unsigned int status;
    unsigned int id_channel;

    status = ADC_GetStatus(AT91C_BASE_ADC);
    TRACE_DEBUG("status =0x%X\n\r", status);
    //TRACE_DEBUG("adc_imr=0x%X\n\r", ADC_GetInterruptMaskStatus());

    for(id_channel=ADC_NUM_1;id_channel<=ADC_NUM_4;id_channel++) {

        if (ADC_IsChannelInterruptStatusSet(status, id_channel)) {

            TRACE_DEBUG("channel %d\n\r", id_channel);
            ADC_DisableIt(AT91C_BASE_ADC, id_channel);
            conversionDone |= 1<<id_channel;
        }
    }
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Performs measurements on ADC channel 0 and displays the result on the DBGU.
//------------------------------------------------------------------------------
int main(void)
{
    unsigned int id_channel;	

    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);
    printf("-- Basic ADC Project %s --\n\r", SOFTPACK_VERSION);
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

#ifdef PINS_ADC
    PIO_Configure(pinsADC, PIO_LISTSIZE(pinsADC));
#endif

    ADC_Initialize( AT91C_BASE_ADC,
                    AT91C_ID_ADC,
                    AT91C_ADC_TRGEN_DIS,
                    0,
                    AT91C_ADC_SLEEP_NORMAL_MODE,
                    AT91C_ADC_LOWRES_10_BIT,
                    BOARD_MCK,
                    BOARD_ADC_FREQ,
                    10,
                    1200);

    ADC_EnableChannel(AT91C_BASE_ADC, ADC_NUM_1);
    ADC_EnableChannel(AT91C_BASE_ADC, ADC_NUM_2);
    ADC_EnableChannel(AT91C_BASE_ADC, ADC_NUM_3);
    ADC_EnableChannel(AT91C_BASE_ADC, ADC_NUM_4);

    AIC_ConfigureIT(AT91C_ID_ADC, 0, ISR_Adc);
    AIC_EnableIT(AT91C_ID_ADC);

    printf("-I- Press any key to perform a measurement on the ADC ...\n\r");

    // Infinite loop
    while (1) {

        // Wait for user input
        DBGU_GetChar();

        conversionDone = 0;

        ADC_EnableIt(AT91C_BASE_ADC, ADC_NUM_1);
        ADC_EnableIt(AT91C_BASE_ADC, ADC_NUM_2);
        ADC_EnableIt(AT91C_BASE_ADC, ADC_NUM_3);
        ADC_EnableIt(AT91C_BASE_ADC, ADC_NUM_4);

        // Start measurement
        ADC_StartConversion(AT91C_BASE_ADC);

        while( conversionDone != ((1<<ADC_NUM_1)|(1<<ADC_NUM_2)|(1<<ADC_NUM_3)|(1<<ADC_NUM_4)) );

        for(id_channel=ADC_NUM_1;id_channel<=ADC_NUM_4;id_channel++) {

            printf("Channel %d : %d mV\n\r",
                id_channel,
                ConvHex2mV(ADC_GetConvertedData(AT91C_BASE_ADC, id_channel))
                );
        }

        printf("\n\r");
    }
}

