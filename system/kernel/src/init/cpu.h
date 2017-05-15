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

#ifndef INIT_CPU_H
#define INIT_CPU_H

#include <init/gdt.h>
#include <init/tss.h>
#include <util/list.h>

namespace CPU
{
	typedef struct scpu
	{
		/*
		 * cpu_get() relies on the fact that the first 8 bytes in the structure
		 * points to itself
		 */
		struct scpu *self;

		/*
		 * the hold count of the 'interrupt lock' (intr_enable/disable()).
		 * intr_stub() relies on the fact that the second 8 bytes in the structure
		 * are occupied by this field
		 */
		uint64_t intr_mask_count;

		/*
		 * the current thread running on this cpu. syscall_stub() relies on the fact
		 * that this is the third group of 8 bytes in this structure
		 */
		 //thread_t *thread;

		 /* global CPU list node */
		list_node_t node;

		/* BSP flag */
		bool bsp;

		/* the local APIC and ACPI ids of this processor */
		//cpu_lapic_id_t lapic_id;
		//cpu_acpi_id_t acpi_id;

		/* the gdt and gdtr for this processor */
		GDT::GDTR_t gdtr;
		GDT::Descriptor descriptors[GDT_DESCRIPTORS];

		/* the tss for this processor */
		TSS::TSS_t tss;

		/* current process running on this cpu */
		//proc_t *proc;

		/* idle thread for this cpu */
		//thread_t *idle_thread;

		/* number of APIC ticks per millisecond */
		uint32_t apic_ticks_per_ms;

		/* flags indicating if LINTn should be programmed as NMIs */
		bool apic_lint_nmi[2];
	} cpu_t;

	extern list_t cpulist;

	void init(void);
	//bool cpu_ap_init(cpu_lapic_id_t lapic_id, cpu_acpi_id_t acpi_id);
	void ap_install(cpu_t *cpu);
	extern "C" cpu_t *cpu_get(void);
}

#endif
