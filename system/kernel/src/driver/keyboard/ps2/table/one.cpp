
#include "one.hpp"
#include "common.hpp"

namespace Keys {
	namespace Table {
		char One(uint32_t iFlags, uint8_t iCode) {
			if ( ((CAPSLOCK & iFlags) != 0) ^ (((LSHIFT & iFlags) != 0) || ((RSHIFT & iFlags) != 0)) ) {
				switch (iCode) {
				case 0x01: return '\e'; break;
				case 0x02: return '!'; break;
				case 0x03: return '@'; break;
				case 0x04: return '#'; break;
				case 0x05: return '$'; break;
				case 0x06: return '%'; break;
				case 0x07: return '^'; break;
				case 0x08: return '&'; break;
				case 0x09: return '*'; break;
				case 0x0A: return '('; break;
				case 0x0B: return ')'; break;
				case 0x0C: return '_'; break;
				case 0x0D: return '+'; break;
				case 0x0E: return 0x7F; break;
				case 0x0F: return '\t'; break;
				case 0x10: return 'Q'; break;
				case 0x11: return 'W'; break;
				case 0x12: return 'E'; break;
				case 0x13: return 'R'; break;
				case 0x14: return 'T'; break;
				case 0x15: return 'Y'; break;
				case 0x16: return 'U'; break;
				case 0x17: return 'I'; break;
				case 0x18: return 'O'; break;
				case 0x19: return 'P'; break;
				case 0x1A: return '{'; break;
				case 0x1B: return '}'; break;
				case 0x1C: return '\n'; break;
				case 0x1E: return 'A'; break;
				case 0x1F: return 'S'; break;
				case 0x20: return 'D'; break;
				case 0x21: return 'F'; break;
				case 0x22: return 'G'; break;
				case 0x23: return 'H'; break;
				case 0x24: return 'J'; break;
				case 0x25: return 'K'; break;
				case 0x26: return 'L'; break;
				case 0x27: return ':'; break;
				case 0x28: return '/"'; break;
				case 0x29: return '~'; break;
				case 0x2B: return '|'; break;
				case 0x2C: return 'Z'; break;
				case 0x2D: return 'X'; break;
				case 0x2E: return 'C'; break;
				case 0x2F: return 'V'; break;
				case 0x30: return 'B'; break;
				case 0x31: return 'N'; break;
				case 0x32: return 'M'; break;
				case 0x33: return '<'; break;
				case 0x34: return '>'; break;
				case 0x35: return '?'; break;
				case 0x37: return '*'; break;
				case 0x39: return ' '; break;
				case 0x47: return '7'; break;
				case 0x48: return '8'; break;
				case 0x49: return '9'; break;
				case 0x4A: return '-'; break;
				case 0x4B: return '4'; break;
				case 0x4C: return '5'; break;
				case 0x4D: return '6'; break;
				case 0x4E: return '+'; break;
				case 0x4F: return '1'; break;
				case 0x50: return '2'; break;
				case 0x51: return '3'; break;
				case 0x52: return '0'; break;
				case 0x53: return '.'; break;
				case 0xE0: return '\n'; break;
				default:   return '\0'; break;
				}
			} else {
				switch (iCode)
				{
				case 0x01: return '\e'; break;
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
				case 0x0D: return '='; break;
				case 0x0E: return 0x7F; break;
				case 0x0F: return '\t'; break;
				case 0x10: return 'q'; break;
				case 0x11: return 'w'; break;
				case 0x12: return 'e'; break;
				case 0x13: return 'r'; break;
				case 0x14: return 't'; break;
				case 0x15: return 'y'; break;
				case 0x16: return 'u'; break;
				case 0x17: return 'i'; break;
				case 0x18: return 'o'; break;
				case 0x19: return 'p'; break;
				case 0x1A: return '['; break;
				case 0x1B: return ']'; break;
				case 0x1C: return '\n'; break;
				case 0x1E: return 'a'; break;
				case 0x1F: return 's'; break;
				case 0x20: return 'd'; break;
				case 0x21: return 'f'; break;
				case 0x22: return 'g'; break;
				case 0x23: return 'h'; break;
				case 0x24: return 'j'; break;
				case 0x25: return 'k'; break;
				case 0x26: return 'l'; break;
				case 0x27: return ';'; break;
				case 0x28: return '\''; break;
				case 0x29: return '`'; break;
				case 0x2B: return '\\'; break;
				case 0x2C: return 'z'; break;
				case 0x2D: return 'x'; break;
				case 0x2E: return 'c'; break;
				case 0x2F: return 'v'; break;
				case 0x30: return 'b'; break;
				case 0x31: return 'n'; break;
				case 0x32: return 'm'; break;
				case 0x33: return ','; break;
				case 0x34: return '.'; break;
				case 0x35: return '/'; break;
				case 0x37: return '*'; break;
				case 0x39: return ' '; break;
				case 0x47: return '7'; break;
				case 0x48: return '8'; break;
				case 0x49: return '9'; break;
				case 0x4A: return '-'; break;
				case 0x4B: return '4'; break;
				case 0x4C: return '5'; break;
				case 0x4D: return '6'; break;
				case 0x4E: return '+'; break;
				case 0x4F: return '1'; break;
				case 0x50: return '2'; break;
				case 0x51: return '3'; break;
				case 0x52: return '0'; break;
				case 0x53: return '.'; break;
				case 0xE0: return '\n'; break;
				default:   return '\0'; break;
				}
			}
			return '\0';
		}
	}
}