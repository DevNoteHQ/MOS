
#ifndef PS2_KEYBOARD_HPP
#define PS2_KEYBOARD_HPP

namespace Driver
{
	namespace Keyboard
	{
		void Init();
		static void SendCommand(uint8_t command);
	}
}

#endif