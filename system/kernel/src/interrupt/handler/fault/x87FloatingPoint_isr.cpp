
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void x87FloatingPoint(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: x87 Floating Point!");
}
