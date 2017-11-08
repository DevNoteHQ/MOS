CurDir = $(shell pwd)
DirBelow = $(shell cd ../ && pwd)
CutPath = $(patsubst $(DirBelow)/%,%,$(CurDir))
TARGET = $(patsubst %,%.a,$(CutPath))
ARCH = x86_64-elf

CC = $(ARCH)-gcc
CPP = $(ARCH)-g++
AS = $(ARCH)-as
ASM = nasm
LD = $(ARCH)-ld
AR = $(ARCH)-ar

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

INCFLAGS = $(INCPATHS) $(INCLUDE)

FFLAGS = -ffreestanding -fno-exceptions -fno-rtti -fPIC
64FLAGS = -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow
WFLAGS = -pedantic -Wall -Wextra -Wno-unused-parameter

NASFLAGS = -f elf64 $(NASBUILD)
GASFLAGS = $(GASBUILD)
CPPFLAGS = $(CPPBUILD) $(64FLAGS) $(INCFLAGS) $(FFLAGS) $(WFLAGS) -std=gnu++1z -nostdlib -nostartfiles -lgcc
CFLAGS = $(CBUILD) $(64FLAGS) $(INCFLAGS) $(FFLAGS) $(WFLAGS) -std=gnu11 -nostdlib -nostartfiles -lgcc

SRCS_c = $(shell find $(SRCDIR)/* -name '*.c')
SRCS_cpp = $(shell find $(SRCDIR)/* -name '*.cpp')
SRCS_cc = $(shell find $(SRCDIR)/* -name '*.cc')
SRCS_S = $(shell find $(SRCDIR)/* -name '*.S')
SRCS_asm = $(shell find $(SRCDIR)/* -name '*.asm')

OBJS_c = $(addprefix $(OBJDIR)/,$(SRCS_c:$(SRCDIR)/%.c=%_c.o))
OBJS_cc = $(addprefix $(OBJDIR)/,$(SRCS_cc:$(SRCDIR)/%.cc=%_cc.o))
OBJS_cpp = $(addprefix $(OBJDIR)/,$(SRCS_cpp:$(SRCDIR)/%.cpp=%_cpp.o))
OBJS_S = $(addprefix $(OBJDIR)/,$(SRCS_S:$(SRCDIR)/%.S=%_S.o))
OBJS_asm = $(addprefix $(OBJDIR)/,$(SRCS_asm:$(SRCDIR)/%.asm=%_asm.o))

OBJS = $(OBJS_c) $(OBJS_cpp) $(OBJS_S) $(OBJS_asm) $(OBJS_cc)

DEPS =  -MD -MP -MT $@ -MF $(subst obj,dep, $(addsuffix .d,$(basename $@)))

OLDDEPS = $(shell find $(DEPDIR)/* -name '*.d')

rm = rm -f -r
mk = mkdir -p

$(BINDIR)/$(TARGET): $(OBJS)
	$(mk) $(@D)
	$(AR) rcs $@ $(OBJS)
	cp $(BINDIR)/$(TARGET) ../../include/$(TARGET)

include $(OLDDEPS)

$(OBJDIR)/%_c.o : $(SRCDIR)/%.c
	$(mk)$(@D)
	$(mk) $(subst obj,dep,$(@D))
	$(CC) $(CFLAGS) $(DEPS) -c $< -o $@
	
$(OBJDIR)/%_cpp.o : $(SRCDIR)/%.cpp
	$(mk)$(@D)
	$(mk) $(subst obj,dep,$(@D))
	$(CPP) $(CPPFLAGS) $(DEPS) -c $< -o $@
	
$(OBJDIR)/%_cc.o : $(SRCDIR)/%.cc
	$(mk)$(@D)
	$(mk) $(subst obj,dep,$(@D))
	$(CPP) $(CPPFLAGS) $(DEPS) -c $< -o $@

$(OBJDIR)/%_S.o : $(SRCDIR)/%.S
	$(mk)$(@D)
	$(AS) $(GASFLAGS) -c $< -o $@
	
$(OBJDIR)/%_asm.o : $(SRCDIR)/%.asm
	$(mk)$(@D)
	$(ASM) $(NASFLAGS) $< -o $@

.PHONY: clean
clean:
	$(rm) $(OBJDIR)
	$(mk) $(OBJDIR)
	$(rm) $(DEPDIR)
	$(mk) $(DEPDIR)
