
#include "string.hpp"

template<uint64_t S>
String<S>::String(const char(&str)[S]) {
	this->assignData(str);
}

template<uint64_t S>
void String<S>::assignData(const char(&str)[S]) {
	for (int i = 0; i < S; i++) {
		this->data[i] = str[i];
		if (str[i] == '\0') {
			break;
		}
	}
}

template<uint64_t S>
void String<S>::reverseIndexed(int lastElement) {
	int lastIndex = lastElement;
	for (int j = 0; j < lastIndex; j++, lastIndex--) {
		char buffer = this->data[j];
		this->data[j] = this->data[lastIndex];
		this->data[lastIndex] = buffer;
	}
}

namespace StringUtils {
	String<65> toString(uint64_t value, uint8_t base) {
	    String<65> str;
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
