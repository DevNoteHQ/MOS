
#ifndef CPU_CPU_H
#define CPU_CPU_H

#include <init/gdt.hpp>
#include <init/tss.hpp>

namespace CPU
{
	typedef struct{
		uint64_t iRAX;
		uint64_t iRBX;
		uint64_t iRCX;
		uint64_t iRDX;
		uint64_t iRSI;
		uint64_t iRDI;
		uint64_t iRBP;
		uint64_t iR8;
		uint64_t iR9;
		uint64_t iR10;
		uint64_t iR11;
		uint64_t iR12;
		uint64_t iR13;
		uint64_t iR14;
		uint64_t iR15;

		uint64_t iCode;
		uint64_t iError;

		uint64_t   iRIP;
		uint64_t   iCS;
		uint64_t   iRFLAGS;
		uint64_t   iRSP;
		uint64_t   iSS;
	} __attribute__((__packed__)) State;

	typedef struct CPU_t {
		struct CPU_t *self;

		bool IsBSP;

		GDT::GDTR gdtr;
		uint64_t gdt[ENTRIES];

		TSS::TSS tss;

		uint64_t iTest;
	} __attribute__((__packed__)) CPU;

	void InitBSP();
}

extern "C" CPU::CPU *cpu_get();

#endif