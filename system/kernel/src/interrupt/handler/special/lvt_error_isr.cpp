
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void LVT_Error(CPU::State *state)
{
	Text::WriteLine("LVT_Error!");
	Interrupt::APIC::Write(APIC_EOI, 0);
}