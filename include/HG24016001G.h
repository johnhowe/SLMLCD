/*
 * HG24016001G.h
 *
 *  Definitions for HG24016001G-VB LCD
 *      John Howe	2010
 */


#ifndef HG24016001G_H
#define HG24016001G_H

// Control instructions

// 						Function								Parameter
#define EXTIN	0x30	// Extension instruction disable (Ext = 0)
#define EXTOUT	0x31	// Extension instruction enable (Ext = 1)
// Ext = 0
#define DISON   0xAF    // Display on
#define DISOFF  0xAE    // Display off
#define DISNOR  0xA6    // Normal display
#define DISINV  0xA7    // Inverse display
#define COMSCN  0xBB    // Common scan direction				1 byte
#define DISCTL  0xCA    // Display control						3 bytes
#define SLPIN   0x95    // Sleep in
#define SLPOUT  0x94    // Sleep out
#define LASET   0x75    // Line address set
#define CASET   0x15    // Column address set					2 bytes
#define DATSDR  0xBC    // Data scan direction					2 bytes
#define RGBSET8 0xCE    // 256-color position set				3 bytes
#define RAMWR   0x5C    // Writing to memory					data
#define RAMRD   0x5D    // Reading from memory					data
#define PTLIN   0xA8    // Partial display in					2 bytes
#define PTLOUT  0xA9    // Partial display out
#define RMWIN   0xE0    // Read and modify write
#define RMWOUT  0xEE    // RMW End
#define ASCSET  0xAA    // Area scroll set						4 bytes
#define SCSTART 0xAB    // Scroll start set						1 byte
#define OSCON   0xD1    // Internal oscillation on
#define OSCOFF  0xD2    // Internal oscillation off
#define PWRCTR  0x20    // Power control						1 byte
#define VOLCTR  0x81    // Electronic volume control            2 bytes
#define VOLUP   0xD6    // Increment electronic control by 1
#define VOLDOWN	0xD7    // Decrement electronic control by 1
#define RESERVE 0x82    // Not used
#define EPSRRD1 0x7C    // Read register 1
#define EPSRRD2 0x7D    // Read register 2
#define NOP     0x25    // NOP instruction
#define EPINT	0x07    // Initial code(1)                      1 byte
// Ext = 1
#define GRAY1   0x20    // Frame 1 gray PWM set
#define GRAY2   0x21    // Frame 2 gray PWM set
#define ANASET  0x32    // Analog circuit set
#define SWINT   0x34    // Software initial
#define EPCTIN  0xCD    // Control EEPROM
#define EPCOUT  0xCC    // Cancel EEPROM control
#define EPMWR   0xFC    // Write into EEPROM
#define EPMRD   0xFD    // Read from EEPROM


// Colour definitions for LCD
#define BLACK 		0
#define COLOUR1 	(2<<3)
#define COLOUR2 	(4<<3)
#define COLOUR3 	(6<<3)
#define COLOUR4 	(8<<3)
#define COLOUR5 	(10<<3)
#define COLOUR6 	(12<<3)
#define COLOUR7 	(14<<3)
#define COLOUR8 	(16<<3)
#define COLOUR9 	(18<<3)
#define COLOUR10	(20<<3)
#define COLOUR11	(22<<3)
#define COLOUR12	(24<<3)
#define COLOUR13	(26<<3)
#define COLOUR14 	(28<<3)
#define COLOUR15 	(30<<3)
#define WHITE 		(31<<3) 

#endif
