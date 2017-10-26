
#ifndef CPU_CPU_H
#define CPU_CPU_H

#include <init/gdt.hpp>
#include <init/tss.hpp>

namespace CPU
{
	typedef struct{
		uint64_t rax;
		uint64_t rbx;
		uint64_t rcx;
		uint64_t rdx;
		uint64_t rsi;
		uint64_t rdi;
		uint64_t rbp;
		uint64_t r8;
		uint64_t r9;
		uint64_t r10;
		uint64_t r11;
		uint64_t r12;
		uint64_t r13;
		uint64_t r14;
		uint64_t r15;

		uint64_t iCode;
		uint64_t iError;

		uint64_t   rip;
		uint64_t   cs;
		uint64_t   rflags;
		uint64_t   rsp;
		uint64_t   ss;
	} __attribute__((__packed__)) State;

	typedef struct CPU_t {
		struct CPU_t *self;

		bool IsBSP;

		GDT::GDTR gdtr;
		uint64_t gdt[ENTRIES];

		TSS::TSS tss;

		uint64_t iTest;
	} CPU;

	void InitBSP();
}

extern "C" CPU::CPU *cpu_get();

#endif