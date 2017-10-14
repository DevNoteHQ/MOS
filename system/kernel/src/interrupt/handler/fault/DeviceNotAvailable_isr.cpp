
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void DeviceNotAvailable(CPU::State *state)
{
	Console::Write("\nFAULT: Device Not Available!");
	asm volatile("hlt");
}
