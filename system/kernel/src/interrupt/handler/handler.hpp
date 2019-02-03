

#ifndef INTERRUPT_HANDLER_HANDLER_HPP
#define INTERRUPT_HANDLER_HANDLER_HPP

#include <cpu/cpu.hpp>

extern "C" void Interrupt_Handler(CPU::State *State);

namespace Interrupt::Handler
{
	extern void(*Handlers[256])(CPU::State*);
	void Set(uint8_t Code, void(*ThisHandler)(CPU::State*));
	void SetDefault();
}

#endif