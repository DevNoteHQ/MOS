
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_21(CPU::State *state)
{
	Console::Write("\nIRQ_21!");

	IO::outb(0x20, 0x20);
}