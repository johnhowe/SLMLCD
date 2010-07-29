/*
 * lcd.c
 *
 * Functions for communicating with LCD module
 *
 * John Howe 2010
 */

#include "lcd.h"

/* Init function taken from datasheet */
void initLCD(void) {

    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;

    // Enable PIO in output mode
    pPIO->PIO_PER = PA0 | PWR | PRD | PXCS | PRST | PD;
    pPIO->PIO_OER = PA0 | PWR | PRD | PXCS | PRST | PD;

    // Set all pins LOW
    pPIO->PIO_CODR = PA0 | PWR | PRD | PXCS | PRST | PD;

    busyWait(10000); // 10ms
    write(COMMAND, EXTIN);
    write(COMMAND, SLPOUT);
    write(COMMAND, OSCON);
    write(COMMAND, PWRCTR);
    write(DATA, 0x08); // booster must be on first
    busyWait(1000); // wait one millisecond
    write(COMMAND, PWRCTR);
    write(DATA, 0x0b); // booster, regulator, follower on
    write(COMMAND, VOLCTR);
    write(DATA, 0x32); // DL38
    write(DATA, 0x04); // DH,Vop = 15.5v, normal display
    write(COMMAND, DISCTL);
    write(DATA, 0x04); // CLD = 0, not divide
    write(DATA, 0x27); // 1/160 duty 39
    write(DATA, 0x00); // FR
    write(COMMAND, DISINV);
    write(COMMAND, COMSCN);
    write(DATA, 0x01); // 0->79 159->80
    write(COMMAND, DATSDR);
    write(DATA, 0x00); // normal
    write(DATA, 0x00); // RGB arrangement
    write(DATA, 0x02); // 32 gray-scale 3byte 3pixel mode
    write(COMMAND, LASET);
    write(DATA, 0x00); // start line = 0
    write(DATA, 0x9f); // end line = 159
    write(COMMAND, CASET);
    write(DATA, 0x00); // start column = 0
    write(DATA, 0xf4); // end column = 79 -> (79+1)*3=240

    write(COMMAND, EXTOUT);
    write(COMMAND, ANASET);
    write(DATA, 0x07); // oscillator frequency = 12.7KHz
    write(DATA, 0x02); // Booter frequency = 6KHz
    write(DATA, 0x03); // bias = 1/11
    write(COMMAND, SWINT);
    write(COMMAND, EXTIN);
    write(COMMAND, DISON);
    busyWait(10000); // 10ms
}

/* Writes instruction or data to I/O ports connected to LCD. */
void write(uint8 type, uint8 instruction) {

    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;

    // Set Data/Command pin
    if (type) { // type == COMMAND
        pPIO->PIO_CODR = PA0;
    } else { // type == DATA
        pPIO->PIO_SODR = PA0;
    }

    // Drop chip select to enable data/instruction I/O
    pPIO->PIO_CODR = PXCS;

    // Drop WR and raise RD to prepare the lcd to read on D0-D7 pins
    pPIO->PIO_CODR = PWR;
    pPIO->PIO_SODR = PRD;

    //TODO: Improve speed of this section
    if (bitRead(instruction,CD0)) { pPIO->PIO_SODR|=PD0; } 
    else { pPIO->PIO_CODR|=PD0; }
    if (bitRead(instruction,CD1)) { pPIO->PIO_SODR|=PD1; } 
    else { pPIO->PIO_CODR|=PD1; }
    if (bitRead(instruction,CD2)) { pPIO->PIO_SODR|=PD2; } 
    else { pPIO->PIO_CODR|=PD2; }
    if (bitRead(instruction,CD3)) { pPIO->PIO_SODR|=PD3; } 
    else { pPIO->PIO_CODR|=PD3; }
    if (bitRead(instruction,CD4)) { pPIO->PIO_SODR|=PD4; } 
    else { pPIO->PIO_CODR|=PD4; }
    if (bitRead(instruction,CD5)) { pPIO->PIO_SODR|=PD5; } 
    else { pPIO->PIO_CODR|=PD5; }
    if (bitRead(instruction,CD6)) { pPIO->PIO_SODR|=PD6; } 
    else { pPIO->PIO_CODR|=PD6; }
    if (bitRead(instruction,CD7)) { pPIO->PIO_SODR|=PD7; } 
    else { pPIO->PIO_CODR|=PD7; }

    // Raise WR to have LCD latch data on D0-D7 pins
    pPIO->PIO_SODR = PWR;

    // Raise chip select 
    pPIO->PIO_SODR = PXCS;
}

/* Write unstructured data to LCD */
void testDisplay(void) {


    write (COMMAND, EXTIN); // ext = 0
    write (COMMAND, CASET); // column address set
    write (DATA, 10); // from col 0
    write (DATA, 20); // to col 240 (240/3)-1
    write (COMMAND, LASET); // line address set
    write (DATA, 10); // from line 0
    write (DATA, 20); // to line 159
    write (COMMAND, RAMWR); // enter memory write mode
    uint8 j;
    for (j=0; j<100; j++) {
        write (DATA, BLACK);
    }
}

void testWrite(void) {
    write (COMMAND, 0x00); // ext = 0
    write (DATA, 0xff);
}
