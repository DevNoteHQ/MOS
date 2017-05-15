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

#include <init/gdt.h>
#include <init/msr.h>
#include <init/cpu.h>

/* flags */
#define GDT_CS       0x18
#define GDT_DS       0x10
#define GDT_TSS      0x09
#define GDT_WRITABLE 0x02
#define GDT_USER     0x60
#define GDT_PRESENT  0x80

/* granularity */
#define GDT_LM       0x2

namespace GDT
{
	static void set(Descriptor *descriptor_a, uint16_t sel, uint8_t flags, uint8_t gran)
	{
		Descriptor *descriptor = &descriptor_a[sel / sizeof(*descriptor_a)];
		descriptor->flags = flags;
		descriptor->granularity = (gran << 4) | 0x0F;
		descriptor->limit_low = 0xFFFF;
	}

	static void setx(Descriptor *descriptor_a, uint16_t sel, uint8_t flags, uint8_t gran, uint64_t base, uint64_t limit)
	{
		XDescriptor *xdescriptor = (XDescriptor *)(&descriptor_a[sel / sizeof(*descriptor_a)]);
		xdescriptor->low.flags = flags;
		xdescriptor->low.granularity = (gran << 4) | ((limit >> 16) & 0x0F);
		xdescriptor->low.limit_low = limit & 0xFFFF;
		xdescriptor->low.base_low = base & 0xFFFF;
		xdescriptor->low.base_mid = ((base >> 16) & 0xFF);
		xdescriptor->low.base_high = ((base >> 24) & 0xFF);
		xdescriptor->high.base_xhigh = ((base >> 32) & 0xFFFFFFFF);
		xdescriptor->high.reserved = 0;
	}

	void init(void)
	{
		/* get this CPU's local data */
		CPU::cpu_t *cpu = CPU::cpu_get();

		/* get pointers to the GDT and GDTR */
		GDTR_t *gdtr = &cpu->gdtr;
		Descriptor *descriptors = cpu->descriptors;

		TSS::TSS_t *tss = &cpu->tss;
		uint64_t tss_base = (uint64_t)tss;
		uint64_t tss_limit = sizeof(*tss);

		memset(descriptors, 0, sizeof(*descriptors) * GDT_DESCRIPTORS);

		set (descriptors, SLTR_KERNEL_CODE, GDT_PRESENT | GDT_CS, GDT_LM);
		set (descriptors, SLTR_KERNEL_DATA, GDT_PRESENT | GDT_DS | GDT_WRITABLE, 0);
		set (descriptors, SLTR_USER_DATA, GDT_PRESENT | GDT_DS | GDT_USER | GDT_WRITABLE, 0);
		set (descriptors, SLTR_USER_CODE, GDT_PRESENT | GDT_CS | GDT_USER, GDT_LM);
		setx(descriptors, SLTR_TSS, GDT_PRESENT | GDT_TSS, 0, tss_base, tss_limit);

		uint64_t gs_base = msr_read(MSR_GS_BASE);

		gdtr->addr = (uint64_t)descriptors;
		gdtr->len = sizeof(*descriptors) * GDT_DESCRIPTORS - 1;
		gdtr_install(gdtr, SLTR_KERNEL_CODE, SLTR_KERNEL_DATA);

		msr_write(MSR_GS_BASE, gs_base);
		msr_write(MSR_GS_KERNEL_BASE, gs_base);
	}
}

