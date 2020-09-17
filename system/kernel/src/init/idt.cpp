
#include <init/idt.hpp>
#include <interrupt/common.hpp>
#include <interrupt/handler/stubs.hpp>

#define IDT_PRESENT		0x80
#define IDT_USER		0x60
#define IDT_INTERRUPT	0x0E
#define IDT_TRAP		0x0F

namespace IDT {
	static Descriptor descriptors[INTERRUPTS];
	static IDTR_t idtr;

	void Set (Descriptor *descriptor, void(*handler)(), uint8_t flags) {
		descriptor->selector = 0x08;

		uintptr_t handler_addr = (uintptr_t)handler;
		descriptor->offset_1 = handler_addr & 0xFFFF;
		descriptor->offset_2 = (handler_addr >> 16) & 0xFFFF;
		descriptor->offset_3 = (handler_addr >> 32) & 0xFFFFFFFF;

		descriptor->flags = flags;
	}

	void Init() {
		memset(descriptors, 0, sizeof(descriptors));

		//Faults:
		Set(&descriptors[FAULT00], &fault0,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT01], &fault1,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT02], &fault2,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT03], &fault3,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT04], &fault4,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT05], &fault5,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT06], &fault6,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT07], &fault7,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT08], &fault8,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT09], &fault9,		IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT10], &fault10,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT11], &fault11,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT12], &fault12,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT13], &fault13,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT14], &fault14,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT15], &fault15,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT16], &fault16,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT17], &fault17,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT18], &fault18,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT19], &fault19,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT20], &fault20,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT21], &fault21,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT22], &fault22,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT23], &fault23,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT24], &fault24,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT25], &fault25,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT26], &fault26,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT27], &fault27,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT28], &fault28,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT29], &fault29,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT30], &fault30,	IDT_PRESENT | IDT_INTERRUPT);
		Set(&descriptors[FAULT31], &fault31,	IDT_PRESENT | IDT_INTERRUPT);

		//IRQs:
		Set (&descriptors[IRQ00], &irq0,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ01], &irq1,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ02], &irq2,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ03], &irq3,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ04], &irq4,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ05], &irq5,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ06], &irq6,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ07], &irq7,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ08], &irq8,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ09], &irq9,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ10], &irq10,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ11], &irq11,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ12], &irq12,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ13], &irq13,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ14], &irq14,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ15], &irq15,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ16], &irq16,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ17], &irq17,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ18], &irq18,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ19], &irq19,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ20], &irq20,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ21], &irq21,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ22], &irq22,		IDT_PRESENT | IDT_INTERRUPT);
		Set (&descriptors[IRQ23], &irq23,		IDT_PRESENT | IDT_INTERRUPT);

		//Software Interrupts:


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