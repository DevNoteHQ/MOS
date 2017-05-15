
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void Overflow(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Overflow!");
}
