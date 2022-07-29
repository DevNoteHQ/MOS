
#ifndef SCHEDULER_TASK_HPP
#define SCHEDULER_TASK_HPP

#include <cpu/cpu.hpp>

namespace Scheduler {
	class Task {
	private:
		uint8_t stack[4096];
		CPU::State internalState;
	public:
		Task(void (*executable)());
		void saveState(CPU::State *state);
		void restoreState(CPU::State *state);
	};
}

#endif