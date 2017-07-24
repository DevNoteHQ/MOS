
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Fault0x17(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Fault0x17!");
}
