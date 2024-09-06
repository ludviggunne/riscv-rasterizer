PROGRAM_PREFIX	= riscv64-linux-gnu-
CC 		= $(PROGRAM_PREFIX)gcc
OBJDUMP		= $(PROGRAM_PREFIX)objdump
OBJCOPY		= $(PROGRAM_PREFIX)objcopy
MACHFLAGS	= -mabi=ilp32 -march=rv32imzicsr
ASFLAGS		= $(MACHFLAGS)
CFLAGS		= $(MACHFLAGS) -fno-pic -Os -g -Wall
LDSCRIPT	= link.ld
LDFLAGS		= -T $(LDSCRIPT) -nostdlib -Wl,-no-pie,--build-id=none
LDLIBS		=

.PHONY: all clean all-host clean-host

all: rast.bin all-host

clean: clean-host
	rm -f rast.elf rast.bin
	$(MAKE) -f Makefile.host $(@)

rast.elf: display.c main.c mvec.S qmath.c reset.S stack.S start.S stop.S trap.S
	$(CC) -o $(@) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(^) $(LDLIBS)

rast.bin: rast.elf
	$(OBJCOPY) -S -O binary $(<) $(@)

all-host:
	$(MAKE) -f Makefile.host all

clean-host:
	$(MAKE) -f Makefile.host clean

rast_host tri2c:
	$(MAKE) -f Makefile.host $(@)
