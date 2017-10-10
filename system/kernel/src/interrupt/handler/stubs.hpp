

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
__attribute__((interrupt)) void IRQ_00(CPU::State *state);
__attribute__((interrupt)) void IRQ_01(CPU::State *state);
__attribute__((interrupt)) void IRQ_02(CPU::State *state);
__attribute__((interrupt)) void IRQ_03(CPU::State *state);
__attribute__((interrupt)) void IRQ_04(CPU::State *state);
__attribute__((interrupt)) void IRQ_05(CPU::State *state);
__attribute__((interrupt)) void IRQ_06(CPU::State *state);
__attribute__((interrupt)) void IRQ_07(CPU::State *state);
__attribute__((interrupt)) void IRQ_08(CPU::State *state);
__attribute__((interrupt)) void IRQ_09(CPU::State *state);
__attribute__((interrupt)) void IRQ_10(CPU::State *state);
__attribute__((interrupt)) void IRQ_11(CPU::State *state);
__attribute__((interrupt)) void IRQ_12(CPU::State *state);
__attribute__((interrupt)) void IRQ_13(CPU::State *state);
__attribute__((interrupt)) void IRQ_14(CPU::State *state);
__attribute__((interrupt)) void IRQ_15(CPU::State *state);
__attribute__((interrupt)) void IRQ_16(CPU::State *state);
__attribute__((interrupt)) void IRQ_17(CPU::State *state);
__attribute__((interrupt)) void IRQ_18(CPU::State *state);
__attribute__((interrupt)) void IRQ_19(CPU::State *state);
__attribute__((interrupt)) void IRQ_20(CPU::State *state);
__attribute__((interrupt)) void IRQ_21(CPU::State *state);
__attribute__((interrupt)) void IRQ_22(CPU::State *state);
__attribute__((interrupt)) void IRQ_23(CPU::State *state);

//Syscalls:
__attribute__((interrupt)) void Syscall0(CPU::State *state);


//Special:
__attribute__((interrupt)) void Special(CPU::State *state);
__attribute__((interrupt)) void LVT_Timer(CPU::State *state);
__attribute__((interrupt)) void LVT_Error(CPU::State *state);
__attribute__((interrupt)) void Spurious(CPU::State *state);


#endif