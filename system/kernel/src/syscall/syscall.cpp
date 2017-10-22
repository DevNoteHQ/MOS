
#include "syscall.hpp"

#include <cpu/msr.hpp>
#include <init/gdt.hpp>

#define IA32_EFER	0xC0000080
#define MSR_STAR	0xC0000081
#define MSR_LSTAR	0xC0000082
#define MSR_CSTAR	0xC0000083

namespace Syscall
{
	void Init()
	{
		msr_write(IA32_EFER, msr_read(IA32_EFER) | 0x1);
		msr_write(MSR_STAR, (SLTR_USER_CODE_32 << 48) | (SLTR_KERNEL_CODE << 32));
		msr_write(MSR_CSTAR, &abort);
		msr_write(MSR_LSTAR, &Handler);
	}

	void Handler(uint64_t iCall, void* OtherArguments)
	{
		//asm volatile("push %rcx");
		//(*Handlers[iCall])(OtherArguments);
		//asm volatile("pop %rax");
		//asm volatile("sysret");
		//return (*Handlers[iCall])(OtherArguments);
	}
}