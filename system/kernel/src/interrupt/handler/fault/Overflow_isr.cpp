
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void Overflow(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Overflow!");
}
