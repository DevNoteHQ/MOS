
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void Debug(struct cpu_state *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT!");
}
