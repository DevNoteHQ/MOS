
#ifndef STRING_HPP
#define STRING_HPP

#include "array.hpp"
#include <initializer_list.hpp>

namespace STD {
    template<uint64_t S>
    class String : public Array<char, S> {
        public:
            String() = default;
            String(const char(&str)[S]) {
                this->assignData(str);
            }
            String(std::initializer_list<const char> list) {
                this->assignData(list);
            }
        
            void assignData(const char(&str)[S]) {
                for (int i = 0; i < S; i++) {
                    this->data[i] = str[i];
                    if (str[i] == '\0') {
                        break;
                    }
                }
            }
            void assignData(std::initializer_list<const char> list) {
                for (int i = 0; i < list.size(); i++) {
                    this->data[i] = list.begin()[i];
                }
            }

            void reverseIndexed(int lastElement) {
                int lastIndex = lastElement;
                for (int j = 0; j < lastIndex; j++, lastIndex--) {
                    char buffer = this->data[j];
                    this->data[j] = this->data[lastIndex];
                    this->data[lastIndex] = buffer;
                }
            }
    };

    template <uint64_t N>
    String(const char(&)[N]) -> String<N>;
}

namespace StringUtils {
	STD::String<65> toString(uint64_t value, uint8_t base);
}
#endif