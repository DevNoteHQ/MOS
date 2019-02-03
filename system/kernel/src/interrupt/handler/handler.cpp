
#include "handler.hpp"
#include "stubs.hpp"

#include <interrupt/common.hpp>

void Interrupt_Handler(CPU::State *state)
{
	(*Interrupt::Handler::Handlers[state->Code])(state);
}

namespace Interrupt::Handler
{
	void(*Handlers[256])(CPU::State*);

	void Set(uint8_t Code, void(*ThisHandler)(CPU::State*))
	{
		Handlers[Code] = ThisHandler;
	}

	void SetDefault()
	{
		Set(FAULT00, &DivideByZero);
		Set(FAULT01, &Debug);
		Set(FAULT02, &NonMaskableInterrupt);
		Set(FAULT03, &Breakpoint);
		Set(FAULT04, &Overflow);
		Set(FAULT05, &BoundRange);
		Set(FAULT06, &InvalidOpcode);
		Set(FAULT07, &DeviceNotAvailable);
		Set(FAULT08, &DoubleFault);
		Set(FAULT09, &CoprocessorSegmentOverrun);
		Set(FAULT10, &InvalidTSS);
		Set(FAULT11, &SegmentNotPresent);
		Set(FAULT12, &StackFault);
		Set(FAULT13, &GeneralProtection);
		Set(FAULT14, &PageFault);
		Set(FAULT15, &Fault0x0F);
		Set(FAULT16, &X87FloatingPoint);
		Set(FAULT17, &AlignmentCheck);
		Set(FAULT18, &MachineCheck);
		Set(FAULT19, &SIMDFloatingPoint);
		Set(FAULT20, &Virtualization);
		Set(FAULT21, &Fault0x15);
		Set(FAULT22, &Fault0x16);
		Set(FAULT23, &Fault0x17);
		Set(FAULT24, &Fault0x18);
		Set(FAULT25, &Fault0x19);
		Set(FAULT26, &Fault0x1A);
		Set(FAULT27, &Fault0x1B);
		Set(FAULT28, &Fault0x1C);
		Set(FAULT29, &Fault0x1D);
		Set(FAULT30, &SecuritySensitiveEvent);
		Set(FAULT31, &Fault0x1F);

		Set(IRQ00, &IRQ_00);
		Set(IRQ01, &IRQ_01);
		Set(IRQ02, &IRQ_02);
		Set(IRQ03, &IRQ_03);
		Set(IRQ04, &IRQ_04);
		Set(IRQ05, &IRQ_05);
		Set(IRQ06, &IRQ_06);
		Set(IRQ07, &IRQ_07);
		Set(IRQ08, &IRQ_08);
		Set(IRQ09, &IRQ_09);
		Set(IRQ10, &IRQ_10);
		Set(IRQ11, &IRQ_11);
		Set(IRQ12, &IRQ_12);
		Set(IRQ13, &IRQ_13);
		Set(IRQ14, &IRQ_14);
		Set(IRQ15, &IRQ_15);
		Set(IRQ16, &IRQ_16);
		Set(IRQ17, &IRQ_17);
		Set(IRQ18, &IRQ_18);
		Set(IRQ19, &IRQ_19);
		Set(IRQ20, &IRQ_20);
		Set(IRQ21, &IRQ_21);
		Set(IRQ22, &IRQ_22);
		Set(IRQ23, &IRQ_23);

		Set(IPI_PANIC, &IPI_Panic);
		Set(IPI_TLB, &IPI_Tlb);
		Set(LVT_TIMER, &LVT_Timer);
		Set(LVT_ERROR, &LVT_Error);
		Set(SPURIOUS, &Spurious);

		for (int i = 0; i < 256; i++)
		{
			if (Handlers[i] == 0)
			{
				Set(i, &Default);
			}
		}
	}
}