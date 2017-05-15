
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void Fault0x16(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Fault0x16!");
}
