
#Build mode. m=d => Debug | m=t => Test | m=r => release | default => release
ifeq ($(m), d)
	NASBUILD = $(NASDEBUG)
	GASBUILD = $(GASDEBUG)
	CPPBUILD = $(CPPDEBUG)
	CBUILD = $(CDEBUG)
	export NASBUILD
	export GASBUILD
	export CPPBUILD
	export CBUILD
else ifeq ($(m), t)
	NASBUILD = $(NASTEST)
	GASBUILD = $(GASTEST)
	CPPBUILD = $(CPPTEST)
	CBUILD = $(CTEST)
	export NASBUILD
	export GASBUILD
	export CPPBUILD
	export CBUILD
else ifeq ($(m), r)
	NASBUILD = $(NASRELEASE)
	GASBUILD = $(GASRELEASE)
	CPPBUILD = $(CPPRELEASE)
	CBUILD = $(CRELEASE)
	export NASBUILD
	export GASBUILD
	export CPPBUILD
	export CBUILD
else
	NASBUILD = $(NASRELEASE)
	GASBUILD = $(GASRELEASE)
	CPPBUILD = $(CPPRELEASE)
	CBUILD = $(CRELEASE)
	export NASBUILD
	export GASBUILD
	export CPPBUILD
	export CBUILD
endif

SYSDIR = system
USRDIR = userland

SYSBINDIR = $(SYSDIR)/bin
USRBINDIR = $(USRDIR)/bin

FSYSMODULES = $(shell find $(SYSDIR)/ -maxdepth 1 -type d)
FUSRMODULES = $(shell find $(USRDIR)/ -maxdepth 1 -type d)

RSYSMODULES = $(patsubst $(SYSDIR)/%,%,$(FSYSMODULES))
RUSRMODULES = $(patsubst $(USRDIR)/%,%,$(FUSRMODULES))

SYSMODULES = $(filter-out bin,$(RSYSMODULES))
USRMODULES = $(filter-out bin,$(RUSRMODULES))

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

MODULES = libs $(SYSDIR) $(USRDIR)

.PHONY: all clean mount run $(MODULES) $(SYSMODULES) $(USRMODULES)

all: $(MODULES)

$(MODULES):
	rm -r -f Debug
	$(MAKE) -C $@
	
$(SYSMODULES):
	rm -r -f Debug
	$(MAKE) -C $(SYSDIR)/$@
	@cp -R $(SYSDIR)/$@/bin $(SYSDIR)
	
$(USRMODULES):
	rm -r -f Debug
	$(MAKE) -C $(USRDIR)/$@
	@cp -R $(USRDIR)/$@/bin $(USRDIR)

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(module) clean;)
	
mount:
	rm isodir/mos.iso
	cp -a $(SYSBINDIR)/. isodir/boot/
	cp -a $(USRBINDIR)/. isodir/userland/
	cp grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o isodir/mos.iso isodir
	./Multiboot.sh

run:
	export DISPLAY=:0
	qemu-system-x86_64 -cdrom isodir/mos.iso -cpu Haswell