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
BINDIR = ../../include

INCFLAGS = -I $(SRCDIR) -I ../../include -include types.h
FFLAGS = -ffreestanding -fno-exceptions -fno-rtti 
64FLAGS = -mcmodel=kernel -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow
WFLAGS = -pedantic -Wall -Wextra -Wno-unused-parameter

NASFLAGS = -f elf64
GASFLAGS = 
CPPFLAGS = $(64FLAGS) $(INCFLAGS) $(FFLAGS) $(WFLAGS) -std=gnu++14 -O2 -nostdlib -nostartfiles -lgcc
CFLAGS = $(64FLAGS) $(INCFLAGS) $(FFLAGS) $(WFLAGS) -std=gnu11 -O2 -nostdlib -nostartfiles -lgcc
LDFLAGS = -T linker.ld -O2 -z max-page-size=0x1000

SRCS_c = $(shell find $(SRCDIR)/* -name "*.c")
SRCS_cpp = $(shell find $(SRCDIR)/* -name "*.cpp")
SRCS_cc = $(shell find $(SRCDIR)/* -name "*.cc")
SRCS_S = $(shell find $(SRCDIR)/* -name "*.S")
SRCS_asm = $(shell find $(SRCDIR)/* -name "*.asm")

OBJS_c = $(addprefix $(OBJDIR)/,$(SRCS_c:$(SRCDIR)/%.c=%_c.o))
OBJS_cc = $(addprefix $(OBJDIR)/,$(SRCS_cpp:$(SRCDIR)/%.cc=%_cc.o))
OBJS_cpp = $(addprefix $(OBJDIR)/,$(SRCS_cpp:$(SRCDIR)/%.cpp=%_cpp.o))
OBJS_S = $(addprefix $(OBJDIR)/,$(SRCS_S:$(SRCDIR)/%.S=%_S.o))
OBJS_asm = $(addprefix $(OBJDIR)/,$(SRCS_asm:$(SRCDIR)/%.asm=%_asm.o))

OBJS = $(OBJS_c) $(OBJS_cpp) $(OBJS_S) $(OBJS_asm) $(OBJS_cc)
rm = rm -f -r

$(BINDIR)/$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)

$(OBJDIR)/%_c.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/%_cpp.o : $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CPP) $(CPPFLAGS) -c $< -o $@
	
$(OBJDIR)/%_cc.o : $(SRCDIR)/%.cc
	@mkdir -p $(@D)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/%_S.o : $(SRCDIR)/%.S
	@mkdir -p $(@D)
	$(AS) $(GASFLAGS) -c $< -o $@
	
$(OBJDIR)/%_asm.o : $(SRCDIR)/%.asm
	@mkdir -p $(@D)
	$(ASM) $(NASFLAGS) $< -o $@

.PHONY: clean
clean:
	$(rm) $(OBJS)
	
.PHONY: remove
remove:
	$(rm) $(BINDIR)/$(TARGET)