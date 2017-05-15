
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void CoprocessorSegmentOverrun(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Coporcessor Segment Overrun!");
}
