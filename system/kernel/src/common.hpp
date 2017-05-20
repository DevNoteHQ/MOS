

//Start and Stop from linker.ld
extern "C" uint64_t _start; // & of it should be 1M + VMA_KERNEL = 1M + 0xFFFFFFFF80000000
extern "C" uint64_t _end; // & of it should be 1M + Kernelsize + VMA_KERNEL = 1M + Kernelsize + 0xFFFFFFFF80000000

extern "C" uint64_t _rstart; // & of it should be 1M
extern "C" uint64_t _rend; // & of it should be 1M + Kernelsize