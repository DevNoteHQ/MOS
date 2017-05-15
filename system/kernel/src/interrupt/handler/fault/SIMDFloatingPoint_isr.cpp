
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void SIMDFloatingPoint(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: SIMD Floating Point!");
}
