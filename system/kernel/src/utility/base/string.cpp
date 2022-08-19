
#include "string.hpp"

namespace StringUtils {
	STD::String<65> toString(uint64_t value, uint8_t base) {
		STD::String<65> str;
		str.data[0] = '\0';
		if (base > 16 || base < 2) return str;
		uint64_t workingValue = value;
		int i = 1;
		for (; workingValue > 0; i++) {
			uint8_t digit = workingValue % base;
			uint8_t characterOffset = digit > 9 ? 0x37 : 0x30;
			str.data[i] = characterOffset + digit;
			workingValue /= base;
		}
		i--;
		str.reverseIndexed(i);
		return str;
	}
}
