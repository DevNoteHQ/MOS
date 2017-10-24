
#include "syscall.hpp"

namespace System
{
	void* Syscall(uint64_t iCall, void* OtherArguments)
	{
		void *retval;
		asm volatile("syscall" : "=a"(retval) : "D"(iCall), "S"(OtherArguments) : "memory", "%rcx", "%r11");
		return retval;
	}
}
