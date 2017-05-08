call Build.bat
bash -c "cp kernel/bin/kernel.elf isodir/boot/kernel.elf"
bash -c "grub-mkrescue -o mos.iso isodir"
pause