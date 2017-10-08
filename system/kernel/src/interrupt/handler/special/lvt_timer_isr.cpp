
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void LVT_Timer(CPU::State *state)
{
	Text::WriteLine("TIMER!");
}