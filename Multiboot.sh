#!/bin/bash
grub-file --is-x86-multiboot "${PWD}/system/kernel/bin/kernel.elf"
if [ $? == 0 ]
then
echo "Multiboot confirmed!"
else
echo "The file is not multiboot(1) capable"
fi
grub-file --is-x86-multiboot2 "${PWD}/system/kernel/bin/kernel.elf"
if [ $? == 0 ]
then
echo "Multiboot2 confirmed!"
else
echo "The file is not multiboot2 capable"
fi
echo ""
