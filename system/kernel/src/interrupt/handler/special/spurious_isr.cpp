
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Spurious(CPU::State *state)
{
	Text::WriteLine("Spurious!");
}