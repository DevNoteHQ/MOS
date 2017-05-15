
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void Debug(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Debug!");
}
