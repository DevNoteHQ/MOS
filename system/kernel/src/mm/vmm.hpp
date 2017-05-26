


namespace Paging
{
	extern uint64_t *PL4;
	extern uint64_t *PL3;
	void init(void);
	extern "C" void SetCR3(uint64_t PL4);
}