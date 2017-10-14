
#include <mm/vmm.hpp>

#include "console.hpp"
#include "keys.hpp"
#include "shell.hpp"

namespace Shell
{
	char cBanner[] = "MOS> ";

	void Init()
	{
		Console::WriteLine("--------------------------------------------------------------------------------");
		Console::WriteLine("----------------  Hello! This is MOS - Modern Operating System  ----------------");
		Console::WriteLine("--------------------------------------------------------------------------------");
		Console::WriteLine("");
		Banner();
	}

	void Banner()
	{
		Console::Write(cBanner);
	}

	void Clear()
	{
		Console::Clear();
		Banner();
	}

	void Write(const char* s)
	{
		if (Console::iX == 0) Banner();
		Console::Write(s);
	}

	void Write(char cC)
	{
		if (Console::iX == 0) Banner();
		Console::Write(cC);
	}

	void WriteLine(const char* s)
	{
		if (Console::iX == 0) Banner();
		Console::WriteLine(s);
	}

	void WriteLine(char cC)
	{
		if (Console::iX == 0) Banner();
		Console::WriteLine(cC);
	}

	void Putc(char cC)
	{
		if(Console::iX == 0) Banner();
		Console::Putc(cC);
	}

	void GetKeys(uint8_t iTable, uint32_t iFlags, uint8_t iCode)
	{
		Write(Keys::ScanCode(iTable, iFlags, iCode));
	}
}