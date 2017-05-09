TARGET = kernel.elf
ARCH = x86_64-elf

CC = $(ARCH)-gcc
ASM = nasm
LD = $(ARCH)-ld

SRCDIR = src
OBJDIR = obj
BINDIR = bin

INCFLAGS = -I include/
FFLAGS = -fno-use-cxa-atexit -fno-builtin -fno-leading-underscore -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti 
64FLAGS = -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2

SRCS_c = $(wildcard $(SRCDIR)/*.c)
SRCS_cpp = $(wildcard $(SRCDIR)/*.cpp)
SRCS_S = $(wildcard $(SRCDIR)/*.S)
SRCS_ASM = $(wildcard $(SRCDIR)/*.asm)
OBJS = $(SRCS_c:$(SRCDIR)/%.c=$(OBJDIR)/%_c.o) $(SRCS_cpp:$(SRCDIR)/%.cpp=$(OBJDIR)/%_cpp.o) $(SRCS_S:$(SRCDIR)/%.S=$(OBJDIR)/%_S.o) $(SRCS_ASM:$(SRCDIR)/%.asm=$(OBJDIR)/%_asm.o)
rm = rm -f

ASFLAGS = -f elf64
GASFLAGS = -m64
CFLAGS = -m64 $(64FLAGS) $(INCFLAGS) $(FFLAGS) -pedantic-errors -g -O2 -Wall -Wextra -nostdinc -nostdlib -lgcc
LDFLAGS = -T linker.ld -O2 -z max-page-size=0x1000 -nostdlib

$(BINDIR)/$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%_c.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/%_cpp.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%_S.o : $(SRCDIR)/%.S
	$(CC) $(ASFLAGS) -c $< -o $@
	
$(OBJDIR)/%_asm.o : $(SRCDIR)/%.asm
	$(ASM) $(ASFLAGS) $< -o $@

.PHONY: clean
clean:
	$(rm) $(OBJS)
	
.PHONY: remove
remove:
	$(rm) $(BINDIR)/$(TARGET)