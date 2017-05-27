
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void DeviceNotAvailable(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Device Not Available!");
}
