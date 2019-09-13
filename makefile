
#Build mode. m=d => Debug | m=t => Test | m=r => release | default => release
ifeq ($(m), d)
	NASBUILD = $(NASDEBUG)
	GASBUILD = $(GASDEBUG)
	CPPBUILD = $(CPPDEBUG)
	CBUILD = $(CDEBUG)
else ifeq ($(m), t)
	NASBUILD = $(NASTEST)
	GASBUILD = $(GASTEST)
	CPPBUILD = $(CPPTEST)
	CBUILD = $(CTEST)
else ifeq ($(m), r)
	NASBUILD = $(NASRELEASE)
	GASBUILD = $(GASRELEASE)
	CPPBUILD = $(CPPRELEASE)
	CBUILD = $(CRELEASE)
else
	NASBUILD = $(NASRELEASE)
	GASBUILD = $(GASRELEASE)
	CPPBUILD = $(CPPRELEASE)
	CBUILD = $(CRELEASE)
endif

export NASBUILD
export GASBUILD
export CPPBUILD
export CBUILD

SYSDIR = system
USRDIR = userland
LIBDIR = libs
IGNDIR = bin obj

SYSBINDIR = $(SYSDIR)/bin
USRBINDIR = $(USRDIR)/bin
LIBBINDIR = $(LIBDIR)/bin

FSYSMODULES = $(shell find $(SYSDIR)/ -maxdepth 1 -type d)
FUSRMODULES = $(shell find $(USRDIR)/ -maxdepth 1 -type d)
FLIBMODULES = $(shell find $(LIBDIR)/ -maxdepth 1 -type d)

RSYSMODULES = $(patsubst $(SYSDIR)/%,%,$(FSYSMODULES))
RUSRMODULES = $(patsubst $(USRDIR)/%,%,$(FUSRMODULES))
RLIBMODULES = $(patsubst $(LIBDIR)/%,%,$(FLIBMODULES))

SYSMODULES = $(filter-out $(IGNDIR),$(RSYSMODULES))
USRMODULES = $(filter-out $(IGNDIR),$(RUSRMODULES))
LIBMODULES = $(filter-out $(IGNDIR),$(RLIBMODULES))

SYSBINS = $(patsubst %,%.elf,$(SYSMODULES))
USRBINS = $(patsubst %,%.elf,$(USRMODULES))

NASDEBUG = -F dwarf -g
GASDEBUG = 
CPPDEBUG = -gdwarf -Og
CDEBUG = -gdwarf -Og

NASTEST = -F dwarf -g
GASTEST = 
CPPTEST = -gdwarf -O2
CTEST = -gdwarf -O2

NASRELEASE = 
GASRELEASE = 
CPPRELEASE = -O3
CRELEASE = -O3

MODULES = $(SYSDIR) $(USRDIR) $(LIBDIR)

.PHONY: all clean mount run $(MODULES) $(SYSMODULES) $(USRMODULES) $(LIBMODULES)

all: $(MODULES)

$(MODULES):
	rm -r -f Debug
	$(MAKE) -C $@
	
$(SYSMODULES):
	rm -r -f Debug
	rm -r -f $(SYSDIR)/obj
	$(MAKE) -C $(SYSDIR)/$@
	@cp -R $(SYSDIR)/$@/bin $(SYSDIR)
	
$(USRMODULES):
	rm -r -f Debug
	rm -r -f $(USRDIR)/obj
	$(MAKE) -C $(USRDIR)/$@
	@cp -R $(USRDIR)/$@/bin $(USRDIR)
	
$(LIBMODULES):
	rm -r -f Debug
	rm -r -f $(LIBDIR)/obj
	$(MAKE) -C $(LIBDIR)/$@
	@cp -R $(LIBDIR)/$@/bin $(LIBDIR)

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(module) clean;)
	
mount:
	rm -f iso_out/mos.iso
	cp -a $(SYSBINDIR)/. iso_source/boot/
	cp -a $(USRBINDIR)/. iso_source/userland/
	cp grub/grub.cfg iso_source/boot/grub/grub.cfg
	grub-mkrescue -o iso_out/mos.iso iso_source
	./Multiboot.sh

run:
	qemu-system-x86_64 -cdrom iso_out/mos.iso -cpu Haswell
