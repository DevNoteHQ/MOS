

#include <cpu/cpu.hpp>

#ifndef INTERRUPT_HANDLER_STUBS_HPP
#define INTERRUPT_HANDLER_STUBS_HPP

extern "C" {
	void fault0();
	void fault1();
	void fault2();
	void fault3();
	void fault4();
	void fault5();
	void fault6();
	void fault7();
	void fault8();
	void fault9();
	void fault10();
	void fault11();
	void fault12();
	void fault13();
	void fault14();
	void fault15();
	void fault16();
	void fault17();
	void fault18();
	void fault19();
	void fault20();
	void fault21();
	void fault22();
	void fault22();
	void fault23();
	void fault24();
	void fault25();
	void fault26();
	void fault27();
	void fault28();
	void fault29();
	void fault30();
	void fault31();

	void irq0();
	void irq1();
	void irq2();
	void irq3();
	void irq4();
	void irq5();
	void irq6();
	void irq7();
	void irq8();
	void irq9();
	void irq10();
	void irq11();
	void irq12();
	void irq13();
	void irq14();
	void irq15();
	void irq16();
	void irq17();
	void irq18();
	void irq19();
	void irq20();
	void irq21();
	void irq22();
	void irq23();

	void ipi_route();
	void ipi_panic();
	void ipi_tlb();
	void lvt_timer();
	void lvt_error();
	void spurious();
}

namespace Interrupt::Handler {
	void DivideByZero(CPU::State *state);
	void Debug(CPU::State *state);
	void NonMaskableInterrupt(CPU::State *state);
	void Breakpoint(CPU::State *state);
	void Overflow(CPU::State *state);
	void BoundRange(CPU::State *state);
	void InvalidOpcode(CPU::State *state);
	void DeviceNotAvailable(CPU::State *state);
	void DoubleFault(CPU::State *state);
	void CoprocessorSegmentOverrun(CPU::State *state);
	void InvalidTSS(CPU::State *state);
	void SegmentNotPresent(CPU::State *state);
	void StackFault(CPU::State *state);
	void GeneralProtection(CPU::State *state);
	void PageFault(CPU::State *state);
	void Fault0x0F(CPU::State *state);
	void X87FloatingPoint(CPU::State *state);
	void AlignmentCheck(CPU::State *state);
	void MachineCheck(CPU::State *state);
	void SIMDFloatingPoint(CPU::State *state);
	void Virtualization(CPU::State *state);
	void Fault0x15(CPU::State *state);
	void Fault0x16(CPU::State *state);
	void Fault0x17(CPU::State *state);
	void Fault0x18(CPU::State *state);
	void Fault0x19(CPU::State *state);
	void Fault0x1A(CPU::State *state);
	void Fault0x1B(CPU::State *state);
	void Fault0x1C(CPU::State *state);
	void Fault0x1D(CPU::State *state);
	void SecuritySensitiveEvent(CPU::State *state);
	void Fault0x1F(CPU::State *state);

	void IRQ_00(CPU::State *state);
	void IRQ_01(CPU::State *state);
	void IRQ_02(CPU::State *state);
	void IRQ_03(CPU::State *state);
	void IRQ_04(CPU::State *state);
	void IRQ_05(CPU::State *state);
	void IRQ_06(CPU::State *state);
	void IRQ_07(CPU::State *state);
	void IRQ_08(CPU::State *state);
	void IRQ_09(CPU::State *state);
	void IRQ_10(CPU::State *state);
	void IRQ_11(CPU::State *state);
	void IRQ_12(CPU::State *state);
	void IRQ_13(CPU::State *state);
	void IRQ_14(CPU::State *state);
	void IRQ_15(CPU::State *state);
	void IRQ_16(CPU::State *state);
	void IRQ_17(CPU::State *state);
	void IRQ_18(CPU::State *state);
	void IRQ_19(CPU::State *state);
	void IRQ_20(CPU::State *state);
	void IRQ_21(CPU::State *state);
	void IRQ_22(CPU::State *state);
	void IRQ_23(CPU::State *state);

	void Default(CPU::State *state);

	void IPI_Panic(CPU::State *state);
	void IPI_Tlb(CPU::State *state);
	void LVT_Timer(CPU::State *state);
	void LVT_Error(CPU::State *state);
	void Spurious(CPU::State *state);
}

#endif