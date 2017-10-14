
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void X87FloatingPoint(CPU::State *state)
{
	Console::Write("\nFAULT: x87 Floating Point!");
	asm volatile("hlt");
}
