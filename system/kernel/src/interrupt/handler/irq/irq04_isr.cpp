
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_04(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("IRQ_04!");

	Interrupt::APIC::Write(APIC_EOI, 0);
}