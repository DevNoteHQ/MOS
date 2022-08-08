
#include "string.hpp"

namespace StringUtils {
	String<70> toString(uint64_t value, uint8_t base) {
		if (base > 16) return;
		uint64_t workingValue = value;
		String<70> str;
		str.data[0] = '\0';
		int i = 1;
		for (; workingValue > 0; i++) {
			uint8_t digit = workingValue % base;
			uint8_t characterOffset = digit > 9 ? 0x37 : 0x30;
			str.data[i] = characterOffset + digit;
			workingValue /= base;
		}
		i--;
		for (int j = 0; j < i; j++, i--) {
			char buffer = str.data[j];
			str.data[j] = str.data[i];
			str.data[i] = buffer;
		}
		return str;
	}
}
