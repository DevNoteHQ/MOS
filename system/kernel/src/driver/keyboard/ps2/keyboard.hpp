
#ifndef PS2_KEYBOARD_HPP
#define PS2_KEYBOARD_HPP

namespace Driver
{
	namespace Keyboard
	{
		extern uint8_t iTable;
		void Init();
		void SendCommand(uint8_t iCommand);
	}
}

#endif