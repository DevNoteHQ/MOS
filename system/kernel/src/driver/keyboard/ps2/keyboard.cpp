
#include "keyboard.hpp"

#include <terminal/text.hpp>

#include <libMOS/convert/convert.hpp>

namespace Driver
{
	namespace Keyboard
	{
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

			SendCommand(0xF4);
		}

		static void SendCommand(uint8_t command)
		{
			do
			{
				while ((IO::inb(0x64) & 0x2)) 
				{
					asm volatile("nop");
				}
				IO::outb(0x60, command);
				while ((IO::inb(0x64) & 0x1) == 0)
				{
					asm volatile("nop");
				}
			} while (IO::inb(0x60) == 0xFE);
		}
	}
}