
#ifndef TERMINAL_KEYS_HPP
#define TERMINAL_KEYS_HPP

namespace Keys
{
	char ScanCode(uint8_t iTable, uint32_t iFlags, uint8_t iCode);

	extern void(*UpdateFocusedElement)(uint8_t, uint32_t, uint8_t);
}

#endif