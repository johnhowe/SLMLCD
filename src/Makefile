# Makefile for AT91SAM7 hello world example. 
# Wolfgang Wieser 07/2007. 

OBJECTS = crt.o	main.o init.o lcd.o timers.o
LDSCRIPT = ld_flash.cmd

# -mthumb-interwork
CFLAGS  = -I. -c -fno-common -O3 -g -std=gnu99 -Wall
AFLAGS  = -ahls -mapcs-32
LFLAGS  = -Map main.map -nostartfiles -T $(LDSCRIPT)

CC = arm-elf-gcc
LD = arm-elf-ld -v
AS = arm-elf-as
OBJCPY = arm-elf-objcopy
OBJDMP = arm-elf-objdump

CPFLAGS = --output-target=binary
ODFLAGS	= -x -S -t

OPENOCD = openocd

all: clean main.bin

clean:
	-rm -f $(OBJECTS) *.lst *.bin *.elf *.map *.dmp

flash: main.bin
	-sh flash.sh
	
#debug: main.elf
#	$(OPENOCD) -f openocd.cfg

#dist:
#	tar -c *.h *.c *.s Makefile *.cmd *.cfg openocd_doflash | gzip > minimal_hello_world.tar.gz

main.bin: main.elf 
	$(OBJCPY) $(CPFLAGS) main.elf main.bin
	$(OBJDMP) $(ODFLAGS) main.elf > main.dmp
	ls -l main.elf main.bin

main.elf: $(OBJECTS) $(LDSCRIPT)
	@ echo "...linking"
	$(LD) $(LFLAGS) -o main.elf $(OBJECTS)

crt.o: crt.s	# startup scripts for microcontroller
	$(AS) $(AFLAGS) crt.s -o crt.o > crt.lst

main.o: main.c init.o lcd.o config.h
	$(CC) $(CFLAGS) main.c
	
init.o: init.c init.h config.h
	$(CC) $(CFLAGS) init.c
	
lcd.o: lcd.c lcd.h config.h
	$(CC) $(CFLAGS) lcd.c

timers.o: timers.c timers.h config.h
	$(CC) $(CFLAGS) timers.c