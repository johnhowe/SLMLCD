OUTFILE_SRAM = slmlcd-sram
OUTFILE_FLASH = slmlcd-flash

INCL = ../include
LDSCRIPT = $(INCL)/at91lib/at91sam7s256/flash.lds
CSTARTUP = $(INCL)/at91lib/board_cstartup.S

OBJS = board_cstartup.o main.o init.o lcd.o timers.o

CFLAGS = -g -mcpu=arm7tdmi -c -O3 -Wall -I$(INCL)
AFLAGS = -D__ASSEMBLY__ -g -mcpu=arm7tdmi -c -Os -Wall -I$(INCL)
LFLAGS = -nostartfiles -Wl,--cerf -lc -lgcc -T $(LDSCRIPT)

CC = arm-elf-gcc
LD = arm-elf-ld -v
AS = arm-elf-as
NM = arm-elf-nm
OBJCPY = arm-elf-objcopy
OBJDMP = arm-elf-objdump
SIZE = arm-elf-size

all: sram flash

sram: $(OBJS)
	$(LD) $(LDFLAGS) -Ttext 0x201000 -Tdata 0x200000 -n -o $(OUTFILE_SRAM).elf $(OBJS)
	$(OBJCOPY) --strip-debug --strip-unneeded $(OUTFILE_SRAM).elf -O binary $(OUTFILE_SRAM).bin

flash: $(OBJS)
	$(LD) $(LDFLAGS) -Ttext 0x100000 -Tdata 0x200000 -n -o $(OUTFILE_FLASH).elf $(OBJS)
	$(OBJCOPY) --strip-debug --strip-unneeded $(OUTFILE_FLASH).elf -O binary $(OUTFILE_FLASH).bin
	
board_cstartup.o: board_cstartup.S
	$(AS) $(ASFLAGS) board_cstartup.S -o board_cstartup.o

main.o: main.c init.o lcd.o config.h
	$(CC) $(CFLAGS) main.c
	
init.o: init.c init.h config.h
	$(CC) $(CFLAGS) init.c
	
lcd.o: lcd.c lcd.h config.h
	$(CC) $(CFLAGS) lcd.c

timers.o: timers.c timers.h config.h
	$(CC) $(CFLAGS) timers.c
	
	
	