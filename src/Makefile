##############################################################################################
#
#       !!!! Do NOT edit this makefile with an editor which replace tabs by spaces !!!!    
#
##############################################################################################
# 
# On command line:
#
# make all = Create PROJECT
#
# make clean = Clean PROJECT files.
#
# To rebuild PROJECT do "make clean" and "make all".
#

##############################################################################################
# Start of default section
#

TRGT = arm-elf-
CC   = $(TRGT)gcc
LD   = $(TRGT)ld -v
CP   = $(TRGT)objcopy --output-target=binary
DMP  = $(TRGT)objdump -x -S -t
AS   = $(TRGT)gcc -x assembler-with-cpp
BIN  = $(CP) -O ihex 

MCU  = arm7tdmi

# List all default ASM defines here, like -D_DEBUG=1
DADEFS = 

# List the default directory to look for the libraries here
DLIBDIR = ../libs

# List all default libraries here
DLIBS = 

#
# End of default section
##############################################################################################

##############################################################################################
# Start of user section
#

# Define PROJECT name here (the main C file without extension)
PROJECT = main

# Define linker script file here
#LDSCRIPT= AT91SAM7S256-ROM.ld
LDSCRIPT = ../runtime/ld_flash.cmd

# List all user C define here, like -D_DEBUG=1
UDEFS = 

# Define ASM defines here
UADEFS = 

# List additional C source files here
SRC  = $(PROJECT).c init.c lcd.c

# List ASM source files here
ASRC = ../runtime/crt.s

# List all user directories here
UINCDIR = ../include

# List the user directory to look for the libraries here
ULIBDIR =

# Define optimisation level here [0, 1, 2, 3, s]. 
# 0 = turn off optimization. s = optimize for size.
OPT = -O3

#
# End of user defines
##############################################################################################


INCDIR  = $(patsubst %,-I%,$(UINCDIR))
LIBDIR  = $(patsubst %,-L%,$(ULIBDIR))
ADEFS   = $(DADEFS) $(UADEFS)
OBJS    = $(ASRC:.s=.o) $(SRC:.c=.o)
MCFLAGS = -mcpu=$(MCU)

ASFLAGS = $(MCFLAGS) -g -gdwarf-2 -Wa,-amhls=$(<:.s=.lst) $(ADEFS)
CPFLAGS = -fno-common -g -std=gnu99
#LDFLAGS = $(MCFLAGS) -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(PROJECT).map,--cref,--no-warn-mismatch $(LIBDIR)
LDFLAGS = -Map main.map -nostartfiles -T $(LDSCRIPT)

# Generate dependency information
CPFLAGS += -MD -MP -MF .dep/$(@F).d

#
# makefile rules
#

all: $(OBJS) $(PROJECT).elf $(PROJECT).hex $(PROJECT).bin 

%o : %c
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

%o : %s
	$(AS) -c $(ASFLAGS) $< -o $@

%elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $(PROJECT).elf $(OBJS)

%hex: %elf
	$(BIN) $< $@

%bin: %elf
	$(CP) --output-target=binary $< $@
	$(DMP) $< > $(PROJECT).dmp
	

clean:
	#-rm -f $(SRC:.c=.s)
	-rm -f $(SRC:.c=.o)
	-rm -f $(SRC:.c=.lst)
	-rm -f $(ASRC:.s=.lst)
	-rm -f $(ASRC:.s=.o)
	-rm -f $(PROJECT).elf
	-rm -f $(PROJECT).map
	-rm -f $(PROJECT).hex
	-rm -f $(PROJECT).dmp
	-rm -f $(PROJECT).bin
	-rm -fR .dep

install:
	./flash.sh

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
