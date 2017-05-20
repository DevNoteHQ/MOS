/*
 *  Original:
 *  Copyright(c) 2011 - 2014 Graham Edgecombe <graham@grahamedgecombe.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 */

OUTPUT_FORMAT(elf64-x86-64)
ENTRY(start)

PAGE_SIZE  = 0x1000;
UPPER_MEM  = 0x100000;

SECTIONS
{
	. = UPPER_MEM;
	_start = . ;

	.multiboot :
	{
		*(.multiboot)
	}

	.text ALIGN(PAGE_SIZE) :
	{
		*(.text)
		*(.rodata)
	}

	.data ALIGN(PAGE_SIZE) :
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
