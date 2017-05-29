# MOS
Modern Operating System (not a final name)

`[Description = Empty]`


To build MOS, you'll either need Linux or the WSL on Windows, GCC 7.1.0 and binutils >=2.28 as a x86-64-elf crosscompiler and NASM.

You'll also need to add the bin/ folder of your crosscompiler to the PATHS variable in `/etc/environment` and `~/.bashrc`.

To make sure you installed everything correctly, try to run `x86_64-elf-gcc --version`, `x86_64-elf-g++ --version` and `x86_64-elf-as --version`.

For a description on how to build a crosscompiler, see http://wiki.osdev.org/GCC_Cross-Compiler

Note: It is important that you have at least GCC 7.1.0. MOS uses GCC features that are only available since GCC 7.1.0 (for example `__attribute__((interrupt))`


TODO: APCI, Memory Management, new and delete Operator, MOSLib with Convert and String class;
