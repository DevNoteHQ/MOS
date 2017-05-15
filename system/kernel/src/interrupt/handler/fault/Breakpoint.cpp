
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void Breakpoint(struct cpu_state *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT!");
}
