
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void Fault0x1C(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Fault0x1C!");
}
