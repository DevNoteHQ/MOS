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

#ifndef INIT_MSR_H
#define INIT_MSR_H

#define MSR_EFER           0xC0000080
#define MSR_FS_BASE        0xC0000100
#define MSR_GS_BASE        0xC0000101
#define MSR_GS_KERNEL_BASE 0xC0000102
#define MSR_APIC_BASE      0x0000001B
#define MSR_STAR           0xC0000081
#define MSR_LSTAR          0xC0000082
#define MSR_CSTAR          0xC0000083
#define MSR_SFMASK         0xC0000084

#define APIC_BASE_ENABLED 0x800
#define APIC_BASE_X2_MODE 0x400
#define APIC_BASE_BSP     0x100

extern "C" uint64_t msr_read(uint32_t msr);
extern "C" void msr_write(uint32_t msr, uint64_t value);

#endif
