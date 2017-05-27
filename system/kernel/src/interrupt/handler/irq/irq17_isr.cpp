
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void irq17(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("IRQ!");
}