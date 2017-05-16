/*
 * Copyright (c) 2011-2014 Graham Edgecombe <graham@grahamedgecombe.com>
 *
 */

#ifndef MEMORYMANAGEMENT_PHY32_H
#define MEMORYMANAGEMENT_PHY32_H

#include <stdint.h>

#define PHY32_OFFSET 0xFFFFFEFF00000000

/*
 * The kernel maps the first 4 gigabytes of physical memory into virtual
 * memory, this vastly simplifies dealing with the multiboot and ACPI
 * structures, as the RSDP and multiboot structures are always within the
 * 32-bit physical address space.
 *
 * This function converts a physical 32-bit pointer into a virtual 64-bit
 * pointer.
 */
void *phy32_to_virt(void *ptr);

/* Identical to the above, but works with integers instead, to avoid casts. */
uintptr_t aphy32_to_virt(uintptr_t addr);

#endif
