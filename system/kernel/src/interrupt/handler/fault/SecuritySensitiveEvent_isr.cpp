
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void SecuritySensitiveEvent(CPU::State *state, uint64_t error)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Security-sensitive Event in Host!");
}
