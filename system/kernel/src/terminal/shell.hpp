
#ifndef TERMINAL_SHELL_HPP
#define TERMINAL_SHELL_HPP

namespace Shell
{
	extern char cBanner[];
	extern uint16_t iX;
	extern uint16_t iY;

	void Init();

	void Banner();

	void Clear();

	void Write(const char* s);
	void Write(char cC);

	void WriteLine(const char* s);
	void WriteLine(char cC);

	void Putc(char cC);

	void GetKeys(uint8_t iTable, uint32_t iFlags, uint8_t iCode);
}

#endif