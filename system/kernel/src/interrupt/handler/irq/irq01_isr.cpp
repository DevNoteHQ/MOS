
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

#include <libMOS/convert/convert.hpp>


__attribute__((interrupt)) void IRQ_01(CPU::State *state)
{
	//Keyboard Driver
	uint8_t iScancode;
	uint8_t iKeycode = 0;
	while (true)
	{
		if (IO::inb(0x60) != iScancode)
		{
			iScancode = IO::inb(0x60);
			if (iScancode > 0)
			{
				break;
			}
		}
	}
	iScancode = IO::inb(0x60);
	char cKey[3] = { '\0' };
	Convert::OldToString((uint64_t) iScancode, cKey);
	Text::Write(cKey);
	Text::Write(" - ");

#ifndef FORCE_PIC
	Interrupt::APIC::Write(APIC_EOI, 0);
#else
	IO::outb(0x20, 0x20);
#endif
}