#!/bin/bash
grub-file --is-x86-multiboot /mnt/d/Coding/OSDev/MOS/system/kernel/bin/kernel.elf
if [ $? == 0 ]
then
echo "Multiboot confirmed!"
else
echo "The file is not multiboot(1) capable"
fi
grub-file --is-x86-multiboot2 /mnt/d/Coding/OSDev/MOS/system/kernel/bin/kernel.elf
if [ $? == 0 ]
then
echo "Multiboot2 confirmed!"
else
echo "The file is not multiboot2 capable"
fi
echo ""