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
/// \dir "Basic PWM Project"
///
/// !!!Purpose
///
/// This example demonstrates a simple configuration of two PWM channels to generate
/// variable duty cycle signals. This will cause one or more LEDs the evaluation kit to
/// glow repeatedly.
///
/// !!!See
/// - pwmc: Pulse width modulation controller driver
///
/// !!!Requirements
///
/// This package can be used with all Atmel evaluation kits that have PWMC
/// interface, the package runs at SDRAM or SRAM.
///
/// !!!Description
///
/// Two PWM channels (channel #1 and channel #2) are configured to generate
/// a 100kHz PWM signal. On channel #1, the signal is configured as left-aligned.
/// On channel #2, the signal is center-aligned and the polarity is inverted.
///
/// On most Atmel evaluation kits, PWM signals for channels #1 and #2 are connected
/// to two LEDs on the board. Since the duty cycle of the PWM signals varies continuously,
/// the two LEDs will alternate between their minimum and maximum intensity. Note that
/// on some boards, only one LED will be connected.
///
/// !!!Usage
///
/// -# Build the program and download it inside the evaluation board. Please refer to the
/// <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6132.pdf">
/// SAM-BA User Guide</a>, the
/// <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6132.pdf">
/// GNU-Based Software Development</a> application note or to the
/// <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6132.pdf">
/// IAR EWARM User Guide</a>, depending on your chosen solution.
/// -# Optionally, on the computer, open the DBGU port with a terminal application
///    (e.g. HyperTerminal on Microsoft Windows) with these settings:
///   - 115200 bauds
///   - 8 bits of data
///   - No parity
///   - 1 stop bit
///   - No flow control
/// -# Start the application.
/// -# Depending on the board being used, either one or two LEDs will start glowing.
/// If two LEDs are glowing, their states will be inverted (since channel #2
/// uses a reversed polarity).
///
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \unit
///
/// !Purpose
///
/// This file contains all the specific code for the basic-pwm-project
///
/// !Contents
/// The code can be roughly broken down as follows:
///    - Interrupt handler for the PWM controller
///    - The main function, which implements the program behavior
///       - Configure PWM clock
///       - Configure PWM channel #1 and channel #2 to generate a 100kHz PWM signal
///       - Enalbe PWM interrupt on channel #1
///       - Enable channel #1 and channel #2
///
/// Please refer to the list of functions in the #Overview# tab of this unit
/// for more detailed information.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <pio/pio.h>
#include <aic/aic.h>
#include <dbgu/dbgu.h>
#include <pwmc/pwmc.h>
#include <utility/trace.h>

#include <stdio.h>

//------------------------------------------------------------------------------
//         Local definitions
//------------------------------------------------------------------------------

/// PWM frequency in Hz.
#define PWM_FREQUENCY               20000

/// Maximum duty cycle value.
#define MAX_DUTY_CYCLE              50

/// Minimum duty cycle value (cannot be 0 or 1 for the SAM7S, c.f. errata)
#if defined(at91sam7s16) || defined(at91sam7s161) || defined(at91sam7s32) \
    || defined(at91sam7s321) || defined(at91sam7s64) || defined(at91sam7s128) \
    || defined(at91sam7s256) || defined(at91sam7s512) || defined(at91sam7a3)

    #define MIN_DUTY_CYCLE          2
#else

    #define MIN_DUTY_CYCLE          0
#endif

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

/// Pio pins to configure.
static const Pin pins[] = {
    PINS_DBGU,
    PIN_PWM_LED0,
    PIN_PWM_LED1
};

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Wait time in ms
//------------------------------------------------------------------------------
void UTIL_Loop(unsigned int loop)
{
    while(loop--);	
}


void UTIL_WaitTimeInMs(unsigned int mck, unsigned int time_ms)
{
    register unsigned int i = 0;
    i = (mck / 1000) * time_ms;
    i = i / 3;
    UTIL_Loop(i);
}

//------------------------------------------------------------------------------
/// Wait time in us
//------------------------------------------------------------------------------
void UTIL_WaitTimeInUs(unsigned int mck, unsigned int time_us)
{
    volatile unsigned int i = 0;
    i = (mck / 1000000) * time_us;
    i = i / 3;
    UTIL_Loop(i);
}

//------------------------------------------------------------------------------
/// Interrupt handler for the PWM controller. Counts the number of periods and
/// updates the duty cycle after a given number.
//------------------------------------------------------------------------------
static void ISR_Pwmc(void)
{
    static unsigned int count = 0;
    static unsigned int duty = MIN_DUTY_CYCLE;
    static unsigned char fadeIn = 1;

    // Interrupt on channel #1
    if ((AT91C_BASE_PWMC->PWMC_ISR & AT91C_PWMC_CHID1) == AT91C_PWMC_CHID1) {

        count++;

        // Fade in/out
        if (count == (PWM_FREQUENCY / (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE))) {

            // Fade in
            if (fadeIn) {

                duty++;
                if (duty == MAX_DUTY_CYCLE) {

                    fadeIn = 0;
                }
            }
            // Fade out
            else {

                duty--;
                if (duty == MIN_DUTY_CYCLE) {

                    fadeIn = 1;
                }
            }

            // Set new duty cycle
            count = 0;
            PWMC_SetDutyCycle(CHANNEL_PWM_LED0, duty);
            PWMC_SetDutyCycle(CHANNEL_PWM_LED1, duty);
        }
    }
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Outputs a PWM on LED1 & LED2 to makes it fade in and out.
//------------------------------------------------------------------------------
int main(void)
{
    PIO_Configure(pins, PIO_LISTSIZE(pins));
    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);
    printf("-- Basic PWMC Project %s --\n\r", SOFTPACK_VERSION);
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

    UTIL_WaitTimeInMs(BOARD_MCK, 1000);
    UTIL_WaitTimeInUs(BOARD_MCK, 1000);

    // Enable PWMC peripheral clock
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_PWMC;

    // Settings:
    // - 100kHz PWM period (PWM_FREQUENCY)
    // - 1s rise/fall time for the LED intensity

    // Set clock A to run at 100kHz * MAX_DUTY_CYCLE (clock B is not used)
    PWMC_ConfigureClocks(PWM_FREQUENCY * MAX_DUTY_CYCLE, 0, BOARD_MCK);

    // Configure PWMC channel for LED0 (left-aligned)
    PWMC_ConfigureChannel(CHANNEL_PWM_LED0, AT91C_PWMC_CPRE_MCKA, 0, 0);
    PWMC_SetPeriod(CHANNEL_PWM_LED0, MAX_DUTY_CYCLE);
    PWMC_SetDutyCycle(CHANNEL_PWM_LED0, MIN_DUTY_CYCLE);

    // Configure PWMC channel for LED1 (center-aligned, inverted polarity)
    PWMC_ConfigureChannel(CHANNEL_PWM_LED1, AT91C_PWMC_CPRE_MCKA, AT91C_PWMC_CALG, AT91C_PWMC_CPOL);
    PWMC_SetPeriod(CHANNEL_PWM_LED1, MAX_DUTY_CYCLE);
    PWMC_SetDutyCycle(CHANNEL_PWM_LED1, MIN_DUTY_CYCLE);

    // Configure interrupt on channel #1
    AIC_ConfigureIT(AT91C_ID_PWMC, 0, ISR_Pwmc);
    AIC_EnableIT(AT91C_ID_PWMC);
    PWMC_EnableChannelIt(CHANNEL_PWM_LED0);

    // Enable channel #1 and #2
    PWMC_EnableChannel(CHANNEL_PWM_LED0);
    PWMC_EnableChannel(CHANNEL_PWM_LED1);

    // Infinite loop
    while (1);
}

