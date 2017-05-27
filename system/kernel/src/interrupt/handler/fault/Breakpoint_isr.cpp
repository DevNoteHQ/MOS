
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void Breakpoint(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Breakpoint!");
}
