/*
 * lcd.c
 *
 * Functions for communicating with LCD module
 *
 * John Howe 2010
 */

#include "lcd.h"

uint32 table[256];

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
    write(DATA, 0x00); // 0->79 80->159
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

    write(COMMAND, EXTOUT); // use the ext=1 command table
    write(COMMAND, ANASET); // analog circuit set
    write(DATA, 0x07); // oscillator frequency = 12.7KHz
    write(DATA, 0x02); // Booter frequency = 6KHz
    write(DATA, 0x03); // bias = 1/11
    write(COMMAND, SWINT); // software initial

    write(COMMAND, EXTIN); // use the ext=0 command table
    write(COMMAND, DISON); // turn display on
    busyWait(10000); // 10ms
}

/*
 * Problem is that the data coming in is an 8bit integer and not in the same
 * order as the PIO, so the bits need reordering and placing in their correct
 * locations in a 32 bit integer corresponding to their PIO locations. This is
 * an expensive operation and needs to be executed every time an instruction is
 * sent to the LCD.
 * Instead, this pre-generates a 256 element array corresponding to each
 * possible instruction and its relevant mask on the PIO.
 */
uint32* generateLookupTable () {
    //uint32* table;
    //table = malloc(256 * sizeof(uint32));
    //if (table == NULL) {
        // Malloc failed
        // TODO: flash error code - do not continue.
    //}

    // do-while loop used here as for (i=0;i < 256;i++) would never exit
    uint8 inst = 0;
    do {
        // calculate possible PIO combinations for any data input
        uint32 instIO = 0;

        // Rearrange bit order for pPIO
        if (bitRead (inst, CD0)) { instIO |= PD0; }
        if (bitRead (inst, CD1)) { instIO |= PD1; }
        if (bitRead (inst, CD2)) { instIO |= PD2; }
        if (bitRead (inst, CD3)) { instIO |= PD3; }
        if (bitRead (inst, CD4)) { instIO |= PD4; }
        if (bitRead (inst, CD5)) { instIO |= PD5; }
        if (bitRead (inst, CD6)) { instIO |= PD6; }
        if (bitRead (inst, CD7)) { instIO |= PD7; }

        // store result
        table[inst] = instIO;
        inst++;
    }
    while (inst != 255);

    return table;
}

/* Butler looks after the lookup table. Generating it the first time it is
 * requred, then returning a pointer to it. */

uint32* tableButler (void) {
    static uint8 firstRun = TRUE;
    //static uint32* table;
    if (firstRun) {
        //table = generateLookupTable();
        generateLookupTable();
    }
    return table;
}


/* Writes instruction or data to I/O ports connected to LCD. */
void write(uint8 type, uint8 instruction) {

    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
    //uint32* table = tableButler();

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

    // Write data bits to I/O
    pPIO->PIO_CODR = PD;
    pPIO->PIO_SODR = table[instruction];

    // Raise WR to have LCD latch data on D0-D7 pins
    pPIO->PIO_SODR = PWR;
    pPIO->PIO_CODR = PRD;

    // Raise chip select 
    pPIO->PIO_SODR = PXCS;
}

/* Write unstructured data to LCD */
void testDisplay(void) {


    write (COMMAND, EXTIN); // ext = 0
    write (COMMAND, CASET); // column address set
    write (DATA, 0x00); // from col 0xn
    write (DATA, 0x50); // to col (0xn/3)-1
    write (COMMAND, LASET); // line address set
    write (DATA, 0x00); // from line 0
    write (DATA, 0x9f); // to line 159
    write (COMMAND, RAMWR); // enter memory write mode
    uint8 j;
    for (j=0; j<(0x50*0x9f); j++) {
            write (DATA, BLACK);
            write (DATA, COLOUR7);
            write (DATA, WHITE);
    }
}

void testWrite(void) {
    //write (COMMAND, 0x00); // ext = 0
    write (DATA, WHITE);
}

void volUp(void)
{
    write (COMMAND, EXTIN);
    write (COMMAND, VOLUP);
}

void volDown(void)
{
    write (COMMAND, EXTIN);
    write (COMMAND, VOLDOWN);
}
