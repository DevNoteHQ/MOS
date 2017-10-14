
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void DivideByZero(CPU::State *state)
{
	Console::Write("\nFAULT: Divide By Zero!");
	asm volatile("hlt");
}