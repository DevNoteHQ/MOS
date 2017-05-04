SRCS = $(shell find -name '*.c') $(shell find -name '*.cpp') $(shell find -name '*.S')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = gcc
LD = ld

ASFLAGS = -m64
CFLAGS = -m64 -Wall -g -fno-stack-protector -nostdinc
LDFLAGS = -m elf_x86_64 -Ttext=0x100000

kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $^

clean:
	rm $(OBJS)

.PHONY: clean