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

#ifndef INIT_TSS_HPP
#define INIT_TSS_HPP

namespace TSS
{
	typedef struct
	{
		uint32_t reserved0;
		uint64_t rsp0;
		uint64_t rsp1;
		uint64_t rsp2;
		uint64_t reserved1;
		uint64_t ist1;
		uint64_t ist2;
		uint64_t ist3;
		uint64_t ist4;
		uint64_t ist5;
		uint64_t ist6;
		uint64_t ist7;
		uint64_t reserved2;
		uint16_t reserved3;
		uint16_t iomap_base;
	} __attribute__((__packed__)) TSS_t;

	extern TSS_t *tss;
	void Init();
	void SetRsp0(uint64_t rsp0);
	extern "C" void tss_install(uint16_t selector);
}

#endif
