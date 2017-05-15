
#include <init/idt.h>
#include <interrupt/handler/stubs.h>

#define IDT_PRESENT		0x80
#define IDT_USER		0x60
#define IDT_INTERRUPT	0x0E
#define IDT_TRAP		0x0F

#define INTERRUPTS		256
#define LASTFAULT		0x1F
#define LASTIRQ			0x37
#define LASTSYSCALL		0xF9

#define NOT_INTR 0xFA

/* IPIs */
#define IPI_PANIC 0xFB
#define IPI_TLB   0xFC

/* LAPIC LVT interrupts */
#define LVT_TIMER 0xFD
#define LVT_ERROR 0xFE

/* LAPIC spurious interrupt */
#define SPURIOUS 0xFF

namespace IDT
{
	static IDTDescr descriptors[INTERRUPTS];
	static IDTR_t idtr;

	void set(IDTDescr *descriptor, void(*handler)(void), uint8_t flags)
	{
		descriptor->selector = 0x08;

		uintptr_t handler_addr = (uintptr_t)handler;
		descriptor->offset_1 = handler_addr & 0xFFFF;
		descriptor->offset_2 = (handler_addr >> 16) & 0xFFFF;
		descriptor->offset_3 = (handler_addr >> 32) & 0xFFFFFFFF;

		descriptor->flags = flags;
	}

	void init(void)
	{
		memset(descriptors, 0, sizeof(descriptors));

		//Faults:
		set(&descriptors[0x00], &DivideByZero,				IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x01], &Debug,						IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x02], &NonMaskableInterrupt,		IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x03], &Breakpoint,				IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x04], &Overflow,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x05], &BoundRange,				IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x06], &InvalidOpcode,				IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x07], &DeviceNotAvailable,		IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x08], &DoubleFault,				IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x09], &CoprocessorSegmentOverrun,	IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x0A], &InvalidTSS,				IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x0B], &SegmentNotPresent,			IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x0C], &StackFault,				IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x0D], &GeneralProtection,			IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x0E], &PageFault,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x0F], &Fault0x0F,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x10], &x87FloatingPoint,			IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x11], &AlignmentCheck,			IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x12], &MachineCheck,				IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x13], &SIMDFloatingPoint,			IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x14], &Fault0x14,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x15], &Fault0x15,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x16], &Fault0x16,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x17], &Fault0x17,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x18], &Fault0x18,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x19], &Fault0x19,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x1A], &Fault0x1A,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x1B], &Fault0x1B,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x1C], &Fault0x1C,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x1D], &Fault0x1D,					IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x1E], &SecuritySensitiveEvent,	IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[0x1F], &Fault0x1F,					IDT_PRESENT | IDT_INTERRUPT);


		//IRQs:
		set(&descriptors[0x20], &irq0, IDT_PRESENT | IDT_INTERRUPT);


		//Syscalls:
		set(&descriptors[0x38], &syscall0, IDT_PRESENT | IDT_INTERRUPT);


		//Special:
		set(&descriptors[NOT_INTR], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[IPI_PANIC], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[IPI_TLB], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[LVT_TIMER], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[LVT_ERROR], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[SPURIOUS], &special, IDT_PRESENT | IDT_INTERRUPT);

		idtr.addr = (uint64_t)descriptors;
		idtr.len = sizeof(descriptors) - 1;
		idtr_install(&idtr);
	}
}