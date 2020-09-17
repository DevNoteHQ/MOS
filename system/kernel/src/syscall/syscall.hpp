
#ifndef SYSCALL_SYSCALL_HPP
#define SYSCALL_SYSCALL_HPP

namespace Syscall {
	extern void(*Handlers[400])(void*);

	void Init();
	void Handler(uint64_t iCall, void* OtherArguments);
}

#endif