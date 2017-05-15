
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void GeneralProtection(CPU::State *state, uint64_t error)
{
	Text::Clear();
	Text::Simple::Write("FAULT: General Protection!");
}
