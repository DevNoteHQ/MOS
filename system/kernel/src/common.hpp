
#ifndef COMMON_HPP
#define COMMON_HPP

#define HVMA 0xFFFFFF0000000000 //HVMA = Higher Virtual Memory Address

//Start and Stop from linker.ld
extern "C" char _start; // & of it should be 1M + HVMA
extern "C" char _end; // & of it should be 1M + Kernelsize + HVMA

#endif