
OUTPUT_FORMAT(elf64-x86-64)
ENTRY(start)

HVMA = 0xFFFFFF0000000000;

SECTIONS
{
	. = 1M;
	_start = . + HVMA;

	.init :
	{
		*(.initl)
	}

	. += HVMA;

	.text ALIGN(0x1000) : AT(ADDR(.text) - HVMA)
	{
		*(.inith)
		*(.text)
	}

	.data ALIGN(0x1000) : AT(ADDR(.data) - HVMA)
	{
		start_ctors = . - HVMA;
		*(.ctor*)
		end_ctors = . - HVMA;
		start_dtors = . - HVMA;
		*(.dtor*)
		end_dtors = . - HVMA;
		*(.data)
	}

	.rodata ALIGN(0x1000) : AT(ADDR(.rodata) - HVMA)
	{
		*(.rodata)
	}

	.bss ALIGN(0x1000) : AT(ADDR(.bss) - HVMA)
	{
		_sbss = .;
		*(COMMON)
		*(.bss)
		_ebss = .;
	}

	_end = .;
}
