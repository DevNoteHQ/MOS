
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void CoprocessorSegmentOverrun(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Coporcessor Segment Overrun!");
}
