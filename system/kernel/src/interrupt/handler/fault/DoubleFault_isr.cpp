
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void DoubleFault(CPU::State *state, uint64_t error)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Double Fault!");
}
