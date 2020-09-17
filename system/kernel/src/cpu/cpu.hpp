
#ifndef CPU_CPU_H
#define CPU_CPU_H

#include <init/gdt.hpp>
#include <init/tss.hpp>

namespace CPU {
	typedef struct {
		uint64_t RAX;
		uint64_t RBX;
		uint64_t RCX;
		uint64_t RDX;
		uint64_t RSI;
		uint64_t RDI;
		uint64_t RBP;
		uint64_t R8;
		uint64_t R9;
		uint64_t R10;
		uint64_t R11;
		uint64_t R12;
		uint64_t R13;
		uint64_t R14;
		uint64_t R15;

		uint64_t Code;
		uint64_t Error;

		uint64_t   RIP;
		uint64_t   CS;
		uint64_t   RFLAGS;
		uint64_t   RSP;
		uint64_t   SS;
	} __attribute__((__packed__)) State;

	typedef struct CPU_t {
		struct CPU_t *self;

		bool IsBSP;

		GDT::GDTR gdtr;
		uint64_t gdt[ENTRIES];

		TSS::TSS tss;

		uint64_t Test;
	} __attribute__((__packed__)) CPU;

	void InitBSP();
}

extern "C" CPU::CPU *cpu_get();

#endif