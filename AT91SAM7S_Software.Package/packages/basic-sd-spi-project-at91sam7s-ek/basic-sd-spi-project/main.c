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
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <aic/aic.h>
#include <pio/pio.h>
#include <dbgu/dbgu.h>
#include <sdmmc/sdspi.h>
#include <utility/assert.h>
#include <utility/trace.h>
#include <sdmmc/sdmmc_spi.h>

#include <string.h>

//------------------------------------------------------------------------------
/// \dir "Basic-sd-spi-project"
///
/// !!!Purpose
///
/// The Basic-sd-spi-project will help you to get familiar with sdmmc_spi interface on 
/// AT91SAM microcontrollers. It can also help you to get familiar with the SD operation flow
/// which can be used for fast implementation of your own sd drivers and other applications 
/// related.
///
/// You can find following information depends on your needs:
/// - Usage of auto detection of sdcard insert and sdcard write-protection detection
/// - sdspi interface initialize sequence and interrupt installation
/// - Sdcard driver implementation based on spi-interface (sdmmc_spi)
/// - Sdcard physical layer (spi-interface) initialize sequence implementation
/// - Sample usage of sdcard write and read
///
/// !See
/// - sdmmc_spi : sdcard physical layer driver with spi-interface
/// - sdspi : spi-bus driver
///
/// !!!Requirements
///
/// This package can be used with all Atmel evaluation kits that have SPI and EBI interface,  
/// the package runs at SRAM or SDRAM, so SDRAM device is needed if you want to run this 
/// package in SDRAM
/// Please note that the AT91SAM7L-EK, AT91SAM7S-EK and AT91SAM7SE-EK don't have
/// SDCARD inside board.
///
/// !!!Description
///
/// Open HyperTerminal before running this program, use SAM-BA to download this program to 
/// SRAM or SDRAM, make the program run, the HyperTerminal will give out the test results.
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
/// -# Start the application
/// -# In HyperTerminal, it will show something like
///
///     \code
///     -I- Testing block [  4216 -   4217] ...
///     0x00000000: 02000000 02040004 0A000800 0A040804
///     0x00000010: 02100010 02140014 0A100810 0A140814
///     0x00000020: 22002000 22042004 2A002800 2A042804
///     0x00000030: 22102010 22142014 2A102810 2A142814
///     0x00000040: 02400040 02440044 0A400840 0A440844
///     \endcode
///
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \unit
///
/// !Purpose
///
/// This file contains all the specific code for the basic-sd-spi-project
///
/// !Contents
/// The basic-sd-spi-project application can be roughly broken down as follows:
///    - Optional functions
///       - CheckProtection
///       - WaitSdConn
///    - Interrupt handlers
///       - ISR_Spi0
///    - Debug functions
///       - DumpMemorySDSPI
///    - The main function, which implements the program behavior
///       - I/O configuration
///       - sd card auto-detect and check whether sd card is write-protected (if supported)
///       - Initialize SPI interface and installing an isr relating to SPI
///       - Initialize sdcard with sdspi interface, get necessary sdcard's parameters
///       - write/read multiple blocks once and print the result to DBGU
///       - write/read single block once


//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

/// SPI driver instance.
static SdSpi sdSpiDrv;

/// SDCard driver instance.
static SdCard sdDrv;

/// SD card pins.
static const Pin pinsSd[] = {BOARD_SD_SPI_PINS};
 
//------------------------------------------------------------------------------
//         Local define
//------------------------------------------------------------------------------
#define MULTIPLE_TEST

#define NB_MULTI_BLOCKS 5

/// SPI clock frequency, in Hz.
#define SPCK        10000000


//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// SPI0 interrupt handler. Forwards the event to the SPI driver handler.
//------------------------------------------------------------------------------
void ISR_Spi0(void)
{
    SDSPI_Handler(&sdSpiDrv);
}

//------------------------------------------------------------------------------
/// Displays the content of the given buffer on the DBGU.
/// \param pBuffer  Pointer to the buffer to dump.
/// \param size  Buffer size in bytes.
//------------------------------------------------------------------------------
void DumpMemorySDSPI(const unsigned char *pBuffer, unsigned int size)
{
    unsigned int i, j;

    for (i=0; i < (size / 16); i++) {

        printf("0x%08X: ", i*16);
        for (j=0; j < 4; j++) {

            printf("%08X ", ((unsigned int *) pBuffer)[i*4+j]);
        }
        printf("\n\r");
    }
}

//------------------------------------------------------------------------------
//         Optional: SD card detection
//------------------------------------------------------------------------------

#ifdef BOARD_SD_PIN_CD

/// SD card detection pin instance.
static const Pin pinSdCardDetect = BOARD_SD_PIN_CD;

//------------------------------------------------------------------------------
/// Waits for a SD card to be connected.
//------------------------------------------------------------------------------
void WaitSdConn(void)
{
    PIO_Configure(&pinSdCardDetect, 1);
    printf("-I- Please connect a SD card ...\n\r");
    while (PIO_Get(&pinSdCardDetect) != 0);
    printf("-I- SD card connection detected\n\r");
}

#else

//------------------------------------------------------------------------------
/// Dummy function.
//------------------------------------------------------------------------------
void WaitSdConn(void)
{
    printf("-I- SD card detection not available, assuming card is present\n\r");
}

#endif

//------------------------------------------------------------------------------
//         Optional: Write protection status
//------------------------------------------------------------------------------

#ifdef BOARD_SD_PIN_WP

/// Write protection status pin instance.
static const Pin pinSdWriteProtect = BOARD_SD_PIN_WP;

//------------------------------------------------------------------------------
/// Checks if the device is write protected.
//------------------------------------------------------------------------------
void CheckProtection(void)
{
    PIO_Configure(&pinSdWriteProtect, 1);
    if (PIO_Get(&pinSdWriteProtect) != 0) {

        printf("-I- SD card is write-protected\n\r");
    }
    else {

        printf("-I- SD card is NOT write-protected.\n\r");
    }
}

#else

//------------------------------------------------------------------------------
/// Dummy implementation.
//------------------------------------------------------------------------------
void CheckProtection(void)
{
    printf("-I- Cannot check if SD card is write-protected\n\r");
}

#endif
//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Main function
//------------------------------------------------------------------------------
int main(void)
{
    unsigned char pBuffer[SD_BLOCK_SIZE * NB_MULTI_BLOCKS];
    unsigned int block;
    unsigned int i;
    unsigned short multiBlock;
    unsigned char error;

    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);
    printf("-- Basic SD-Card SPI Mode Project %s --\n\r", SOFTPACK_VERSION);
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

    // Configure SDcard pins
    PIO_Configure(pinsSd, PIO_LISTSIZE(pinsSd));

    // Wait for SD card connection (if supported)
    WaitSdConn();

    // Check if card is write-protected (if supported)
    CheckProtection();

    // Initialize the SPI driver
    AIC_ConfigureIT(BOARD_SD_SPI_ID,  AT91C_AIC_PRIOR_LOWEST, ISR_Spi0);
    SDSPI_Configure(&sdSpiDrv, BOARD_SD_SPI_BASE, BOARD_SD_SPI_ID);
    AIC_EnableIT(BOARD_SD_SPI_ID);

    //SDSPI_ConfigureCS(&sdSpiDrv, BOARD_SD_NPCS, SDSPI_CSR(BOARD_MCK / SPCK));
    SDSPI_ConfigureCS(&sdSpiDrv, BOARD_SD_NPCS, AT45_CSR(BOARD_MCK, SPCK));

    // Initialize the SD card driver
    if (SD_Init(&sdDrv, (SdDriver *)&sdSpiDrv)) {

        printf("-E- SD/MMC card initialization failed\n\r");
        return 0;
    }
    else {

        printf("-I- SD/MMC card initialization successful\n\r");
        printf("-I- Card size: %u MB\n\r", SD_TOTAL_SIZE(&sdDrv)/(1024*1024));
        printf("-I- Block size: %d Bytes\n\r", SD_CSD_BLOCK_LEN(&sdDrv));
    }

    // Perform tests on each block
    multiBlock = 1;
    for (block=0; block < (SD_TOTAL_BLOCK(&sdDrv)-multiBlock); ) {
        // Perform single block or multi block transfer
        printf("-I- Testing block [%6u - %6u] ...\n\r", block, (block + multiBlock -1));
        //printf("multiBlock=%d\n\r", multiBlock);

        // Clear the block
        memset(pBuffer, 0, SD_BLOCK_SIZE * multiBlock);
        for (i=0; i < SD_BLOCK_SIZE * multiBlock; i++) {

            ASSERT(pBuffer[i] == 0,
                   "-F- Invalid data at pBuffer[%u] before write ! (expected 0x00, read 0x%02X)\n\r",
                   i, pBuffer[i]);
        }
        error = SD_WriteBlock(&sdDrv, block, multiBlock, pBuffer);
        ASSERT(!error, "-F- Failed to write block (%d) #%u\n\r", error, block);

        // Read back the data to check the write operation
        memset(pBuffer, 0xFF, SD_BLOCK_SIZE * multiBlock);
        error = SD_ReadBlock(&sdDrv, block, multiBlock, pBuffer);
        ASSERT(!error, "-F- Failed to read block (%d) #%u\n\r", error, block);
        for (i=0; i < SD_BLOCK_SIZE * multiBlock; i++) {

            ASSERT(pBuffer[i] == 0,
                   "-F- Invalid data at pBuffer[%u] (expected 0x00, read 0x%02X)\n\r",
                   i, pBuffer[i]);
        }

        // Write a checkerboard pattern on the block
        for (i=0; i < SD_BLOCK_SIZE * multiBlock; i++) {

            if ((i & 1) == 0) {

                pBuffer[i] = (i & 0x55);
            }
            else {

                pBuffer[i] = (i & 0xAA);
            }
        }
        error = SD_WriteBlock(&sdDrv, block, multiBlock, pBuffer);
        ASSERT(!error, "\n\r-F- Failed to write block #%u\n\r", block);

        // Read back the data to check the write operation
        memset(pBuffer, 0, SD_BLOCK_SIZE * multiBlock);
        error = SD_ReadBlock(&sdDrv, block, multiBlock, pBuffer);

        DumpMemorySDSPI(pBuffer, SD_BLOCK_SIZE * multiBlock);

        ASSERT(!error, "\n\r-F- Failed to read block #%u\n\r", block);

        for (i=0; i < SD_BLOCK_SIZE * multiBlock; i++) {

            ASSERT( (((i & 1) == 0) && (pBuffer[i] == (i & 0x55)))
                 || (pBuffer[i] == (i & 0xAA)),
                   "\n\r-F- Invalid data at pBuffer[%u] (expected 0x%02X, read 0x%02X)\n\r",
                   i, ((i & 1) == 0) ? (i & 0x55) : (i & 0xAA), pBuffer[i]);
        }
        printf("***** Block OK *****\n\r");
        block += multiBlock;

        // Perform different single or multiple bloc operations
        if (++multiBlock > NB_MULTI_BLOCKS)
            multiBlock = 1;
    }

    #ifdef MULTIPLE_TEST
    printf("MULTIPLE_TEST\n\r");
    block=0;
    for (; block < SD_TOTAL_BLOCK(&sdDrv)-NB_MULTI_BLOCKS; ) {

        for (multiBlock = 0; multiBlock < NB_MULTI_BLOCKS; multiBlock++) {
            for (i=0; i < SD_BLOCK_SIZE; i++) {
                    pBuffer[i] = ((block + multiBlock) & 0xFF);
            }
            printf("-I- Writing block [%6u] ...\n\r", (block + multiBlock));
            error = SD_WriteBlock(&sdDrv, (block + multiBlock), 1, pBuffer);
            ASSERT(!error, "-F- 2 Failed to write block #%u\n\r", (block + multiBlock));
        }


        for (multiBlock = 0; multiBlock < NB_MULTI_BLOCKS; multiBlock++) {
            printf("-I- Reading block [%6u] ...\n\r", (block + multiBlock));
            error = SD_ReadBlock(&sdDrv, (block + multiBlock), 1, pBuffer);
            // Dump(pBuffer, SD_BLOCK_SIZE);
            ASSERT(!error, "-F- Failed to read block #%u\n\r", (block + multiBlock));
            for (i=0; i < SD_BLOCK_SIZE; i++) {

                ASSERT(pBuffer[i] == ((block + multiBlock) & 0xFF),
                       "-F- Invalid data at pBuffer[%u] (expected 0x%02X, read 0x%02X)\n\r",
                       i, ((block + multiBlock) & 0xFF), pBuffer[i]);
            }
        }

        block+= NB_MULTI_BLOCKS;
    }
    #endif

    SDSPI_Close(&sdSpiDrv);
    // ASSERT(!error, "\n\r-F- Failed to stop SD card!\n\r");

    return 0;
}

