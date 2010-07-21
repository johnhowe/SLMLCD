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
/// \dir "Getting Started with AT91SAM Microcontrollers"
///
/// !!!Purpose
///
/// The Getting Started project will help new users get familiar with Atmel's
/// AT91 family of microcontrollers. This basic application shows the startup
/// sequence of a chip and how to use its core peripherals.
///
/// !!!Requirements
///
/// This package can be used with all Atmel evaluation kits.
///
/// !!!Description
///
/// The demonstration program makes two LEDs on the board blink at a fixed rate.
/// This rate is generated by using a timer for the first LED; the second one
/// uses a Wait function based on a 1 ms tick. The blinking can be stopped using
/// two buttons (one for each LED).
///
/// !!!Usage
///
/// -# Build the program and download it inside the evaluation board. Please
///    refer to the <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6224.pdf">SAM-BA User Guide</a>,
///    the <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">GNU-Based Software Development</a>
///    application note or to the <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">IAR EWARM User Guide</a>,
///    depending on your chosen solution.
/// -# On the computer, open and configure a terminal application
///    (e.g. HyperTerminal on Microsoft Windows) with these settings:
///   - 115200 bauds
///   - 8 bits of data
///   - No parity
///   - 1 stop bit
///   - No flow control
/// -# Start the application.
/// -# Two LEDs should start blinking on the board. In the terminal window, the
///    following text should appear (values depend on the board and chip used):
///    \code
///     -- Getting Started Project xxx --
///     -- AT91xxxxxx-xx
///     -- Compiled: xxx xx xxxx xx:xx:xx --
///    \endcode
/// -# Pressing button 1 should make the first LED stop & restart blinking; same
///    for button 2 with the second LED.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \unit
///
/// !Purpose
///
/// This file contains all the specific code for the getting-started-project.
///
/// !Contents
/// The code can be roughly broken down as follows:
///    - Configuration functions
///    - Interrupt handlers
///    - Utility functions (such as Wait())
///    - The main() function, which implements the program behavior
///
/// Please refer to the list of functions in the #Overview# tab of this unit
/// for more detailed information.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <pio/pio.h>
#include <pio/pio_it.h>
#include <pit/pit.h>
#include <aic/aic.h>
#include <tc/tc.h>
#include <utility/led.h>
#include <utility/trace.h>

#include <stdio.h>

//------------------------------------------------------------------------------
//         Local definitions
//------------------------------------------------------------------------------
#ifndef AT91C_ID_TC0
#if defined(AT91C_ID_TC012)
    #define AT91C_ID_TC0 AT91C_ID_TC012
#elif defined(AT91C_ID_TC)
    #define AT91C_ID_TC0 AT91C_ID_TC
#else
    #error Pb define ID_TC
#endif
#endif

/// Delay for pushbutton debouncing (in milliseconds).
#define DEBOUNCE_TIME       500

/// PIT period value in �seconds.
#define PIT_PERIOD          1000

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

 /// Pushbutton \#1 pin instance.
const Pin pinPB1 = PIN_PUSHBUTTON_1;

/// Pushbutton \#1 pin instance.
const Pin pinPB2 = PIN_PUSHBUTTON_2;

/// Indicates the current state (on or off) for each LED.
unsigned char pLedStates[2] = {1, 1};

/// Global timestamp in milliseconds since start of application.
volatile unsigned int timestamp = 0;

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Handler for PIT interrupt. Increments the timestamp counter.
//------------------------------------------------------------------------------
void ISR_Pit(void)
{
    unsigned int status;

    // Read the PIT status register
    status = PIT_GetStatus() & AT91C_PITC_PITS;
    if (status != 0) {

        // Read the PIVR to acknowledge interrupt and get number of ticks
        timestamp += (PIT_GetPIVR() >> 20);
    }
}

//------------------------------------------------------------------------------
/// Configure the periodic interval timer to generate an interrupt every
/// millisecond.
//------------------------------------------------------------------------------
void ConfigurePit(void)
{
    // Initialize the PIT to the desired frequency
    PIT_Init(PIT_PERIOD, BOARD_MCK / 1000000);

    // Configure interrupt on PIT
    AIC_DisableIT(AT91C_ID_SYS);
    AIC_ConfigureIT(AT91C_ID_SYS, AT91C_AIC_PRIOR_LOWEST, ISR_Pit);
    AIC_EnableIT(AT91C_ID_SYS);
    PIT_EnableIT();

    // Enable the pit
    PIT_Enable();
}

//------------------------------------------------------------------------------
/// Interrupt handler for pushbutton\#1. Starts or stops LED\#1.
//------------------------------------------------------------------------------
void ISR_Bp1(void)
{
    static unsigned int lastPress = 0;

    // Check if the button has been pressed
    if (!PIO_Get(&pinPB1)) {

        // Simple debounce method: limit push frequency to 1/DEBOUNCE_TIME
        // (i.e. at least DEBOUNCE_TIME ms between each push)
        if ((timestamp - lastPress) > DEBOUNCE_TIME) {

            lastPress = timestamp;

            // Toggle LED state
            pLedStates[0] = !pLedStates[0];
            if (!pLedStates[0]) {

                LED_Clear(0);
            }
        }
    }
}

//------------------------------------------------------------------------------
/// Interrupt handler for pushbutton\#2. Starts or stops LED\#2 and TC0.
//------------------------------------------------------------------------------
void ISR_Bp2(void)
{
    static unsigned int lastPress = 0;

    // Check if the button has been pressed
    if (!PIO_Get(&pinPB2)) {

        // Simple debounce method: limit push frequency to 1/DEBOUNCE_TIME
        // (i.e. at least DEBOUNCE_TIME ms between each push)
        if ((timestamp - lastPress) > DEBOUNCE_TIME) {

            lastPress = timestamp;

            // Disable LED#2 and TC0 if there were enabled
            if (pLedStates[1]) {

                pLedStates[1] = 0;
                LED_Clear(1);
                AT91C_BASE_TC0->TC_CCR = AT91C_TC_CLKDIS;
            }   
            // Enable LED#2 and TC0 if there were disabled
            else {
                
                pLedStates[1] = 1;
                LED_Set(1);
                AT91C_BASE_TC0->TC_CCR = AT91C_TC_CLKEN | AT91C_TC_SWTRG;
            }
        }
    }
}

//------------------------------------------------------------------------------
/// Configures the pushbuttons to generate interrupts when pressed.
//------------------------------------------------------------------------------
void ConfigureButtons(void)
{
#if defined(at91sam7lek)
    const Pin pinCol0 = PIN_KEYBOARD_COL0;
    PIO_Configure(&pinCol0, 1);
#endif

#if defined(at91cap9dk)
    const Pin pinRow0 = PIN_KEYBOARD_ROW0;
    PIO_Configure(&pinRow0, 1);
#endif

    // Configure pios
    PIO_Configure(&pinPB1, 1);
    PIO_Configure(&pinPB2, 1);

    // Initialize interrupts
    PIO_InitializeInterrupts(AT91C_AIC_PRIOR_LOWEST);
    PIO_ConfigureIt(&pinPB1, (void (*)(const Pin *)) ISR_Bp1);
    PIO_ConfigureIt(&pinPB2, (void (*)(const Pin *)) ISR_Bp2);
    PIO_EnableIt(&pinPB1);
    PIO_EnableIt(&pinPB2);
}

//------------------------------------------------------------------------------
/// Configures LEDs \#1 and \#2 (cleared by default).
//------------------------------------------------------------------------------
void ConfigureLeds(void)
{
    LED_Configure(0);
    LED_Configure(1);
}

//------------------------------------------------------------------------------
/// Interrupt handler for TC0 interrupt. Toggles the state of LED\#2.
//------------------------------------------------------------------------------
void ISR_Tc0(void)
{
    // Clear status bit to acknowledge interrupt
    AT91C_BASE_TC0->TC_SR;

    // Toggle LED state
    LED_Toggle(1);
    printf("2 ");
}

//------------------------------------------------------------------------------
/// Configure Timer Counter 0 to generate an interrupt every 250ms.
//------------------------------------------------------------------------------
void ConfigureTc(void)
{
    unsigned int div;
    unsigned int tcclks;

    // Enable peripheral clock
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_TC0;

    // Configure TC for a 4Hz frequency and trigger on RC compare
    TC_FindMckDivisor(4, BOARD_MCK, &div, &tcclks);
    TC_Configure(AT91C_BASE_TC0, tcclks | AT91C_TC_CPCTRG);
    AT91C_BASE_TC0->TC_RC = (BOARD_MCK / div) / 4; // timerFreq / desiredFreq

    // Configure and enable interrupt on RC compare
    AIC_ConfigureIT(AT91C_ID_TC0, AT91C_AIC_PRIOR_LOWEST, ISR_Tc0);
    AT91C_BASE_TC0->TC_IER = AT91C_TC_CPCS;
    AIC_EnableIT(AT91C_ID_TC0);

    // Start the counter if LED is enabled.
    if (pLedStates[1]) {

        TC_Start(AT91C_BASE_TC0);
    }
}

//------------------------------------------------------------------------------
/// Waits for the given number of milliseconds (using the timestamp generated
/// by the PIT).
/// \param delay  Delay to wait for, in milliseconds.
//------------------------------------------------------------------------------
void Wait(unsigned long delay)
{
    volatile unsigned int start = timestamp;
    unsigned int elapsed;
    do {
        elapsed = timestamp;
        elapsed -= start;
    }
    while (elapsed < delay);
}

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Application entry point. Configures the DBGU, PIT, TC0, LEDs and buttons
/// and makes LED\#1 blink in its infinite loop, using the Wait function.
/// \return Unused (ANSI-C compatibility).
//------------------------------------------------------------------------------
int main(void)
{
    // DBGU configuration
    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);
    printf("-- Getting Started Project %s --\n\r", SOFTPACK_VERSION);
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
         
    // Configuration
    ConfigurePit();
    ConfigureTc();
    ConfigureButtons();
    ConfigureLeds();
    
    // Main loop
    while (1) {

        // Wait for LED to be active
        while (!pLedStates[0]);
        
        // Toggle LED state if active
        if (pLedStates[0]) {

            LED_Toggle(0);
            printf("1 ");
        }

        // Wait for 500ms
        Wait(500);
    }
}

