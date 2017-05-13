
#include <init/idt.h>
#include <interrupt/handler.h>

#define IDT_PRESENT   0x80
#define IDT_USER      0x60
#define IDT_INTERRUPT 0x0E
#define IDT_TRAP      0x0F
#define INTERRUPTS 0xFF

namespace IDT
{
	static IDTDescr descriptors[INTERRUPTS];
	IDTR_t idtr;

	static void set(IDTDescr *descriptor, void(*handler)(void), uint8_t flags)
	{
		descriptor->selector = 0x08;

		uintptr_t handler_addr = (uintptr_t)handler;
		descriptor->offset_1 = handler_addr & 0xFFFF;
		descriptor->offset_2 = (handler_addr >> 16) & 0xFFFF;
		descriptor->offset_3 = (handler_addr >> 32) & 0xFFFFFFFF;

		descriptor->ist = flags;
	}

	void init(void)
	{
		memset(descriptors, 0, sizeof(descriptors));

		for (int i = 0; i < INTERRUPTS; i++)
		{
			set(&descriptors[i], &interrupt, IDT_PRESENT | IDT_INTERRUPT);
		}

		idtr.addr = (uint64_t) descriptors;
		idtr.len = sizeof(descriptors) - 1;
		idtr_install(&idtr);
	}
}