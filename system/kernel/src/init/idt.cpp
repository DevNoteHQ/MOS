
#include <init/idt.h>
#include <interrupt/handler.h>

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

		int i = 0;

		for (; i <= LASTFAULT; i++)
		{
			set(&descriptors[i], &fault, IDT_PRESENT | IDT_INTERRUPT);
		}
		for (; i <= LASTIRQ; i++)
		{
			set(&descriptors[i], &irq, IDT_PRESENT | IDT_INTERRUPT);
		}
		for (; i <= LASTSYSCALL; i++)
		{
			set(&descriptors[i], &syscall, IDT_PRESENT | IDT_INTERRUPT);
		}

		set(&descriptors[NOT_INTR], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[IPI_PANIC], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[IPI_TLB], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[LVT_TIMER], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[LVT_ERROR], &special, IDT_PRESENT | IDT_INTERRUPT);
		set(&descriptors[SPURIOUS], &special, IDT_PRESENT | IDT_INTERRUPT);

		idtr.addr = (uint64_t) descriptors;
		idtr.len = sizeof(descriptors) - 1;
		idtr_install(&idtr);
	}
}