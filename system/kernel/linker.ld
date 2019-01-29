
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
		*(.initl)
	}

	. += HVMA;

	.text : AT(ADDR(.text) - HVMA)
	{
		*(.inith)
		*(.text*)
		*(.eh_frame)
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
		_data_end = .;
	}

	.bss ALIGN(0x1000) : AT(ADDR(.bss) - HVMA)
	{
		_bss_start = .;
		*(.bss*)
		*(COMMON)
		_bss_end = .;
	}

	_end = .;
}
