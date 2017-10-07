
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void spurious(CPU::State *state)
{
	Text::WriteLine("Spurious!");
}