
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>

void DivideByZero(struct cpu_state *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT!");
}

void Debug(struct cpu_state *state)
{

}

void NonMaskableInterrupt(struct cpu_state *state)
{
	
}

void Breakpoint(struct cpu_state *state)
{
	
}

void Overflow(struct cpu_state *state)
{
	
}

void BoundRange(struct cpu_state *state)
{
	
}

void InvalidOpcode(struct cpu_state *state)
{
	
}

void DeviceNotAvailable(struct cpu_state *state)
{
	
}

void DoubleFault(struct cpu_state *state, uint64_t error)
{
	
}

void CoprocessorSegmentOverrun(struct cpu_state *state)
{
	
}

void InvalidTSS(struct cpu_state *state, uint64_t error)
{
	
}

void SegmentNotPresent(struct cpu_state *state, uint64_t error)
{
	
}

void StackFault(struct cpu_state *state, uint64_t error)
{
	
}

void GeneralProtection(struct cpu_state *state, uint64_t error)
{
	
}

void PageFault(struct cpu_state *state, uint64_t error)
{
	
}

void Fault0x0F(struct cpu_state *state)
{
	
}

void x87FloatingPoint(struct cpu_state *state)
{
	
}

void AlignmentCheck(struct cpu_state *state, uint64_t error)
{
	
}

void MachineCheck(struct cpu_state *state)
{
	
}

void SIMDFloatingPoint(struct cpu_state *state)
{
	
}

void Fault0x14(struct cpu_state *state)
{
	
}

void Fault0x15(struct cpu_state *state)
{
	
}

void Fault0x16(struct cpu_state *state)
{
	
}

void Fault0x17(struct cpu_state *state)
{
	
}

void Fault0x18(struct cpu_state *state)
{
	
}

void Fault0x19(struct cpu_state *state)
{
	
}

void Fault0x1A(struct cpu_state *state)
{
	
}

void Fault0x1B(struct cpu_state *state)
{
	
}

void Fault0x1C(struct cpu_state *state)
{
	
}

void Fault0x1D(struct cpu_state *state)
{
	
}

void SecuritySensitiveEvent(struct cpu_state *state, uint64_t error)
{
	
}

void Fault0x1F(struct cpu_state *state)
{

}