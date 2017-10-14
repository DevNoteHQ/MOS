
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void SIMDFloatingPoint(CPU::State *state)
{
	Console::Write("\nFAULT: SIMD Floating Point!");
	asm volatile("hlt");
}
