
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void BoundRange(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Bound Range!");
}
