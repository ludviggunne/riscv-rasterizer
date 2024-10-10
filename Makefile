BUILDDIR	= build/

.PHONY: all clean

all: all-common all-host all-target all-avr

clean:
	rm -rf $(BUILDDIR)

.PHONY: all-common clean-common all-host clean-host all-target clean-target

all-common:
	$(MAKE) -f Makefile.common all

clean-common:
	$(MAKE) -f Makefile.common clean

all-host: all-common
	$(MAKE) -f Makefile.host all

clean-host:
	$(MAKE) -f Makefile.host clean

all-target: all-common
	$(MAKE) -f Makefile.target all

clean-target:
	$(MAKE) -f Makefile.target clean

all-avr: all-common
	$(MAKE) -f Makefile.avr all

clean-avr:
	$(MAKE) -f Makefile.avr clean

flash-avr:
	$(MAKE) -f Makefile.avr flash
