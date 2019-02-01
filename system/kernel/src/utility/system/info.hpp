
#ifndef UTILITY_SYSTEM_INFO_HPP
#define UTILITY_SYSTEM_INFO_HPP

//References from linker.ld --- & of it returns the Address
extern "C" char _start;
extern "C" char _bin_start;
extern "C" char _bin_end;
extern "C" char _data_start;
extern "C" char _data_end;
extern "C" char _stack_start;
extern "C" char _stack_end;
extern "C" char _end;

extern "C" char *stack_bottom;
extern "C" char *stack_top;

namespace System::Info
{
	//Static Kernel Size
	const uint64_t StartAddress =		&_start;		//Returns the Kernel-Start-Address at 1M + HVMA
	const uint64_t BinStartAddress =	&_bin_start;	//Returns the Bin-Start-Address at 1M + HVMA + 4k Alignment
	const uint64_t BinEndAddress =		&_bin_end;		//Returns the Bin-End-Address at 1M + HVMA + Binary-Size
	const uint64_t DataStartAddress =	&_data_start;	//Returns the Data-Start-Address at 1M + HVMA + Binary-Size + 4k Alignment
	const uint64_t DataEndAddress =		&_data_end;		//Returns the Data-End-Address at 1M + HVMA + Binary-Size + Data-Size
	const uint64_t StackStartAddress =	&_stack_start;	//Returns the Stack-Bottom-Address
	const uint64_t StackEndAddress =	&_stack_end;	//Returns the Stack-Top-Address
	const uint64_t EndAddress =			&_end;			//Returns the Kernel-End-Address at 1M + Kernel-Size

	const uint64_t BinSize =	BinEndAddress - BinStartAddress;		//Returns the Binary-Size
	const uint64_t DataSize =	DataEndAddress - DataStartAddress;		//Returns the Data-Size
	const uint64_t StackSize =	StackEndAddress - StackStartAddress;	//Returns the BSS-Size
	const uint64_t KernelSize = EndAddress - StartAddress;				//Returns the Static-Kernel-Size
}

#endif