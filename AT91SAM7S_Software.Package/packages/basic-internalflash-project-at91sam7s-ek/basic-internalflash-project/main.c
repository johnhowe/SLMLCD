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
/// \dir "Basic-internal-project"
///
/// !!!Purpose
///
/// This basic demonstrates the features of the Embedded Flash Controller 
/// (EFC/EEFC) present on Atmel AT91 microcontrollers. The EFC enables 
/// in-application programming of the internal %flash, as well as protecting 
/// memory regions or the whole chip. 
///
/// You can find following information depends on your needs:
/// - FLASHD driver provides the unified interface of functions and operations 
///   for all supported Embedded %Flash Memory Devices.
/// - EFC(EEFC) peripheral interface for configuration the EFC(EEFC) peripheral
/// - Example code for internal %Flash operations.
///
/// !See 
///    - flash: FLASHD interface driver.
///    - efc: EFC peripheral interface.
///    - eefc: EEFC peripheral interface.
///
/// !!!Requirements
///
/// This package can be used with all Atmel evaluation kits that have EFC(EEFC)
/// interface, the package could runs at SRAM or internal %flash.
///
/// !!!Description
///
/// The program performs the following set of commands: 
/// - First, it unlocks the whole %flash 
/// - It writes a pattern in the last page of the %flash, and checks it back 
/// - It locks the last region of the %flash, and verifies that the status is 
///   updated accordingly 
/// - It unlocks the last region and verifies that it the status is updated 
///   accordingly 
/// - Lastly, GPNVM 1 is cleared and set, the status being checked for update 
///   between the operations (the original state of the GPNVM is restored 
///   after this step) 
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
/// -# The application will display the various tests it is executing and the 
///    results (example shown for the SAM9XE256): 
///    \code
///     -- Basic Internal Flash Project xxx --
///     -- AT91xxxxxx-xx
///     -- Compiled: xxx xx xxxx xx:xx:xx --
///     -I- Unlocking the whole flash
///     -D- Actual lock range is 0x200000 - 0x240000
///     -I- Writing last page with walking bit pattern
///     -I- Checking page contents ..........................................
///          ................................................................. ok
///     -I- Locking last page
///     -D- Actual lock range is 0x23C000 - 0x240000
///     -I- Checking lock status ... ok
///     -I- Unlocking last page
///     -D- Actual lock range is 0x23C000 - 0x240000
///     -I- Checking lock status ... ok
///     -I- GPNVM #1 is cleared
///     -I- Setting GPNVM #1
///     -I- Clearing GPNVM #1
///     -I- All tests ok
///    \endcode
/// -# As soon as a dataflash is connected, the tests will start. Eventually, 
///    the test result (pass or fail) will be output on the DBGU.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \unit
///
/// !Purpose
///
/// This file contains all the specific code for the basic-internal-project.
/// It tests the embedded %flash present on the evaluation kit by unlock and
/// writing last page of internal %flash.
/// 
/// !Contents
/// The code can be roughly broken down as follows:
///    - The main() function, which implements the program behavior.
///       - Initializes an FLash driver.
///       - Unlock the whole page of the %flash.
///       - It writes a pattern in the last page of the %flash, and checks it back. 
///       - It locks the last region of the %flash, and verifies that 
///         the status is updated accordingly.
///       - It unlocks the last region and verifies that it the status 
///         is updated accordingly 
///       - Lastly, GPNVM 1 is cleared and set, the status being checked 
///         for update between the operations (the original state of the 
///         GPNVM is restored after this step) 
///
/// !See also
///    - flash: FLASHD interface driver.
///    - efc: EFC peripheral interface.
///    - eefc: EEFC peripheral interface.
///
/// Please refer to the list of functions in the #Overview# tab of this unit
/// for more detailed information.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <pio/pio.h>
#include <dbgu/dbgu.h>
#include <efc/efc.h>
#include <eefc/eefc.h>
#include <memories/flash/flashd.h>
#include <utility/assert.h>
#include <utility/trace.h>

#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Tests the EFC peripheral features.
//------------------------------------------------------------------------------
int main(void)
{
    unsigned int i;
    unsigned char error;
    unsigned int pBuffer[AT91C_IFLASH_PAGE_SIZE / 4];
    unsigned int lastPageAddress;
    volatile unsigned int *pLastPageData;
    unsigned char pageLocked;

    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);
    printf("-- Basic Internal Flash Project %s --\n\r", SOFTPACK_VERSION);
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

    // Initialize flash driver
    FLASHD_Initialize(BOARD_MCK);

    // Unlock whole flash
    printf("-I- Unlocking the whole flash\n\r");
#if defined(at91sam7a3)
    error = FLASHD_Unlock(AT91C_IFLASH, AT91C_IFLASH + 64 * 1024, 0, 0);
#else
    error = FLASHD_Unlock(AT91C_IFLASH, AT91C_IFLASH + AT91C_IFLASH_SIZE, 0, 0);
#endif
    ASSERT(!error, "-F- Error while trying to unlock the whole flash (0x%02X)\n\r", error);

    // Performs tests on last page (to avoid overriding existing program).
    lastPageAddress = AT91C_IFLASH + AT91C_IFLASH_SIZE - AT91C_IFLASH_PAGE_SIZE;
    pLastPageData = (volatile unsigned int *) lastPageAddress;

    // Write page with walking bit pattern (0x00000001, 0x00000002, ...)
    printf("-I- Writing last page with walking bit pattern\n\r");
    for (i=0; i < (AT91C_IFLASH_PAGE_SIZE / 4); i++) {

        pBuffer[i] = 1 << (i % 32);
    }
    error = FLASHD_Write(lastPageAddress, pBuffer, AT91C_IFLASH_PAGE_SIZE);
    ASSERT(!error, "-F- Error when trying to write page (0x%02X)\n\r", error);

    // Check page contents
    printf("-I- Checking page contents ");
    for (i=0; i < (AT91C_IFLASH_PAGE_SIZE / 4); i++) {

        printf(".");
        ASSERT(pLastPageData[i] == (1 << (i % 32)),
               "\n\r-F- Expected 0x%08X at address 0x%08X, found 0x%08X\n\r",
               (1 << (i % 32)), (unsigned int) &(pLastPageData[i]), pLastPageData[i]);
    }
    printf(" ok \n\r");

#if defined(at91sam7a3)
    // Only the first 64Kb can be locked in the SAM7A3
    lastPageAddress = AT91C_IFLASH + (64*1024) - AT91C_IFLASH_PAGE_SIZE;
#endif

    // Lock page
    printf("-I- Locking last page\n\r");
    error = FLASHD_Lock(lastPageAddress, lastPageAddress + AT91C_IFLASH_PAGE_SIZE, 0, 0);
    ASSERT(!error, "-F- Error when trying to lock page (0x%02X)\n\r", error);

    // Check that associated region is locked
    printf("-I- Checking lock status ... ");
    pageLocked = FLASHD_IsLocked(lastPageAddress, lastPageAddress + AT91C_IFLASH_PAGE_SIZE);
    ASSERT(pageLocked, "\n\r-F- Page is not locked\n\r");
    printf("ok\n\r");

    // Unlock page
    printf("-I- Unlocking last page\n\r");
    error = FLASHD_Unlock(lastPageAddress, lastPageAddress + AT91C_IFLASH_PAGE_SIZE, 0, 0);
    ASSERT(!error, "-F- Error when trying to unlock page (0x%02X)\n\r", error);

    // Check that associated region is unlocked
    printf("-I- Checking lock status ... ");
    pageLocked = FLASHD_IsLocked(lastPageAddress, lastPageAddress + AT91C_IFLASH_PAGE_SIZE);
    ASSERT(!pageLocked, "\n\r-F- Page is locked\n\r");
    printf("ok\n\r");

#if (EFC_NUM_GPNVMS > 0)
    // Test GPNVM bit #1 (should be safe)
    if (FLASHD_IsGPNVMSet(1)) {

        printf("-I- GPNVM #1 is set\n\r");

        // Clear GPNVM
        printf("-I- Clearing GPNVM #%d\n\r", 1);
        error = FLASHD_ClearGPNVM(1);
        ASSERT(!error, "-F- Error while trying to clear GPNVM (0x%02X)\n\r", error);
        ASSERT(!FLASHD_IsGPNVMSet(1), "-F- GPNVM is set\n\r");

        // Set GPNVM
        printf("-I- Setting GPNVM #%d\n\r", 1);
        error = FLASHD_SetGPNVM(1);
        ASSERT(!error, "-F- Error while trying to set GPNVM (0x%02X)\n\r", error);
        ASSERT(FLASHD_IsGPNVMSet(1), "-F- GPNVM is not set\n\r");

    }
    else {

        printf("-I- GPNVM #1 is cleared\n\r");

        // Set GPNVM
        printf("-I- Setting GPNVM #%d\n\r", 1);
        error = FLASHD_SetGPNVM(1);
        ASSERT(!error, "-F- Error while trying to set GPNVM (0x%02X)\n\r", error);
        ASSERT(FLASHD_IsGPNVMSet(1), "-F- GPNVM is not set\n\r");

        // Clear GPNVM
        printf("-I- Clearing GPNVM #%d\n\r", 1);
        error = FLASHD_ClearGPNVM(1);
        ASSERT(!error, "-F- Error while trying to clear GPNVM (0x%02X)\n\r", error);
        ASSERT(!FLASHD_IsGPNVMSet(1), "-F- GPNVM is set\n\r");
    }
#endif

    printf("-I- All tests ok\n\r");
    return 0;
}

