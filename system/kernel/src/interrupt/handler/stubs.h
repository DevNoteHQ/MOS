

#include <cpu/cpu.h>

#ifndef INTERRUPT_HANDLER_STUBS_H
#define INTERRUPT_HANDLER_STUBS_H


//Faults:
__attribute__((interrupt)) void DivideByZero(CPU::State *state);
__attribute__((interrupt)) void Debug(CPU::State *state);
__attribute__((interrupt)) void NonMaskableInterrupt(CPU::State *state);
__attribute__((interrupt)) void Breakpoint(CPU::State *state);
__attribute__((interrupt)) void Overflow(CPU::State *state);
__attribute__((interrupt)) void BoundRange(CPU::State *state);
__attribute__((interrupt)) void InvalidOpcode(CPU::State *state);
__attribute__((interrupt)) void DeviceNotAvailable(CPU::State *state);
__attribute__((interrupt)) void DoubleFault(CPU::State *state, uint64_t error);
__attribute__((interrupt)) void CoprocessorSegmentOverrun(CPU::State *state);
__attribute__((interrupt)) void InvalidTSS(CPU::State *state, uint64_t error);
__attribute__((interrupt)) void SegmentNotPresent(CPU::State *state, uint64_t error);
__attribute__((interrupt)) void StackFault(CPU::State *state, uint64_t error);
__attribute__((interrupt)) void GeneralProtection(CPU::State *state, uint64_t error);
__attribute__((interrupt)) void PageFault(CPU::State *state, uint64_t error);
__attribute__((interrupt)) void Fault0x0F(CPU::State *state);
__attribute__((interrupt)) void x87FloatingPoint(CPU::State *state);
__attribute__((interrupt)) void AlignmentCheck(CPU::State *state, uint64_t error);
__attribute__((interrupt)) void MachineCheck(CPU::State *state);
__attribute__((interrupt)) void SIMDFloatingPoint(CPU::State *state);
__attribute__((interrupt)) void Fault0x14(CPU::State *state);
__attribute__((interrupt)) void Fault0x15(CPU::State *state);
__attribute__((interrupt)) void Fault0x16(CPU::State *state);
__attribute__((interrupt)) void Fault0x17(CPU::State *state);
__attribute__((interrupt)) void Fault0x18(CPU::State *state);
__attribute__((interrupt)) void Fault0x19(CPU::State *state);
__attribute__((interrupt)) void Fault0x1A(CPU::State *state);
__attribute__((interrupt)) void Fault0x1B(CPU::State *state);
__attribute__((interrupt)) void Fault0x1C(CPU::State *state);
__attribute__((interrupt)) void Fault0x1D(CPU::State *state);
__attribute__((interrupt)) void SecuritySensitiveEvent(CPU::State *state, uint64_t error);
__attribute__((interrupt)) void Fault0x1F(CPU::State *state);

//IRQs:
__attribute__((interrupt)) void irq00(CPU::State *state);
__attribute__((interrupt)) void irq01(CPU::State *state);
__attribute__((interrupt)) void irq02(CPU::State *state);
__attribute__((interrupt)) void irq03(CPU::State *state);
__attribute__((interrupt)) void irq04(CPU::State *state);
__attribute__((interrupt)) void irq05(CPU::State *state);
__attribute__((interrupt)) void irq06(CPU::State *state);
__attribute__((interrupt)) void irq07(CPU::State *state);
__attribute__((interrupt)) void irq08(CPU::State *state);
__attribute__((interrupt)) void irq09(CPU::State *state);
__attribute__((interrupt)) void irq10(CPU::State *state);
__attribute__((interrupt)) void irq11(CPU::State *state);
__attribute__((interrupt)) void irq12(CPU::State *state);
__attribute__((interrupt)) void irq13(CPU::State *state);
__attribute__((interrupt)) void irq14(CPU::State *state);
__attribute__((interrupt)) void irq15(CPU::State *state);
__attribute__((interrupt)) void irq16(CPU::State *state);
__attribute__((interrupt)) void irq17(CPU::State *state);
__attribute__((interrupt)) void irq18(CPU::State *state);
__attribute__((interrupt)) void irq19(CPU::State *state);
__attribute__((interrupt)) void irq20(CPU::State *state);
__attribute__((interrupt)) void irq21(CPU::State *state);
__attribute__((interrupt)) void irq22(CPU::State *state);
__attribute__((interrupt)) void irq23(CPU::State *state);

//Syscalls:
__attribute__((interrupt)) void syscall0(CPU::State *state);


//Special:
__attribute__((interrupt)) void special(CPU::State *state);


#endif