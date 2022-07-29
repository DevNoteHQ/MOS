
#ifndef SCHEDULER_SCHEDULER_HPP
#define SCHEDULER_SCHEDULER_HPP

#include "task.hpp"
#include <cpu/cpu.hpp>
#include <video/console.hpp>
#include <assembler/stack.hpp>
#include <interrupt/apic.hpp>
#include <utility/convert/convert.hpp>

namespace Scheduler {
	class Scheduler {
	private:
		Task *tasks;
		int32_t taskIndex;
		uint32_t taskLength = 0;
		uint64_t systemStack;
		bool initDone = false;

		void saveSystemStack();
		void restoreSystemStack();
		void runSystemTask();
	public:
		void init(uint64_t stack);
		void addNewTask(Task task);
		void executeNextTask(CPU::State *state);
	};

	inline void Scheduler::executeNextTask(CPU::State *state) {
		if (this->initDone) {
			uint64_t currentStack = Assembler::Stack::getStackPointer();
			char test[70];
			Convert::ToString(currentStack, test, 16);
			Console::WriteLine(test);
			Convert::ToString(this->systemStack, test, 16);
			Console::WriteLine(test);
			this->restoreSystemStack();
			Console::WriteLine("Scheduler: Scheduling next task...");

			if (this->taskLength > 0) {
				this->tasks[this->taskIndex].saveState(state);
				if (this->taskIndex >= this->taskLength) {
					this->runSystemTask();
					this->taskIndex = 0;
				}
				this->tasks[this->taskIndex].restoreState(state);
			} else {
				Assembler::Stack::setStackPointer(currentStack);
			}

			this->saveSystemStack();
			Interrupt::APIC::Write(APIC_EOI, 0);
		}
	}

	inline void Scheduler::init(uint64_t stack) {
		this->systemStack = stack;
		this->initDone = true;
	}

	inline void Scheduler::saveSystemStack() {
		this->systemStack = Assembler::Stack::getStackPointer();
	}

	inline void Scheduler::restoreSystemStack() {
		Assembler::Stack::setStackPointer(this->systemStack);
	}

	extern Scheduler scheduler;
}

#endif