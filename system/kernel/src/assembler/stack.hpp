
#ifndef STACK_HPP
#define STACK_HPP

namespace Assembler::Stack {
	inline void setStackPointer(uint64_t pointer) {
		asm volatile("mov %0, %%rsp" :: "r" (pointer));
	}

	inline uint64_t getStackPointer() {
		uint64_t pointer;
		asm volatile("mov %%rsp, %0" : "=r" (pointer));
		return pointer;
	}
}

#endif