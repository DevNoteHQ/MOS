#!/bin/bash
grub-file --is-x86-multiboot /mnt/d/Coding/OSDev/MOS/kernel/bin/kernel.elf
if [ $? == 0 ]
then
echo "multiboot confirmed"
else
echo "the file is not multiboot"
fi
grub-file --is-x86-multiboot2 /mnt/d/Coding/OSDev/MOS/kernel/bin/kernel.elf
if [ $? == 0 ]
then
echo "multiboot2 confirmed"
else
echo "the file is not multiboot2"
fi