
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void CoprocessorSegmentOverrun(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Coporcessor Segment Overrun!");
}
