
#include "array.hpp"

template<typename E, uint64_t S>
Array<E,S>::Array(const E* addr) {
	this->assignData(addr);
}

template<typename E, uint64_t S>
void Array<E,S>::assignData(const E* addr) {
	for (int i = 0; i < S; i++) {
		this->data[i] = addr[i];
	}
}
