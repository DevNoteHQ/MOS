
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_09(CPU::State *state)
{
	Console::Write("\nIRQ_09!");

	IO::outb(0x20, 0x20);
}