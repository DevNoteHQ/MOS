
#ifndef KEYS_KEYS_HPP
#define KEYS_KEYS_HPP

namespace Keys
{
	void Init();
	char ScanCode(uint8_t iTable, uint32_t iFlags, uint8_t iCode);
	void GetKeys(uint8_t iTable, uint32_t iFlags, uint8_t iCode);
	
	extern void (*UpdateFocusedElement)(uint8_t, uint32_t, uint8_t);
}

#endif