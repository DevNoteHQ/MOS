
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void X87FloatingPoint(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: x87 Floating Point!");
}
