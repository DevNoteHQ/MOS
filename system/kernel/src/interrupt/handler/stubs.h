

#include <cpu/cpu.h>

#ifndef INTERRUPT_STUBS_H
#define INTERRUPT_STUBS_H


//Faults:
__attribute__((interrupt)) void DivideByZero(struct cpu_state *state);
__attribute__((interrupt)) void Debug(struct cpu_state *state);
__attribute__((interrupt)) void NonMaskableInterrupt(struct cpu_state *state);
__attribute__((interrupt)) void Breakpoint(struct cpu_state *state);
__attribute__((interrupt)) void Overflow(struct cpu_state *state);
__attribute__((interrupt)) void BoundRange(struct cpu_state *state);
__attribute__((interrupt)) void InvalidOpcode(struct cpu_state *state);
__attribute__((interrupt)) void DeviceNotAvailable(struct cpu_state *state);
__attribute__((interrupt)) void DoubleFault(struct cpu_state *state, uint64_t error);
__attribute__((interrupt)) void CoprocessorSegmentOverrun(struct cpu_state *state);
__attribute__((interrupt)) void InvalidTSS(struct cpu_state *state, uint64_t error);
__attribute__((interrupt)) void SegmentNotPresent(struct cpu_state *state, uint64_t error);
__attribute__((interrupt)) void StackFault(struct cpu_state *state, uint64_t error);
__attribute__((interrupt)) void GeneralProtection(struct cpu_state *state, uint64_t error);
__attribute__((interrupt)) void PageFault(struct cpu_state *state, uint64_t error);
__attribute__((interrupt)) void Fault0x0F(struct cpu_state *state);
__attribute__((interrupt)) void x87FloatingPoint(struct cpu_state *state);
__attribute__((interrupt)) void AlignmentCheck(struct cpu_state *state, uint64_t error);
__attribute__((interrupt)) void MachineCheck(struct cpu_state *state);
__attribute__((interrupt)) void SIMDFloatingPoint(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x14(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x15(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x16(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x17(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x18(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x19(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x1A(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x1B(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x1C(struct cpu_state *state);
__attribute__((interrupt)) void Fault0x1D(struct cpu_state *state);
__attribute__((interrupt)) void SecuritySensitiveEvent(struct cpu_state *state, uint64_t error);
__attribute__((interrupt)) void Fault0x1F(struct cpu_state *state);


//IRQs:
__attribute__((interrupt)) void irq0(struct cpu_state *state);


//Syscalls:
__attribute__((interrupt)) void syscall0(struct cpu_state *state);


//Special:
__attribute__((interrupt)) void special(struct cpu_state *state);


#endif