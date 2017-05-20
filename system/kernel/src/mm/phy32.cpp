/*
 * Copyright (c) 2011-2014 Graham Edgecombe <graham@grahamedgecombe.com>
 *
 */

#include <mm/phy32.hpp>

void *phy32_to_virt(void *ptr)
{
  uintptr_t i = (uintptr_t) ptr;
  i += PHY32_OFFSET;
  return (void *) i;
}

uintptr_t aphy32_to_virt(uintptr_t addr)
{
  return addr + PHY32_OFFSET;
}
