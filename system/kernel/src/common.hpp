

//Start and Stop from linker.ld
extern "C" uint64_t _start; // & of it should be 1M
extern "C" uint64_t _end; // & of it should be 1M + Kernelsize