
#include <driver/keyboard/ps2/keyboard.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>
#include <keys/keys.hpp>
#include <terminal/table/common.hpp>

uint32_t iFlags = 0;

__attribute__((interrupt)) void IRQ_01(CPU::State *state)
{
	uint8_t iScancode = IO::inb(0x60);

	switch (iScancode)
	{
	case 0x1D: iFlags = (iFlags | LCONTR); break;
	case 0x2A: iFlags = (iFlags | LSHIFT); break;
	case 0x36: iFlags = (iFlags | RSHIFT); break;
	case 0x38: iFlags = (iFlags | LALT); break;
	case 0x3A: Driver::Keyboard::SendCommand(0xED); Driver::Keyboard::SendCommand((iFlags ^ CAPSLOCK) >> 14); iFlags = (iFlags ^ CAPSLOCK); break;
	case 0x9D: iFlags = (iFlags & (~LCONTR)); break;
	case 0xAA: iFlags = (iFlags & (~LSHIFT)); break;
	case 0xB6: iFlags = (iFlags & (~RSHIFT)); break;
	case 0xB8: iFlags = (iFlags & (~LALT)); break;
	}

	(*Keys::UpdateFocusedElement)(1, iFlags, iScancode);

	IO::outb(0x20, 0x20);
}