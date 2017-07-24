
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Overflow(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Overflow!");
}
