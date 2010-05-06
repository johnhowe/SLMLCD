# Makefile for AT91SAM7 hello world example. 
# Wolfgang Wieser 07/2007. 

OBJECTS = crt.o	main.o
LDSCRIPT = ld_flash.cmd

# -mthumb-interwork
CFLAGS  = -I. -c -fno-common -O2 -g
AFLAGS  = -ahls -mapcs-32
LFLAGS  = -Map main.map -nostartfiles -T $(LDSCRIPT)

CC = arm-elf-gcc
LD = arm-elf-ld -v
AS = arm-elf-as
OBJCPY = arm-elf-objcopy
OBJDMP = arm-elf-objdump

CPFLAGS = --output-target=binary
ODFLAGS	= -x --syms

OPENOCD = openocd

all: main.bin

clean:
	-rm -f $(OBJECTS) crt.lst main.lst main.elf main.bin main.map main.dmp
	-rm -f flash.bin

flash: main.bin
	$(OPENOCD) -f openocd-flash.cfg
	-cmp main.bin flash.bin

debug: main.elf
	$(OPENOCD) -f openocd.cfg

dist:
	tar -c *.h *.c *.s Makefile *.cmd *.cfg openocd_doflash | gzip > minimal_hello_world.tar.gz

main.bin: main.elf 
	$(OBJCPY) $(CPFLAGS) main.elf main.bin
	$(OBJDMP) $(ODFLAGS) main.elf > main.dmp
	ls -l main.elf main.bin

main.elf: $(OBJECTS) $(LDSCRIPT)
	@ echo "..linking"
	$(LD) $(LFLAGS) -o main.elf $(OBJECTS)

crt.o: crt.s
	$(AS) $(AFLAGS) crt.s -o crt.o > crt.lst

main.o: main.c
	$(CC) $(CFLAGS) main.c
