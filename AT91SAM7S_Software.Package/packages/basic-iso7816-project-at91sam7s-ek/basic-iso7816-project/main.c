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
/// \dir "Basic ISO7816 project"
///
/// !!!Purpose
/// This example sends ISO 7816 commands to a smartcard connected to the 
/// evaluation kits on AT91 microcontrollers.
///
/// !!!Description
/// The iso7816 software provide in this examples is use to transform APDU 
/// commands to TPDU commands for the smart card. 
/// The iso7816 provide here is for the protocol T=0 only.
/// The send and the receive of a character is made under polling.
/// In the file ISO7816_Init is defined all pins of the card. User must have to
/// change this pins according to his environment.
/// The driver is compliant with CASE 1, 2, 3 of the ISO7816-4 specification.
///
/// !!!Usage
/// -# Build the program and download it inside the evaluation board. Please
///    refer to the <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6224.pdf">SAM-BA User Guide</a>,
///    the <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">GNU-Based Software Development</a>
///    application note or to the <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">IAR EWARM User Guide</a>,
///    depending on your chosen solution.
/// -# On the computer, open and configure a terminal application (e.g.
///    HyperTerminal on Microsoft Windows) with these settings:
///       - 115200 bauds
///       - 8 data bits
///       - No parity
///       - 1 stop bit
///       - Hardware flow control (RTS/CTS)
/// -# Connect the card reader to Atmel boards:
///    C1: Vcc:   7816_3V5V  C5: Gnd  C4: RFU
///    C2: Reset: 7816_RST   C6: Vpp  C8: RFU
///    C3: Clock: 7816_CLK   C7: 7816_IO
///    An other pin must be connected on the card reader for detecting the 
///    insertion and removal: 7816_IRQ.
///    On Atmel’s boards, all this pins can be easily connecting with jumpers.
/// -# Start the application. The following traces shall appear on the terminal:
///    \code
///     -- Basic ISO7816 Project xxx -- 
///     -- AT91xxxxxx-xx
///     -- Compiled: xxx xx xxxx xx:xx:xx --
///     Display the ATR
///    \endcode
///
/// !Contents
///
/// The definitions and functions provided are dispatched inside a number of
/// files:
///    - main.c main software
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/// \unit
///
/// !Purpose
///
/// This file contains all the specific code for the basic-iso7816-project.
///
/// !Contents
/// The code can be roughly broken down as follows:
///    - Configuration functions
///    - Interrupt handlers
///    - Utility functions
///    - The main() function, which implements the program behavior
///
/// !Peripherals
///    - aic
///    - dbgu
///    - pio
///    - pit
///    - usart
///
/// !Components
///    - iso7816
///
/// Please refer to the list of functions in the #Overview# tab of this unit
/// for more detailed information.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------ 
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <aic/aic.h>
#include <pio/pio.h>
#include <pio/pio_it.h>
#include <usart/usart.h>
#include <dbgu/dbgu.h>
#include <iso7816/iso7816_4.h>
#include <utility/trace.h>

#include <string.h>

//------------------------------------------------------------------------------
//         Internal definitions
//------------------------------------------------------------------------------

/// Maximum size in bytes of the smartcard answer to a command.
#define MAX_ANSWER_SIZE         10

/// Maximum ATR size in bytes.
#define MAX_ATR_SIZE            55

//------------------------------------------------------------------------------
//         Internal variables
//------------------------------------------------------------------------------

/// Test command #1.
static const unsigned char testCommand1[] = {0x00, 0x10, 0x00, 0x00};
/// Test command #2.
static const unsigned char testCommand2[] = {0x00, 0x20, 0x00, 0x00, 0x02};
/// Test command #3.
static const unsigned char testCommand3[] = {0x00, 0x30, 0x00, 0x00, 0x02, 0x0A, 0x0B};

static const Pin pinsISO7816[]    = {PINS_ISO7816};
static const Pin pinIso7816RstMC  = PIN_ISO7816_RSTMC;


//------------------------------------------------------------------------------
//         Internal functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Optional smartcard detection
//------------------------------------------------------------------------------

#ifdef PIN_SMARTCARD_CONNECT

/// Smartcard detection pin.
static const Pin pinSmartCard = PIN_SMARTCARD_CONNECT;

//------------------------------------------------------------------------------
// PIO interrupt service routine. Checks if the smartcard has been connected
// or disconnected.
//------------------------------------------------------------------------------
static void ISR_PioSmartCard(const Pin *pPin)
{
    // Check all pending interrupts
    if ((pinSmartCard.pio->PIO_ISR & pinSmartCard.mask) != 0) {

        // Check current level on pin
        if (PIO_Get(&pinSmartCard) == 0) {

            printf("-I- Smartcard inserted\n\r");
        }
        else {

            printf("-I- Smartcard removed\n\r");
        }
    }
}

//------------------------------------------------------------------------------
// Configures the smartcard detection pin to trigger an interrupt.
//------------------------------------------------------------------------------
static void ConfigureCardDetection(void)
{
    PIO_Configure(&pinSmartCard, 1);
    PIO_ConfigureIt(&pinSmartCard, ISR_PioSmartCard);
    PIO_EnableIt(&pinSmartCard);
}

#else

//------------------------------------------------------------------------------
/// Dummy implementation.
//------------------------------------------------------------------------------
static void ConfigureCardDetection(void)
{
    printf("-I- Smartcard detection not supported.\n\r");
}

#endif 

//------------------------------------------------------------------------------
// Displays a menu which enables the user to send several commands to the
// smartcard and check its answers.
//------------------------------------------------------------------------------
static void SendReceiveCommands(void)
{
    unsigned char pMessage[MAX_ANSWER_SIZE];
    unsigned char size;
    unsigned char key;
    unsigned char command;
    unsigned char i;

    // Clear message buffer
    memset(pMessage, 0, sizeof(pMessage));

    // Display menu
    printf("-I- The following three commands can be sent:\n\r");
    printf("  1. ");
    for (i=0; i < sizeof(testCommand1); i++) {

        printf("0x%X ", testCommand1[i]);
    }
    printf("\n\r  2. ");
    for (i=0; i < sizeof(testCommand2); i++) {

        printf("0x%X ", testCommand2[i]);
    }
    printf("\n\r  3. ");
    for (i=0; i < sizeof(testCommand3); i++) {

        printf("0x%X ", testCommand3[i]);
    }
    printf("\n\r");

    // Get user input
    key = 0;
    while (key != 'q') {

        printf("\r                        ");
        printf("\rChoice ? (q to quit): ");
        key = DBGU_GetChar();
        printf("%c", key);
        command = key - '0';

        // Check user input
        size = 0;
        if (command == 1) {

            printf("\n\r-I- Sending command ");
            for (i=0; i < sizeof(testCommand1); i++) {
        
                printf("0x%02X ", testCommand1[i]);
            }
            printf("...\n\r");
            size = ISO7816_XfrBlockTPDU_T0(testCommand1,
                                           pMessage,
                                           sizeof(testCommand1));
        }
        else if (command == 2) {

            printf("\n\r-I- Sending command ");
            for (i=0; i < sizeof(testCommand2); i++) {
        
                printf("0x%02X ", testCommand2[i]);
            }
            printf("...\n\r");
            size = ISO7816_XfrBlockTPDU_T0(testCommand2,
                                           pMessage,
                                           sizeof(testCommand2));
        }
        else if (command == 3) {

            printf("\n\r-I- Sending command ");
            for (i=0; i < sizeof(testCommand3); i++) {
        
                printf("0x%02X ", testCommand3[i]);
            }
            printf("...\n\r");
            size = ISO7816_XfrBlockTPDU_T0(testCommand3,
                                           pMessage,
                                           sizeof(testCommand3));
        }

        // Output smartcard answer
        if (size > 0) {

            printf("\n\rAnswer: ");
            for (i=0; i < size; i++) {

                printf("0x%02X ", pMessage[i]);
            }
            printf("\n\r");
        }
    }

    printf("Quitting ...\n\r");
}

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Initializes the DBGU and ISO7816 driver, and starts some tests.
/// \return Unused (ANSI-C compatibility)
//------------------------------------------------------------------------------
int main(void)
{
    unsigned char pAtr[MAX_ATR_SIZE];
    unsigned char size;

    // Initialize Atr buffer
    memset(pAtr, 0, sizeof(pAtr));

    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);
    printf("-- Basic ISO7816 Project %s --\n\r", SOFTPACK_VERSION);
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

    // Configure IT on Smart Card
    ConfigureCardDetection();

    // Configure ISO7816 driver
    PIO_Configure(pinsISO7816, PIO_LISTSIZE(pinsISO7816));
    ISO7816_Init(pinIso7816RstMC);

    // Read ATR
    ISO7816_warm_reset();
    ISO7816_Datablock_ATR(pAtr, &size);

    // Decode ATR
    ISO7816_Decode_ATR(pAtr);

    // Allow user to send some commands
    SendReceiveCommands();

    return 0;
}


