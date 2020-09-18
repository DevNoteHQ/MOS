
#include "pic.hpp"
#include "common.hpp"
#include <assembler/io_ports.hpp>

namespace Interrupt::PIC {
	void Init() {
		//Master-PIC
		Assembler::IO::Ports::outb(PIC1, ICW1_INIT);
		Assembler::IO::Ports::outb(PIC1_DATA, IRQ00);
		Assembler::IO::Ports::outb(PIC1_DATA, 0x4);
		Assembler::IO::Ports::outb(PIC1_DATA, ICW1_ICW4);
		//Slave-PIC
		Assembler::IO::Ports::outb(PIC2, ICW1_INIT);
		Assembler::IO::Ports::outb(PIC2_DATA, IRQ08);
		Assembler::IO::Ports::outb(PIC2_DATA, 0x2);
		Assembler::IO::Ports::outb(PIC2_DATA, ICW1_ICW4);

		//Set PIT in One-Shot Mode
		Assembler::IO::Ports::outb(0x43, 0x30);
	}

	void Activate() {
		//Alle IRQs aktivieren
		Assembler::IO::Ports::outb(PIC1_DATA, 0x0);
		Assembler::IO::Ports::outb(PIC2_DATA, 0x0);
	}

	void Disable() {
		//Alle IRQs aktivieren
		Assembler::IO::Ports::outb(PIC1_DATA, 0xFF);
		Assembler::IO::Ports::outb(PIC2_DATA, 0xFF);
	}
}