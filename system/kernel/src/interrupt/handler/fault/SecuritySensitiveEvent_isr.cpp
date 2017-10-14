
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void SecuritySensitiveEvent(CPU::State *state, uint64_t error)
{
	Console::Write("\nFAULT: Security-sensitive Event in Host!");
	asm volatile("hlt");
}
