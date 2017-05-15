
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void InvalidOpcode(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Invalid Opcode!");
}
