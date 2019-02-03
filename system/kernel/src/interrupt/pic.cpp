
#include "pic.hpp"
#include "common.hpp"

namespace Interrupt::PIC
{
	void Init()
	{
		//Master-PIC
		IO::outb(PIC1, ICW1_INIT);
		IO::outb(PIC1_DATA, IRQ00);
		IO::outb(PIC1_DATA, 0x4);
		IO::outb(PIC1_DATA, ICW1_ICW4);
		//Slave-PIC
		IO::outb(PIC2, ICW1_INIT);
		IO::outb(PIC2_DATA, IRQ08);
		IO::outb(PIC2_DATA, 0x2);
		IO::outb(PIC2_DATA, ICW1_ICW4);

		//Set PIT in One-Shot Mode
		IO::outb(0x43, 0x30);
	}

	void Activate()
	{
		//Alle IRQs aktivieren
		IO::outb(PIC1_DATA, 0x0);
		IO::outb(PIC2_DATA, 0x0);
	}

	void Disable()
	{
		//Alle IRQs aktivieren
		IO::outb(PIC1_DATA, 0xFF);
		IO::outb(PIC2_DATA, 0xFF);
	}
}