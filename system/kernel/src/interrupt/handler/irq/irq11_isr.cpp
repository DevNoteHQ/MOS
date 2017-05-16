
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void irq11(CPU::State *state)
{
	//Text::Clear();
	Text::Simple::Write("IRQ!");
}