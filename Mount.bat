call Build.bat
bash -c "cp kernel/bin/kernel.elf isodir/boot/kernel.elf && cp grub/grub.cfg isodir/boot/grub/grub.cfg"
bash -c "grub-mkrescue -o mos.iso isodir"
pause