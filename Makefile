BUILDDIR	= build/

.PHONY: all clean

all: all-common all-host all-dtekv all-avr

clean:
	rm -rf $(BUILDDIR)

.PHONY: all-common clean-common all-host clean-host all-dtekv clean-dtekv all-avr clean-avr flash-avr

all-common:
	$(MAKE) -f Makefile.common all

clean-common:
	$(MAKE) -f Makefile.common clean

all-host: all-common
	$(MAKE) -f Makefile.host all

clean-host:
	$(MAKE) -f Makefile.host clean

all-dtekv: all-common
	$(MAKE) -f Makefile.dtekv all

clean-dtekv:
	$(MAKE) -f Makefile.dtekv clean

all-avr: all-common
	$(MAKE) -f Makefile.avr all

clean-avr:
	$(MAKE) -f Makefile.avr clean

flash-avr:
	$(MAKE) -f Makefile.avr flash
