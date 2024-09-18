TARGET_TOOLS	= riscv32-unknown-elf- riscv64-unknown-elf- riscv64-linux-gnu-
PROGRAM_PREFIX	:= $(shell for i in $(TARGET_TOOLS); do if which $${i}gcc >/dev/null 2>&1; then echo $${i}; break; fi done)
CC 		= $(PROGRAM_PREFIX)gcc
OBJDUMP		= $(PROGRAM_PREFIX)objdump
OBJCOPY		= $(PROGRAM_PREFIX)objcopy
MACHFLAGS	= -mabi=ilp32 -march=rv32imzicsr
ASFLAGS		= $(MACHFLAGS)
CFLAGS		= $(MACHFLAGS) -fno-pic -g -Wall -O3 -flto -fuse-linker-plugin
LDSCRIPT	= link.ld
LDFLAGS		= -T $(LDSCRIPT) -L. -nostdlib -Wl,-no-pie,--build-id=none,--no-warn-rwx-segments
LDLIBS		= -ldtekv

.PHONY: all clean all-host clean-host

all: rast.bin all-host

clean: clean-host
	rm -f rast.elf rast.bin
	$(MAKE) -f Makefile.host $(@)

rast.elf: display.c main.c mvec.S qmath.c reset.S stack.S start.S stop.S trap.S uart.c vmath.c
	$(CC) -o $(@) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(^) $(LDLIBS)

rast.bin: rast.elf
	$(OBJCOPY) -S -O binary $(<) $(@)

all-host:
	$(MAKE) -f Makefile.host all

clean-host:
	$(MAKE) -f Makefile.host clean

.PHONY: rast_host tri2c

rast_host tri2c obj2c:
	$(MAKE) -f Makefile.host $(@)
