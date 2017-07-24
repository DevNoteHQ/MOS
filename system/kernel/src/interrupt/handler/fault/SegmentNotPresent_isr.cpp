
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void SegmentNotPresent(CPU::State *state, uint64_t error)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Segment Not Present!");
}
