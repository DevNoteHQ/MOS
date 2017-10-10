
#include <init/idt.hpp>
#include <interrupt/common.hpp>
#include <interrupt/handler/stubs.hpp>

#define IDT_PRESENT		0x80
#define IDT_USER		0x60
#define IDT_INTERRUPT	0x0E
#define IDT_TRAP		0x0F

namespace IDT
{
	static Descriptor descriptors[INTERRUPTS];
	static IDTR_t idtr;

	void Set (Descriptor *descriptor, void(*handler)(CPU::State *state), uint8_t flags)
	{
		descriptor->selector = 0x08;

		uintptr_t handler_addr = (uintptr_t)handler;
		descriptor->offset_1 = handler_addr & 0xFFFF;
		descriptor->offset_2 = (handler_addr >> 16) & 0xFFFF;
		descriptor->offset_3 = (handler_addr >> 32) & 0xFFFFFFFF;

		descriptor->flags = flags;
	}

	void Sete(Descriptor *descriptor, void(*handler)(CPU::State *state, uint64_t error), uint8_t flags)
	{
		descriptor->selector = 0x08;

		uintptr_t handler_addr = (uintptr_t)handler;
		descriptor->offset_1 = handler_addr & 0xFFFF;
		descriptor->offset_2 = (handler_addr >> 16) & 0xFFFF;
		descriptor->offset_3 = (handler_addr >> 32) & 0xFFFFFFFF;

		descriptor->flags = flags;
	}

	void Init()
	{
		memset(descriptors, 0, sizeof(descriptors));

		//Faults:
		Set (&descriptors[0x00], &DivideByZero,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x01], &Debug,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x02], &NonMaskableInterrupt,			IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x03], &Breakpoint,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x04], &Overflow,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x05], &BoundRange,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x06], &InvalidOpcode,				IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x07], &DeviceNotAvailable,			IDT_PRESENT | IDT_INTERRUPT);
		Sete(&descriptors[0x08], &DoubleFault,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x09], &CoprocessorSegmentOverrun,	IDT_PRESENT | IDT_INTERRUPT);
		Sete(&descriptors[0x0A], &InvalidTSS,					IDT_PRESENT | IDT_INTERRUPT);
		Sete(&descriptors[0x0B], &SegmentNotPresent,			IDT_PRESENT | IDT_INTERRUPT);
		Sete(&descriptors[0x0C], &StackFault,					IDT_PRESENT | IDT_INTERRUPT);
		Sete(&descriptors[0x0D], &GeneralProtection,			IDT_PRESENT | IDT_INTERRUPT);
		Sete(&descriptors[0x0E], &PageFault,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x0F], &Fault0x0F,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x10], &X87FloatingPoint,				IDT_PRESENT | IDT_INTERRUPT);
		Sete(&descriptors[0x11], &AlignmentCheck,				IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x12], &MachineCheck,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x13], &SIMDFloatingPoint,			IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x14], &Fault0x14,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x15], &Fault0x15,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x16], &Fault0x16,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x17], &Fault0x17,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x18], &Fault0x18,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x19], &Fault0x19,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x1A], &Fault0x1A,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x1B], &Fault0x1B,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x1C], &Fault0x1C,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x1D], &Fault0x1D,					IDT_PRESENT | IDT_INTERRUPT);
		Sete(&descriptors[0x1E], &SecuritySensitiveEvent,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x1F], &Fault0x1F,					IDT_PRESENT | IDT_INTERRUPT);

		//IRQs:
		Set (&descriptors[0x20], &IRQ_00,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x21], &IRQ_01,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x22], &IRQ_02,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x23], &IRQ_03,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x24], &IRQ_04,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x25], &IRQ_05,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x26], &IRQ_06,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x27], &IRQ_07,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x28], &IRQ_08,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x29], &IRQ_09,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2A], &IRQ_00,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2B], &IRQ_11,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2C], &IRQ_12,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2D], &IRQ_13,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2E], &IRQ_14,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2F], &IRQ_15,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x30], &IRQ_16,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x31], &IRQ_17,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x32], &IRQ_18,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x33], &IRQ_19,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x34], &IRQ_20,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x35], &IRQ_21,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x36], &IRQ_22,						IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x37], &IRQ_23,						IDT_PRESENT | IDT_INTERRUPT);

		//Syscalls:
		Set (&descriptors[0x38], &Syscall0,						IDT_PRESENT | IDT_INTERRUPT);

		//Special:
		Set (&descriptors[NOT_INTR],	&Special,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IPI_PANIC],	&Special,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IPI_TLB],		&Special,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[LVT_TIMER],	&LVT_Timer,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[LVT_ERROR],	&LVT_Error,					IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[SPURIOUS],	&Spurious,					IDT_PRESENT | IDT_INTERRUPT);

		idtr.addr = (uint64_t)descriptors;
		idtr.len = sizeof(descriptors) - 1;
		idtr_install(&idtr);
	}
}