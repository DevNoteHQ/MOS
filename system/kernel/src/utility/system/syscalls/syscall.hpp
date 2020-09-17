
#ifndef LIBMOS_SYSTEM_SYSCALLS_SYSCALL_HPP
#define LIBMOS_SYSTEM_SYSCALLS_SYSCALL_HPP



namespace System {
	void* Syscall(uint64_t iCall, void* OtherArguments);
}

#endif