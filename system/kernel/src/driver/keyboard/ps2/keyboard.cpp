
#include "keyboard.hpp"
#include "keys.hpp"
#include <assembler/io_ports.hpp>

namespace Driver {
	namespace Keyboard {
		uint8_t iTable = 0;
		void Init() {
			while ((Assembler::IO::Ports::inb(0x64) & 0x1)) {
				Assembler::IO::Ports::inb(0x60);
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

		void SendCommand(uint8_t iCommand) {
			do {
				while ((Assembler::IO::Ports::inb(0x64) & 0x2)) {}
				Assembler::IO::Ports::outb(0x60, iCommand);
				while ((Assembler::IO::Ports::inb(0x64) & 0x1) == 0) {}
			} while (Assembler::IO::Ports::inb(0x60) == 0xFE);
		}
	}
}