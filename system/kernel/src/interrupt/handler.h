

#include <cpu/cpu.h>

#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

void interrupt(void);
extern "C" void exception(struct cpu_state* cpu);
extern "C" void hwinterrupt(struct cpu_state* cpu);
extern "C" void swinterrupt(struct cpu_state* cpu);
extern "C" void fault();
extern "C" void irq();
extern "C" void syscall();

#endif