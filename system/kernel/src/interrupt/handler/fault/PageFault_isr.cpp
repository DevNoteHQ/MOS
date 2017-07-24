
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void PageFault(CPU::State *state, uint64_t error)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Page Fault!");
}
