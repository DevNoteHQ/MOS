CurDir = $(shell pwd)
DirBelow = $(shell cd ../ && pwd)
CutPath = $(patsubst $(DirBelow)/%,%,$(CurDir))
TARGET = $(patsubst %,%.elf,$(CutPath))
ARCH = x86_64-elf

CC = $(ARCH)-gcc
CPP = $(ARCH)-g++
ASM = nasm
LD = $(ARCH)-ld

SRCDIR = src
OBJDIR = obj
BINDIR = bin
DEPDIR = dep

INCPATHSNP = $(SRCDIR) ../../include
INCPATHS = $(addprefix -I ,$(INCPATHSNP))
STDINCLUDES = stddef.h stdint.h
MOSINCLUDES = string.hpp types.hpp assembler.hpp abort.hpp
INCLUDES = $(STDINCLUDES) $(MOSINCLUDES)
INCLUDE = $(addprefix -include ,$(INCLUDES))

CINCFLAGS = $(INCPATHS) $(INCLUDE)
CFFLAGS = -ffreestanding -fno-stack-protector -fno-builtin
C64FLAGS = -mcmodel=kernel -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow
CWFLAGS = -Wall -Wextra -Wno-unused-parameter

CPPINCFLAGS = $(INCPATHS) $(INCLUDE)
CPPFFLAGS = -ffreestanding -fno-stack-protector -fno-builtin -fpermissive -fno-rtti -fno-exceptions
CPP64FLAGS = -mcmodel=kernel -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow
CPPWFLAGS = -Wall -Wextra -Wno-unused-parameter

INTRFLAGS = -mgeneral-regs-only

NASFLAGS = -f elf64
GASFLAGS = 
CPPFLAGS = -m64 $(CPP64FLAGS) $(CPPINCFLAGS) $(CPPFFLAGS) $(CPPWFLAGS) -std=gnu++14 -O2 -nostdlib -nostartfiles -lgcc
CFLAGS = -m64 $(C64FLAGS) $(CINCFLAGS) $(CFFLAGS) $(CWFLAGS) -std=gnu11 -O2 -nostdlib -nostartfiles -lgcc
LDFLAGS = -T linker.ld -O2 -z max-page-size=0x1000

SRCS_c = $(shell find $(SRCDIR)/* -name '*.c')
SRCS_cpp = $(shell find $(SRCDIR)/* -name '*.cpp')
SRCS_cpp := $(filter-out %_isr.cpp,$(SRCS_cpp))
SRCS_cpp_isr = $(shell find $(SRCDIR)/* -name '*_isr.cpp')
SRCS_S = $(shell find $(SRCDIR)/* -name '*.S')
SRCS_asm = $(shell find $(SRCDIR)/* -name '*.asm')

OBJS_c = $(addprefix $(OBJDIR)/,$(SRCS_c:$(SRCDIR)/%.c=%_c.o))
OBJS_cpp = $(addprefix $(OBJDIR)/,$(SRCS_cpp:$(SRCDIR)/%.cpp=%_cpp.o))
OBJS_cpp_isr = $(addprefix $(OBJDIR)/,$(SRCS_cpp_isr:$(SRCDIR)/%_isr.cpp=%_isr_cpp.o))
OBJS_S = $(addprefix $(OBJDIR)/,$(SRCS_S:$(SRCDIR)/%.S=%_S.o))
OBJS_asm = $(addprefix $(OBJDIR)/,$(SRCS_asm:$(SRCDIR)/%.asm=%_asm.o))

OBJS = $(OBJS_c) $(OBJS_cpp) $(OBJS_cpp_isr) $(OBJS_S) $(OBJS_asm)
rm = rm -f -r
mk = mkdir -p

$(BINDIR)/$(TARGET): $(OBJS)
	$(mk) $(@D)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%_c.o : $(SRCDIR)/%.c
	$(mk) $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/%_cpp.o : $(SRCDIR)/%.cpp
	$(mk) $(@D)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/%_isr_cpp.o : $(SRCDIR)/%_isr.cpp
	$(mk) $(@D)
	$(CPP) $(CPPFLAGS) $(INTRFLAGS) -c $< -o $@

$(OBJDIR)/%_S.o : $(SRCDIR)/%.S
	$(mk) $(@D)
	$(CC) $(GASFLAGS) -c $< -o $@
	
$(OBJDIR)/%_asm.o : $(SRCDIR)/%.asm
	$(mk) $(@D)
	$(ASM) $(NASFLAGS) $< -o $@

.PHONY: clean
clean:
	$(rm) $(OBJS)
	$(rm) $(OBJDIR)
	$(mk) $(OBJDIR)