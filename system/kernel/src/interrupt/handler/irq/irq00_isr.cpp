
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_00(CPU::State *state)
{
	Text::WriteLine("IRQ_00!");

#ifndef FORCE_PIC
	Interrupt::APIC::Write(APIC_EOI, 0);
#else
	IO::outb(0x20, 0x20);
#endif
}