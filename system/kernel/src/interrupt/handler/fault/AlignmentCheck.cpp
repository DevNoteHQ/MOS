
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void AlignmentCheck(struct cpu_state *state, uint64_t error)
{
	Text::Clear();
	Text::Simple::Write("FAULT!");
}
