
#ifndef MM_KMALLOC_HPP
#define MM_KMALLOC_HPP

void *kmalloc(uint64_t size);
void kfree(void *v_addr);

#endif