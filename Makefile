PROGRAM_PREFIX	= riscv64-linux-gnu-
CC 		= $(PROGRAM_PREFIX)gcc
OBJDUMP		= $(PROGRAM_PREFIX)objdump
MACHFLAGS	= -mabi=ilp32 -march=rv32imzicsr
ASFLAGS		= $(MACHFLAGS)
CFLAGS		= $(MACHFLAGS) -Og -g -Wall

qmath_host: PROGRAM_PREFIX =
qmath_host: MACHFLAGS =
tri2c: PROGRAM_PREFIX =
tri2c: MACHFLAGS =

.PHONY: all clean run

all: qmath_host tri2c

run: all
	./qmath_host

clean:
	rm -f qmath_host tri2c

qmath_host: qmath.c main.c vmath.c
	$(CC) -o $(@) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(^) -lm

tri2c: tri2c.c
	$(CC) -Wall -o $@ $<
