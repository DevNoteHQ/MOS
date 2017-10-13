
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_20(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("IRQ_20!");

	Interrupt::APIC::Write(APIC_EOI, 0);
}