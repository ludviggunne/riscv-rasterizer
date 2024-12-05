# By: Tommy Bergman
BUILDDIR	= build/

.PHONY: all clean

all: all-models all-host all-dtekv

clean:
	rm -rf $(BUILDDIR)

.PHONY: all-models clean-models all-host clean-host all-dtekv clean-dtekv

all-models:
	$(MAKE) -f Makefile.models all

clean-models:
	$(MAKE) -f Makefile.models clean

all-host:
	$(MAKE) -f Makefile.host all

clean-host:
	$(MAKE) -f Makefile.host clean

all-dtekv: all-models
	$(MAKE) -f Makefile.dtekv all

clean-dtekv:
	$(MAKE) -f Makefile.dtekv clean
