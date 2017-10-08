

#include <cpu/cpu.hpp>

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
__attribute__((interrupt)) void X87FloatingPoint(CPU::State *state);
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
__attribute__((interrupt)) void Irq00(CPU::State *state);
__attribute__((interrupt)) void Irq01(CPU::State *state);
__attribute__((interrupt)) void Irq02(CPU::State *state);
__attribute__((interrupt)) void Irq03(CPU::State *state);
__attribute__((interrupt)) void Irq04(CPU::State *state);
__attribute__((interrupt)) void Irq05(CPU::State *state);
__attribute__((interrupt)) void Irq06(CPU::State *state);
__attribute__((interrupt)) void Irq07(CPU::State *state);
__attribute__((interrupt)) void Irq08(CPU::State *state);
__attribute__((interrupt)) void Irq09(CPU::State *state);
__attribute__((interrupt)) void Irq10(CPU::State *state);
__attribute__((interrupt)) void Irq11(CPU::State *state);
__attribute__((interrupt)) void Irq12(CPU::State *state);
__attribute__((interrupt)) void Irq13(CPU::State *state);
__attribute__((interrupt)) void Irq14(CPU::State *state);
__attribute__((interrupt)) void Irq15(CPU::State *state);
__attribute__((interrupt)) void Irq16(CPU::State *state);
__attribute__((interrupt)) void Irq17(CPU::State *state);
__attribute__((interrupt)) void Irq18(CPU::State *state);
__attribute__((interrupt)) void Irq19(CPU::State *state);
__attribute__((interrupt)) void Irq20(CPU::State *state);
__attribute__((interrupt)) void Irq21(CPU::State *state);
__attribute__((interrupt)) void Irq22(CPU::State *state);
__attribute__((interrupt)) void Irq23(CPU::State *state);

//Syscalls:
__attribute__((interrupt)) void Syscall0(CPU::State *state);


//Special:
__attribute__((interrupt)) void Special(CPU::State *state);
__attribute__((interrupt)) void LVT_Timer(CPU::State *state);
__attribute__((interrupt)) void LVT_Error(CPU::State *state);
__attribute__((interrupt)) void Spurious(CPU::State *state);


#endif