
#include <mm/vmm.hpp>

#include "console.hpp"
#include "text.hpp"

namespace Console
{
	Mode VideoMode;
	uint16_t iX = 0;
	uint16_t iY = 0;

	void Init()
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::Init();
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void Clear()
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::Clear();
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void Cursor()
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::Cursor();
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void Write(const char* s)
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::Write(s);
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void Write(char cC)
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::Write(cC);
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void WriteLine(const char* s)
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::WriteLine(s);
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void WriteLine(char cC)
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::WriteLine(cC);
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void ForegroundColor(Color color)
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::ForegroundColor(color);
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void BackgroundColor(Color color)
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::BackgroundColor(color);
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void Putc(char cC)
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::Putc(cC);
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}

	void UpdateScreenColor()
	{
		switch (VideoMode)
		{
		case Mode::Text:
			Text::UpdateScreenColor();
			break;
		case Mode::VGA:
			break;
		case Mode::VESA:
			break;
		case Mode::GUI:
			break;
		default:
			break;
		}
	}
}