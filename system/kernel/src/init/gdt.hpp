/*
* Copyright (c) 2011-2014 Graham Edgecombe <graham@grahamedgecombe.com>
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef INIT_GDT_H
#define INIT_GDT_H

#define SLTR_NULL        0x0000
#define SLTR_KERNEL_CODE 0x0008
#define SLTR_KERNEL_DATA 0x0010
#define SLTR_USER_DATA   0x0018
#define SLTR_USER_CODE   0x0020
#define SLTR_TSS         0x0028 /* occupies two GDT descriptors */

#define RPL0 0x0
#define RPL1 0x1
#define RPL2 0x2
#define RPL3 0x3

#define GDT_DESCRIPTORS 7

namespace GDT
{
	typedef struct
	{
		uint16_t limit;
		uint64_t pointer;
	} __attribute__((__packed__)) GDTR_t;

	void remake(void);
	extern uint64_t GDT64;
	extern "C" void reload(uint64_t gdtr, uint16_t cs, uint16_t ds);
}

#endif
