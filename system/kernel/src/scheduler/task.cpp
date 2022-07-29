
#include "task.hpp"

namespace Scheduler {
	Task::Task(void (*executable)()) {
		this->internalState.RSP = &this->stack;
		this->internalState.RIP = executable;
	}

	void Task::saveState(CPU::State *state) {
		memcpy(&this->internalState, state, sizeof(CPU::State));
	}

	void Task::restoreState(CPU::State *state) {
		memcpy(state, &this->internalState, sizeof(CPU::State));
	}
}