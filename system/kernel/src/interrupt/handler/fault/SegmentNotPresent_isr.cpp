
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void SegmentNotPresent(CPU::State *state, uint64_t error)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Segment Not Present!");
}
