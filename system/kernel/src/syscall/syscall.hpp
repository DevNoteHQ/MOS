
#ifndef SYSCALL_SYSCALL_HPP
#define SYSCALL_SYSCALL_HPP

namespace Syscall
{
	void Init();
	void Handler(uint64_t iCall, void* OtherArguments);
}

#endif