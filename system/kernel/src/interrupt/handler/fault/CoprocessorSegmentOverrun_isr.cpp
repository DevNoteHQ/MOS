
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void CoprocessorSegmentOverrun(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Coporcessor Segment Overrun!");
}
