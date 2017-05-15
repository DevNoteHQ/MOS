
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void SecuritySensitiveEvent(CPU::State *state, uint64_t error)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Security-sensitive Event in Host!");
}
