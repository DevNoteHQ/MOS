
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void InvalidTSS(CPU::State *state, uint64_t error)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Invalid TSS!");
}
