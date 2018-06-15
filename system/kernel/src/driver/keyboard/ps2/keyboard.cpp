
#include "keyboard.hpp"

#include <font/keys.hpp>

namespace Driver
{
	namespace Keyboard
	{
		uint8_t iTable = 0;
		void Init()
		{
			while ((IO::inb(0x64) & 0x1))
			{
				IO::inb(0x60);
			}

			SendCommand(0xED);
			SendCommand(0);

			SendCommand(0xF3);
			SendCommand(0);

			SendCommand(0xF0);
			SendCommand(0x01);

			SendCommand(0xF4);
			
			Keys::Init();
		}

		void SendCommand(uint8_t iCommand)
		{
			do
			{
				while ((IO::inb(0x64) & 0x2)) {}
				IO::outb(0x60, iCommand);
				while ((IO::inb(0x64) & 0x1) == 0) {}
			} while (IO::inb(0x60) == 0xFE);
		}
	}
}