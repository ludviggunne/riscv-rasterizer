BUILDDIR	= build/

.PHONY: all clean

all: all-common all-host all-target

clean:
	rm -rf $(BUILDDIR)

.PHONY: all-common all-host all-target

all-common:
	$(MAKE) -f Makefile.common all

all-host: all-common
	$(MAKE) -f Makefile.host all

all-target: all-common
	$(MAKE) -f Makefile.target all
