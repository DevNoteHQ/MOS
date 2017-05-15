
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void Fault0x15(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Fault0x15!");
}
