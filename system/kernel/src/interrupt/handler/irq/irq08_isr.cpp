
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_08(CPU::State *state)
{
	Console::Write("\nIRQ_08!");

	IO::outb(0x20, 0x20);
}