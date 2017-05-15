
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void x87FloatingPoint(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: x87 Floating Point!");
}
