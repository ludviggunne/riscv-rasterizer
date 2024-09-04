PROGRAM_PREFIX	= riscv64-linux-gnu-
CC 		= $(PROGRAM_PREFIX)gcc
OBJDUMP		= $(PROGRAM_PREFIX)objdump
MACHFLAGS	= -mabi=ilp32 -march=rv32imzicsr
ASFLAGS		= $(MACHFLAGS)
CFLAGS		= $(MACHFLAGS) -Og -g -Wall

qmath_host: PROGRAM_PREFIX =
qmath_host: MACHFLAGS =

.PHONY: all clean run

all: qmath_host

run: all
	./qmath_host

clean:
	rm -f qmath_host

qmath_host: qmath.c main.c
	$(CC) -o $(@) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(^) -lm
