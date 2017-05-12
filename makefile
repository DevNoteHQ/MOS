
SYSDIR := system
USRDIR := userland

SYSBINDIR := $(SYSDIR)/bin
USRBINDIR := $(USRDIR)/bin

SYSMODULE := kernel
USRMODULE := 

SYSBINS := $(patsubst %,%.elf,$(SYSMODULE))
USRBINS := $(patsubst %,%.elf,$(USRMODULE))

SYSMODULES := $(SYSDIR)/$(SYSMODULES)
USRMODULES := $(USRDIR)/$(USRMODULES)

MODULES := libs $(SYSDIR) $(USRDIR)

.PHONY: all clean libs mount $(MODULES) $(SYSMODULES) $(USRMODULES)

all: $(MODULES)

$(MODULES):
	rm -r -f Debug
	$(MAKE) -C $@
	
$(SYSMODULES):
	rm -r -f Debug
	$(MAKE) -C $@
	
$(USRMODULES):
	rm -r -f Debug
	$(MAKE) -C $@

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(module) clean;)
	
mount:
	rm isodir/mos.iso
	cp -a $(SYSBINDIR)/. isodir/boot/
	cp -a $(USRBINDIR)/. isodir/userland/
	cp grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o isodir/mos.iso isodir
	./Multiboot.sh
