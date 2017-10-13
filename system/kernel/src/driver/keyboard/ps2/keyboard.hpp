
#ifndef PS2_KEYBOARD_HPP
#define PS2_KEYBOARD_HPP

namespace Driver
{
	namespace Keyboard
	{
		void Init();
		static void SendCommand(uint8_t command);
		char ScanCode(uint8_t iCode, uint8_t iTable);
	}
}

#endif