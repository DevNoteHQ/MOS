
OUTPUT_FORMAT(elf64-x86-64)
ENTRY(start)

SECTIONS
{
	. = 1M;
	_start = . ;

	.multiboot :
	{
		*(.multiboot)
	}

	.text ALIGN(0x1000) :
	{
		*(.text)
		*(.rodata)
	}

	.data ALIGN(0x1000) :
	{
		start_ctors = .;
		*(.ctor*)
		end_ctors = .;
		start_dtors = .;
		*(.dtor*)
		end_dtors = .;
		*(.data)
	}

	.bss :
	{
		_sbss = .;
		*(COMMON)
		*(.bss)
		_ebss = .;
	}

	_end = .;
}
