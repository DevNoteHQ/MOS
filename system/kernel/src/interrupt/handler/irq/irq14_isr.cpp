
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Irq14(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("IRQ!");
}