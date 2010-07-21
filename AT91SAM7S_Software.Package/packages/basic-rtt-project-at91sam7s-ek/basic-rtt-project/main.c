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
 
//-----------------------------------------------------------------------------
/// \dir "Real Time Timer"
///
/// !!!Purpose
///
/// This example demonstrates the Real-Time Timer (RTT) provided on 
/// AT91 microcontrollers. It enables the user to set an alarm and watch 
/// it being triggered when the timer reaches the corresponding value. 
///
/// You can configure the RTT by following steps
/// - SetPrescaler the RTT to 1s (32768)
/// - Initialize the ISR routine which refesh it when 1s is counted down
/// - Enable the RTT Interrtup of the vector 
///
/// !See
/// - rtt: Real Timer Timer driver
/// - aic: Advanced Interrupt Controller driver 
///
///
/// !!!Description
///
/// When launched, this program displays a timer count and a menu on the DBGU, 
/// enabling the user to choose between several options: 
///
///
/// !!!Usage
///
/// -# Build the program and download it inside the evaluation board. Please
///    refer to the
///    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6224.pdf">
///    SAM-BA User Guide</a>, the
///    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
///    GNU-Based Software Development</a> application note or to the
///    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
///    IAR EWARM User Guide</a>, depending on your chosen solution.
/// -# On the computer, open and configure a terminal application
///    (e.g. HyperTerminal on Microsoft Windows) with these settings:
///   - 115200 bauds
///   - 8 bits of data
///   - No parity
///   - 1 stop bit
///   - No flow control
/// -# Start the application.
/// -# In the terminal window, the following text should appear:
///    \code
///     -- Basic RTT Project xxx --
///     -- AT91xxxxxx-xx
///     -- Compiled: xxx xx xxxx xx:xx:xx --
///     Time: 0
///     Menu:
///     r - Reset timer
///     s - Set alarm
///     Choice?
///    \endcode
///
/// The user can then choose any of the available options to perform the described action. 
///
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \unit
///
/// !Purpose
///
/// This file contains all the specific code for the
/// basic-rtt-project
///
/// !Contents
///
/// The code can be roughly broken down as follows:
///    - Configuration functions
///    - Interrupt handlers
///    - Callback functions
///    - The main function, which implements the program behavior
///
/// Please refer to the list of functions in the #Overview# tab of this unit
/// for more detailed information.
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <pio/pio.h>
#include <dbgu/dbgu.h>
#include <aic/aic.h>
#include <rtt/rtt.h>
#include <utility/trace.h>

#include <stdio.h>

//------------------------------------------------------------------------------
//         Local definitions
//------------------------------------------------------------------------------

/// Device is in the main menu.
#define STATE_MAINMENU      0
/// User is setting an alarm time
#define STATE_SETALARM      1

/// Define AT91C_BASE_RTTC if not already done
#if !defined(AT91C_BASE_RTTC)
    #define AT91C_BASE_RTTC     AT91C_BASE_RTTC0
#endif

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

 /// Current device state.
volatile unsigned char state;

/// New alarm time being currently entered.
volatile unsigned int newAlarm;

/// Indicates if an alarm has occured but has not been cleared.
volatile unsigned char alarmed;

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Updates the DBGU display to show the current menu and the current time
/// depending on the device state.
//------------------------------------------------------------------------------
void RefreshDisplay(void)
{
    printf("%c[2J\r", 27);
    printf("Time: %u\n\r", RTT_GetTime(AT91C_BASE_RTTC));

    // Display alarm
    if (alarmed) {

        printf("!!! ALARM !!!\n\r");
    }

    // Main menu
    if (state == STATE_MAINMENU) {

        printf("Menu:\n\r");
        printf(" r - Reset timer\n\r");
        printf(" s - Set alarm\n\r");
        if (alarmed) {

            printf(" c - Clear alarm notification\n\r");
        }
        printf("\n\rChoice? ");
    }
    // Set alarm
    else if (state == STATE_SETALARM) {

        printf("Enter alarm time: ");
        if (newAlarm != 0) {

            printf("%u", newAlarm);
        }
    }
}

//------------------------------------------------------------------------------
/// Interrupt handler for the RTT. Displays the current time on the DBGU.
//------------------------------------------------------------------------------
void ISR_Rtt(void)
{
    unsigned int status;

    // Get RTT status
    status = RTT_GetStatus(AT91C_BASE_RTTC);

    // Time has changed, refresh display
    if ((status & AT91C_RTTC_RTTINC) == AT91C_RTTC_RTTINC) {

        RefreshDisplay();
    }

    // Alarm
    if ((status & AT91C_RTTC_ALMS) == AT91C_RTTC_ALMS) {

        alarmed = 1;
        RefreshDisplay();
    }
}

//------------------------------------------------------------------------------
/// Configures the RTT to generate a one second tick, which triggers the RTTINC
/// interrupt.
//------------------------------------------------------------------------------
void ConfigureRtt(void)
{
    unsigned int previousTime;

    // Configure RTT for a 1 second tick interrupt
    RTT_SetPrescaler(AT91C_BASE_RTTC, 32768);
    previousTime = RTT_GetTime(AT91C_BASE_RTTC);
    while (previousTime == RTT_GetTime(AT91C_BASE_RTTC));

    // Enable RTT interrupt
    AIC_ConfigureIT(AT91C_ID_SYS, 0, ISR_Rtt);
    AIC_EnableIT(AT91C_ID_SYS);
    RTT_EnableIT(AT91C_BASE_RTTC, AT91C_RTTC_RTTINCIEN);
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Initializes the RTT, displays the current time and allows the user to
/// perform several actions: clear the timer, set an alarm, etc.
//------------------------------------------------------------------------------
int main(void)
{
    unsigned char c;

    // Enable DBGU
    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);
    printf("-- Basic RTT Project %s --\n\r", SOFTPACK_VERSION);
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

    // Configure RTT
    ConfigureRtt();

    // Initialize state machine
    state = STATE_MAINMENU;
    alarmed = 0;
    RefreshDisplay();

    // User input loop
    while (1) { 

        // Wait for user input
        c = DBGU_GetChar();

        // Main menu mode
        if (state == STATE_MAINMENU) {

            // Reset timer
            if (c == 'r') {

                ConfigureRtt();
                RefreshDisplay();
            }
            // Set alarm
            else if (c == 's') {

                state = STATE_SETALARM;
                newAlarm = 0;
                RefreshDisplay();
            }
            // Clear alarm
            else if ((c == 'c') && alarmed) {

                alarmed = 0;
                RefreshDisplay();
            }
        }
        // Set alarm mode
        else if (state == STATE_SETALARM) {

            // Number
            if ((c >= '0') && (c <= '9')) {

                newAlarm = newAlarm * 10 + c - '0';
                RefreshDisplay();
            }
            // Backspace
            else if (c == 8) {

                newAlarm /= 10;
                RefreshDisplay();
            }
            // Enter key
            else if (c == 13) {

                // Avoid newAlarm = 0 case
                if (newAlarm != 0) {

                    RTT_SetAlarm(AT91C_BASE_RTTC, newAlarm);
                }
               
                state = STATE_MAINMENU;
                RefreshDisplay();
            }
        }
    }
}

