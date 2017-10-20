
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void LVT_Error(CPU::State *state)
{
	Interrupt::APIC::Write(APIC_EOI, 0);
}