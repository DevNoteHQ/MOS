
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_14(CPU::State *state)
{
	Console::Write("\nIRQ_14!");

	IO::outb(0x20, 0x20);
}