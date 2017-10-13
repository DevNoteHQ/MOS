
#include "keyboard.hpp"

#include <keys/keys.hpp>
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

			Keys::Init();
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

		char ScanCode(uint8_t iCode, uint8_t iTable)
		{
			if (iTable = 1)
			{
				switch (iCode)
				{
				case 0x02: return '1'; break;
				case 0x03: return '2'; break;
				case 0x04: return '3'; break;
				case 0x05: return '4'; break;
				case 0x06: return '5'; break;
				case 0x07: return '6'; break;
				case 0x08: return '7'; break;
				case 0x09: return '8'; break;
				case 0x0A: return '9'; break;
				case 0x0B: return '0'; break;
				case 0x0C: return '-'; break;
				case 0x0F: return '='; break;
				case 0x10: Keys::Q.IsPressed = true; Keys::UpdateFocusedElement(); Keys::Q.IsPressed = false; Keys::Q.IsHeld = true; Keys::UpdateFocusedElement(); break;
				}
			}
			if (iTable = 2)
			{
				//Table 2
			}
			if (iTable = 3)
			{
				//Table 3
			}
		}
	}
}