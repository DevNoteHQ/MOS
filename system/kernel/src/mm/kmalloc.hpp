
#ifndef MM_KMALLOC_HPP
#define MM_KMALLOC_HPP

void *kmalloc(uint64_t size);
void *kmalloc(uint64_t size, uint16_t align);
void kfree(void *v_addr);

#endif