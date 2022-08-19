
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <initializer_list.hpp>

namespace STD {
    template<typename E, uint64_t S>
    class Array {  
        public:
            E data[S];

            Array() = default;
            Array(const E *addr) {
                this->assignData(addr);
            }
            Array(std::initializer_list<E> list) {
                this->assignData(list);
            }

            void assignData(const E *addr) {
                for (int i = 0; i < S; i++) {
                    this->data[i] = addr[i];
                }
            }
            void assignData(std::initializer_list<E> list) {
                for (int i = 0; i < list.size(); i++) {
                    this->data[i] = list.begin()[i];
                }
            }
    };

    template <class T, class... U>
    Array(T, U...) -> Array<T, sizeof...(U)>;
}

#endif