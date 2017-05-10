
MODULES := kernel

.PHONY: all clean libs mount $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) -C $@

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(module) clean;)

libs: libs
	$(MAKE) -C $@
	
mount:
	@echo "cp kernel/bin/kernel.elf isodir/boot/kernel.elf"
	@cp kernel/bin/kernel.elf isodir/boot/kernel.elf
	@echo "cp grub/grub.cfg isodir/boot/grub/grub.cfg"
	@cp grub/grub.cfg isodir/boot/grub/grub.cfg
	@echo "grub-mkrescue -o mos.iso isodir"
	@grub-mkrescue -o mos.iso isodir
	@echo "./Multiboot.sh"
	@./Multiboot.sh
