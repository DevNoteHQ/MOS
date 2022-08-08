
#ifndef STRING_HPP
#define STRING_HPP

#include "array.hpp"

template<uint64_t S>
class String : public Array<char, S> {
    public:
        String() = default;
        
        String(const char(&str)[S]);
    
        void assignData(const char(&str)[S]);
        
        void reverseIndexed(int lastElement);
};

namespace StringUtils {
	String<65> toString(uint64_t value, uint8_t base);
}
#endif