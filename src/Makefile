# File:   Makefile
# Author: M. P. Hayes, ICES
# Date:   31 December 2007
# Descr:  Makefile for busart0_loop


## Create ROM-Image (final)
RUN_MODE=ROM_RUN
## Create RAM-Image (debugging) 
#RUN_MODE=RAM_RUN


SRC = busart0_loop1.c busart.c ring.c usart0.c usart1.c

VPATH = ./mmculib ./mat91lib


CC = arm-elf-gcc
OBJCOPY = arm-elf-objcopy
SIZE = arm-elf-size
DEL = rm


CFLAGS = -mcpu=arm7tdmi -Wall -Wstrict-prototypes -W -gdwarf-2 -std=c99 -D$(RUN_MODE) -I./mat91lib -I./mmculib -I./mdsplib -I/usr/include -I. -O2 -mthumb-interwork

LDFLAGS = -mthumb-interwork -nostartfiles -lm -lc

ifeq ($(RUN_MODE),RAM_RUN)
LDFLAGS +=-T../mat91lib/ldscripts/AT91SAM7S256-RAM.ld
else 
LDFLAGS +=-T../mat91lib/ldscripts/AT91SAM7S256-ROM.ld
endif


# Default target.
all: busart0_loop1.bin


OBJ = $(SRC:.c=.o)


#busart0_loop1.lst: busart0_loop1.c config.h target.h
#	$(CC) -c  $(CFLAGS) -mthumb $< -o /dev/null  -Wa,-adhlns=$@


%.o: %.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

# Automatically generate C source code dependencies.
%.d: %.c
	set -e; $(CC) -MM $(CFLAGS) $< \
	| sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; \
	[ -s $@ ] || rm -f $@

# Include the dependency files.
-include $(SRC:.c=.d)


# This cannot be compiled in thumb mode.
crt0.o: crt0.c config.h target.h
	$(CC) -c $(CFLAGS) -O2 $< -o $@


# Link object files to form output file.
busart0_loop1.out: $(OBJ) crt0.o
	$(CC) $^ $(LDFLAGS) -o $@ -lm
	$(SIZE) $@


# Convert output file to binary image file.
%.bin: %.out
	$(OBJCOPY) --output-target=binary $^ $@


# Remove non-source files.
.PHONY: clean
clean: 
	$(DEL) *.o *.out *.hex *.bin *.elf *.d

