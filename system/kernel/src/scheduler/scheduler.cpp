
#include "scheduler.hpp"
#include "task.hpp"
#include <video/console.hpp>

namespace Scheduler {
	Scheduler scheduler;

	Scheduler::Scheduler() {

	}

	void Scheduler::addNewTask(Task task) {
		
	}

	void Scheduler::executeNextTask(CPU::State state) {
		Console::WriteLine("Scheduler: Scheduling next task...");

		if (this->taskLength > 0) {
			this->tasks[this->taskIndex].saveState(state);
			if (this->taskIndex >= this->taskLength) {
				this->runSystemTask();
				this->taskIndex = 0;
			}
			this->tasks[this->taskIndex].restoreState();
		}
	}

	void Scheduler::runSystemTask() {

	}
}