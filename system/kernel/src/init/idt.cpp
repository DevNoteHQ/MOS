
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

	void Set (Descriptor *descriptor, void(*handler)(), uint8_t flags)
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
		Set(&descriptors[0x00], &fault0,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x01], &fault1,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x02], &fault2,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x03], &fault3,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x04], &fault4,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x05], &fault5,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x06], &fault6,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x07], &fault7,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x08], &fault8,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x09], &fault9,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x0A], &fault10,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x0B], &fault11,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x0C], &fault12,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x0D], &fault13,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x0E], &fault14,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x0F], &fault15,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x10], &fault16,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x11], &fault17,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x12], &fault18,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x13], &fault19,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x14], &fault20,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x15], &fault21,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x16], &fault22,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x17], &fault23,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x18], &fault24,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x19], &fault25,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x1A], &fault26,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x1B], &fault27,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x1C], &fault28,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x1D], &fault29,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x1E], &fault30,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[0x1F], &fault31,	IDT_PRESENT | IDT_INTERRUPT);

		//IRQs:
		Set (&descriptors[0x20], &irq0,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x21], &irq1,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x22], &irq2,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x23], &irq3,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x24], &irq4,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x25], &irq5,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x26], &irq6,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x27], &irq7,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x28], &irq8,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x29], &irq9,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2A], &irq10,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2B], &irq11,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2C], &irq12,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2D], &irq13,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2E], &irq14,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x2F], &irq15,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x30], &irq16,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x31], &irq17,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x32], &irq18,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x33], &irq19,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x34], &irq20,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x35], &irq21,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x36], &irq22,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[0x37], &irq23,	IDT_PRESENT | IDT_INTERRUPT);

		//Special:
		Set (&descriptors[IPI_PANIC],	&ipi_panic,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IPI_TLB],		&ipi_tlb,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[LVT_TIMER],	&lvt_timer,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[LVT_ERROR],	&lvt_error,	IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[SPURIOUS],	&spurious,	IDT_PRESENT | IDT_INTERRUPT);

		idtr.addr = (uint64_t)descriptors;
		idtr.len = sizeof(descriptors) - 1;
		idtr_install(&idtr);
	}
}