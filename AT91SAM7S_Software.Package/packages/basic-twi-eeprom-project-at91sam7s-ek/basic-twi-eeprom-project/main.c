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
/// \dir "TWI EEPROM Project"
///
/// !!!Purpose
///
/// This example program demonstrates how to use the TWI peripheral of an AT91
/// microcontroller to access an external serial EEPROM chip. 
///
/// !See
/// - aic: Advanced interrupt controller driver
/// - twi: Two wire interface driver
///
/// !!!Requirements
///
/// An external serial EEPROM must be connected to the TWI bus of the 
/// microcontroller. For further information on this topic, please refer to 
/// the following application note: 
/// <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6327.pdf">
/// Using the Two-wire interface (TWI) in Master Mode on AT91 Microcontrollers. </a>
///
/// Pay particular attention to the fact that on some boards, such as the
/// AT91SAM7S-EK, there is no pull-up on the TWI bus: they must be 
/// added externally. 
///
/// !!!Description
///
/// This software performs simple tests on the first and second page of the EEPROM: 
/// - Sets both pages to all zeroes 
/// - Writes pattern in page #0 (polling) 
/// - Reads back data in page #0 and compare with original pattern (polling) 
/// - Writes pattern in page #1 (interrupts) 
/// - Reads back data in page #1 and compare with original pattern (interrupts) 
///
/// !!!Usage
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
///     -- Basic TWI EEPROM Project xxx --
///     -- AT91xxxxxx-xx
///     -- Compiled: xxx xx xxxx xx:xx:xx --
///    \endcode
/// -# The following traces detail operations on the EEPROM, displaying success 
///    or error messages depending on the results of the commands. 
///
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \unit
///
/// !Purpose
///
/// This file contains all the specific code for the 
/// basic-twi-eeprom-project.
///
/// !Contents
/// The code can be roughly broken down as follows:
///    - TWI interrupt handler
///    - The main function, which implements the program behavior
///       - Configure TWI
///       - Sets the first and second page of the EEPROM to all zeroes
///       - Writes pattern in page 0; 
///          Reads back data in page 0 and compare with original pattern (polling). 
///       - Writes pattern in page 1; 
///          Reads back data in page 1 and compare with original pattern (interrupts). 
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
#include <twi/twi.h>
#include <utility/math.h>
#include <utility/assert.h>
#include <utility/trace.h>
#include <drivers/async/async.h>
#include <drivers/twi/twid.h>

#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------
//         Local definitions
//------------------------------------------------------------------------------

/// TWI peripheral redefinition if needed
#if !defined(AT91C_BASE_TWI) && defined(AT91C_BASE_TWI0)
    #define AT91C_BASE_TWI      AT91C_BASE_TWI0
    #define AT91C_ID_TWI        AT91C_ID_TWI0
    #define PINS_TWI            PINS_TWI0
#endif

/// TWI clock frequency in Hz.
#define TWCK            400000

/// Slave address of AT24C chips.
#define AT24C_ADDRESS   0x50

/// Page size of an AT24C1024 chip (in bytes)
#define PAGE_SIZE       256

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

/// Pio pins to configure.
static const Pin pins[] = {PINS_TWI};

/// TWI driver instance.
static Twid twid;

/// Page buffer.
static unsigned char pData[PAGE_SIZE];

//------------------------------------------------------------------------------
///        Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// TWI interrupt handler. Forwards the interrupt to the TWI driver handler.
//------------------------------------------------------------------------------
void ISR_Twi(void)
{
    TWID_Handler(&twid);
}

//------------------------------------------------------------------------------
/// Dummy callback, to test asynchronous transfer modes.
//------------------------------------------------------------------------------
void TestCallback()
{
    printf("-I- Callback fired !\n\r");
}

//------------------------------------------------------------------------------
///        Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Main function
//------------------------------------------------------------------------------
int main()
{
    unsigned int i;
    Async async;
    unsigned int numErrors;

    PIO_Configure(pins, PIO_LISTSIZE(pins));
    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);
    printf("-- Basic TWI EEPROM Project %s --\n\r", SOFTPACK_VERSION);
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

    // Configure TWI
    // In IRQ mode: to avoid problems, the priority of the TWI IRQ must be max.
    // In polling mode: try to disable all IRQs if possible.
    // (in this example it does not matter, there is only the TWI IRQ active)
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_TWI;
    TWI_ConfigureMaster(AT91C_BASE_TWI, TWCK, BOARD_MCK);
    TWID_Initialize(&twid, AT91C_BASE_TWI);
    AIC_ConfigureIT(AT91C_ID_TWI, 0, ISR_Twi);
    AIC_EnableIT(AT91C_ID_TWI);

    // Erase page #0 and #1
    memset(pData, 0, PAGE_SIZE);
    printf("-I- Filling page #0 with zeroes ...\n\r");
    TWID_Write(&twid, AT24C_ADDRESS, 0x0000, 2, pData, PAGE_SIZE, 0);

    // Wait at least 10 ms
    for (i=0; i < 1000000; i++);

    printf("-I- Filling page #1 with zeroes ...\n\r");
    TWID_Write(&twid, AT24C_ADDRESS, 0x0100, 2, pData, PAGE_SIZE, 0);

    // Wait at least 10 ms
    for (i=0; i < 1000000; i++);

    // Synchronous operation
    printf("-I- Read/write on page #0 (polling mode)\n\r");

    // Write checkerboard pattern in first page
    for (i=0; i < PAGE_SIZE; i++) {

        // Even
        if ((i & 1) == 0) {
        
            pData[i] = 0xA5;
        }
        // Odd
        else {

            pData[i] = 0x5A;
        }
    }
    TWID_Write(&twid, AT24C_ADDRESS, 0x0000, 2, pData, PAGE_SIZE, 0);

    // Wait at least 10 ms
    for (i=0; i < 1000000; i++);

    // Read back data
    memset(pData, 0, PAGE_SIZE);
    TWID_Read(&twid, AT24C_ADDRESS, 0x0000, 2, pData, PAGE_SIZE, 0);

    // Compare
    numErrors = 0;
    for (i=0; i < PAGE_SIZE; i++) {

        // Even
        if (((i & 1) == 0) && (pData[i] != 0xA5)) {

            printf("-E- Data mismatch at offset #%u: expected 0xA5, read 0x%02X\n\r", i, pData[i]);
            numErrors++;
        }
        // Odd
        else if (((i & 1) == 1) && (pData[i] != 0x5A)) {

            printf("-E- Data mismatch at offset #%u: expected 0x5A, read 0x%02X\n\r", i, pData[i]);
            numErrors++;
        }
    }
    printf("-I- %u comparison error(s) found\n\r", numErrors);

    // Asynchronous operation
    printf("-I- Read/write on page #1 (IRQ mode)\n\r");

    // Write checkerboard pattern in first page
    for (i=0; i < PAGE_SIZE; i++) {

        // Even
        if ((i & 1) == 0) {
        
            pData[i] = 0xA5;
        }
        // Odd
        else {

            pData[i] = 0x5A;
        }
    }
    memset(&async, 0, sizeof(async));
    async.callback = (void *) TestCallback;
    TWID_Write(&twid, AT24C_ADDRESS, 0x0100, 2, pData, PAGE_SIZE, &async);
    while (!ASYNC_IsFinished(&async));

    // Wait at least 10 ms
    for (i=0; i < 1000000; i++);

    // Read back data
    memset(pData, 0, PAGE_SIZE);
    memset(&async, 0, sizeof(async));
    async.callback = (void *) TestCallback;
    TWID_Read(&twid, AT24C_ADDRESS, 0x0100, 2, pData, PAGE_SIZE, &async);
    while (!ASYNC_IsFinished(&async));

    // Compare
    numErrors = 0;
    for (i=0; i < PAGE_SIZE; i++) {

        // Even
        if (((i & 1) == 0) && (pData[i] != 0xA5)) {

            printf("-E- Data mismatch at offset #%u: expected 0xA5, read 0x%02X\n\r", i, pData[i]);
            numErrors++;
        }
        // Odd
        else if (((i & 1) == 1) && (pData[i] != 0x5A)) {

            printf("-E- Data mismatch at offset #%u: expected 0x5A, read 0x%02X\n\r", i, pData[i]);
            numErrors++;
        }
    }
    printf("-I- %u comparison error(s) found\n\r", numErrors);

    return 0;
}

