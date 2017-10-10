
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void IRQ_17(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("IRQ_17!");
}