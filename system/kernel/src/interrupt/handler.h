

#include <cpu/cpu.h>

#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

extern "C" void exception(struct cpu_state* cpu);
extern "C" void hwinterrupt(struct cpu_state* cpu);
extern "C" void swinterrupt(struct cpu_state* cpu);
extern "C" void spechandler(struct cpu_state* cpu);

extern "C" void fault(void);
extern "C" void irq(void);
extern "C" void syscall(void);
extern "C" void special(void);

#endif