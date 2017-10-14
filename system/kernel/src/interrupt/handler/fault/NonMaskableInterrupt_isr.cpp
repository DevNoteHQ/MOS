
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void NonMaskableInterrupt(CPU::State *state)
{
	Console::Write("\nFAULT: Non Maskable Interrupt!");
	asm volatile("hlt");
}
