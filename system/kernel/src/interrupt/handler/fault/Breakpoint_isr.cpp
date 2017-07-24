
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Breakpoint(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Breakpoint!");
}
