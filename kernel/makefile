TARGET = kernel

CC = gcc
LD = ld

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS_c = $(wildcard $(SRCDIR)/*.c)
SRCS_cpp = $(wildcard $(SRCDIR)/*.cpp)
SRCS_S = $(wildcard $(SRCDIR)/*.S)
HDR = $(wildcard $(SRCDIR)/*.h)
OBJS = $(SRCS_c:$(SRCDIR)/%.c=$(OBJDIR)/%_c.o) $(SRCS_cpp:$(SRCDIR)/%.cpp=$(OBJDIR)/%_cpp.o) $(SRCS_S:$(SRCDIR)/%.S=$(OBJDIR)/%_S.o)
rm = rm -f

ASFLAGS = -m64
CFLAGS = -m64 -Wall -g -fno-stack-protector -nostdinc
LDFLAGS = -m elf_x86_64 -Ttext=0x100000

$(BINDIR)/$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%_c.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/%_cpp.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%_S.o : $(SRCDIR)/%.S
	$(CC) $(ASFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(rm) $(OBJS)
	
.PHONY: remove
remove:
	$(rm) $(BINDIR)/$(TARGET)