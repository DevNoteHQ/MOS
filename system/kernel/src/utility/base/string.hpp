
#ifndef STRING_HPP
#define STRING_HPP

#include "array.hpp"

template<uint64_t S>
class String : public Array<char, S> {
};

namespace StringUtils {
	String<70> toString(uint64_t value, uint8_t base);
}
#endif