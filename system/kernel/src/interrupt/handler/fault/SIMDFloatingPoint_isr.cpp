
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void SIMDFloatingPoint(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: SIMD Floating Point!");
}
