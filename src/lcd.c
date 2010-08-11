/*
 * lcd.c
 *
 * Functions for communicating with LCD module
 *
 * John Howe 2010
 */

#include "lcd.h"



void shiftFront (colour_t *colour);

/* Init function taken from datasheet */
void initLCD(void) {

    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
    pPIO->PIO_SODR = PRST; // Reset pin High

    busyWait(10000); // 10ms
    write(COMMAND, EXTIN); // use the ext=0 command table
    write(COMMAND, SLPOUT); // exit sleep mode
    write(COMMAND, OSCON); // turns on internal oscillation circuit
    write(COMMAND, PWRCTR); // turn on or off booster circuit, voltage reg and ref. voltage
    write(DATA, 0x08); // booster must be on first (VB=1)
    busyWait(1000); // wait one millisecond
    write(COMMAND, PWRCTR); // turn on or off booster circuit, voltage reg and ref. voltage
    write(DATA, 0x0b); // booster, regulator, follower on (VB=VF=VR=1)
    write(COMMAND, VOLCTR); // program optimum lcd supply voltage
    write(DATA, 0x32); // DL38
    write(DATA, 0x04); // DH,Vop = 15.5v, normal display
    write(COMMAND, DISCTL);
    write(DATA, 0x04); // CLD = 0, not divide
    write(DATA, 0x27); // 1/160 duty 39
    write(DATA, 0x00); // FR
    write(COMMAND, DISINV);
    write(COMMAND, COMSCN);
    write(DATA, 0x01); // 0->79 80->159
    write(COMMAND, DATSDR);
    write(DATA, 0x00); // normal
    write(DATA, 0x00); // RGB arrangement
    write(DATA, 0x02); // 32 gray-scale 3byte 3pixel mode
    write(COMMAND, LASET);
    write(DATA, 0x00); // start line = 0
    write(DATA, 0x9F); // end line = 159
    write(COMMAND, CASET);
    write(DATA, 0x00); // start column = 0
    write(DATA, 0x4F); // end column = 79 -> (79+1)*3=240

    write(COMMAND, EXTOUT); // use the ext=1 command table
    write(COMMAND, ANASET); // analog circuit set
    write(DATA, 0x00); // oscillator frequency = 12.7KHz
    write(DATA, 0x01); // Booter frequency = 6KHz
    write(DATA, 0x05); // bias = 1/11
    write(COMMAND, SWINT); // software initial

    write(COMMAND, EXTIN); // use the ext=0 command table
    write(COMMAND, DISON); // turn display on
    write(COMMAND, PTLOUT); // exit partial display mode
    busyWait(10000); // 10ms
}

/* Writes instruction or data to I/O ports connected to LCD. */
void write(uint8 type, uint8 instruction) {

    //busyWait(10000); 
    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
    uint32 instIO = 0;

    // Set Data/Command pin
    if (type == COMMAND) { // (control data)
        pPIO->PIO_CODR = PA0; // A0 = 0
    } else { // type == DATA (display data)
        pPIO->PIO_SODR = PA0; // A0 = 1
    }

    // Drop chip select to enable data/instruction I/O
    pPIO->PIO_CODR = PXCS;

    // Drop WR and raise RD to prepare the lcd to read on D0-D7 pins
    pPIO->PIO_CODR = PWR;
    pPIO->PIO_SODR = PRD;

    // Rearrange bit order for pPIO
    if (bitRead (instruction, CD0)) { instIO |= PD0; }
    if (bitRead (instruction, CD1)) { instIO |= PD1; }
    if (bitRead (instruction, CD2)) { instIO |= PD2; }
    if (bitRead (instruction, CD3)) { instIO |= PD3; }
    if (bitRead (instruction, CD4)) { instIO |= PD4; }
    if (bitRead (instruction, CD5)) { instIO |= PD5; }
    if (bitRead (instruction, CD6)) { instIO |= PD6; }
    if (bitRead (instruction, CD7)) { instIO |= PD7; }

    // Write data bits to I/O
    pPIO->PIO_CODR = PD;
    pPIO->PIO_SODR = instIO;

    // Raise WR to have LCD latch data on D0-D7 pins
    pPIO->PIO_SODR = PWR;
    pPIO->PIO_CODR = PRD;

    // Raise chip select 
    pPIO->PIO_SODR = PXCS;
}

/* Prepare the display to accept an image. FIXME  CHECK:_Pixel numbering starts from 1_??, and
 * startCol and endCol must divide by 3. 
 * Returns number of (groups of 3) pixels */
uint16 prepDisplay (window_t *window)
{
    write (COMMAND, EXTIN); // ext = 0
    write (COMMAND, CASET); // column address set
    write (DATA, (window->startCol/3)); // from col 0xn FIXME I don't think this is right.
    write (DATA, (window->endCol/3)-1); // to col (0xn/3)-1
    write (COMMAND, LASET); // line address set
    write (DATA, window->startRow-1); // from line 0
    write (DATA, window->endRow-1); // to line 159
    write (COMMAND, RAMWR); // enter memory write mode

    uint16 pixels = ((window->endCol-window->startCol)/3)*
        (window->endRow-window->startRow);
    return pixels;
}

void eraseDisplay (void)
{
    // Prepare a window covering entire display
    window_t window;
    window.startCol = 0;
    window.endCol = 240;
    window.startRow = 0;
    window.endRow = 160;
    uint16 pix = prepDisplay(&window);

    // Replace each pixel with WHITE.
    // nb: 3 pixels per column
    while (pix--)
    {
        write (DATA, WHITE);
        write (DATA, WHITE);
        write (DATA, WHITE);
    }
}

