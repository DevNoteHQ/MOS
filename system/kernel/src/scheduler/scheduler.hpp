
#ifndef SCHEDULER_SCHEDULER_HPP
#define SCHEDULER_SCHEDULER_HPP

#include "task.hpp"
#include <cpu/cpu.hpp>

namespace Scheduler {
	class Scheduler {
	private:
		Task *tasks;
		int32_t taskIndex;
		uint32_t taskLength;
	public:
		Scheduler();
		void addNewTask(Task task);
		void executeNextTask(CPU::State state);
		void runSystemTask();
	};

	extern Scheduler scheduler;
}

#endif