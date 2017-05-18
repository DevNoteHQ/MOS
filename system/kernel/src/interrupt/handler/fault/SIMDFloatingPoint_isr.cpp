
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void SIMDFloatingPoint(CPU::State *state)
{
	//Text::Clear();
	Text::Simple::Write("FAULT: SIMD Floating Point!");
}
