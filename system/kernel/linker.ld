
OUTPUT_FORMAT(elf64-x86-64)
ENTRY(start)

HVMA = 0xFFFFFF0000000000;

SECTIONS
{
	. = 1M;
	_start = . + HVMA;
	_bin_start = . + HVMA;

	.init :
	{
		*(.init)
	}

	. += HVMA;

	.text : AT(ADDR(.text) - HVMA)
	{
		*(.text*)
	}

	.eh_frame : AT(ADDR(.eh_frame) - HVMA)
	{
		*(.eh_frame)
	}

	.rodata : AT(ADDR(.rodata) - HVMA)
	{
		*(.rodata*)
	}

	_bin_end = .;

	.data ALIGN(0x1000) : AT(ADDR(.data) - HVMA)
	{
		_data_start = .;
		start_ctors = .;
		*(.ctor*)
		end_ctors = .;
		start_dtors = .;
		*(.dtor*)
		end_dtors = .;
		*(.data*)
	}

	.bss : AT(ADDR(.bss) - HVMA)
	{
		*(.bss*)
		*(COMMON)
		_data_end = .;
	}

	.stack ALIGN(0x1000) : AT(ADDR(.stack) - HVMA)
	{
		_stack_start = .;
		*(.stack*)
		_stack_end = .;
	}

	_end = .;
}
