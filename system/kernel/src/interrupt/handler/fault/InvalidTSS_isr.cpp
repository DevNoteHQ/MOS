
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void InvalidTSS(CPU::State *state, uint64_t error)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Invalid TSS!");
}
