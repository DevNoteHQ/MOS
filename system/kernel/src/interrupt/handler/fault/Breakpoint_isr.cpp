
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void Breakpoint(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Breakpoint!");
}
