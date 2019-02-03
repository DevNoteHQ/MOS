
#include "init.hpp"

#include <timer/apit.hpp>

namespace Scheduler
{
	void Init()
	{
		Timer::APIT::Calibrate();
	}
}