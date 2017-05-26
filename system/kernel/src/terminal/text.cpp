
#include <terminal/text.hpp>
#include <assembler.hpp>

#define VIDEO_BUFFER 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define PAGES 5

namespace Text
{
	uint16_t iColor = 0;
	uint16_t *iVideo = VIDEO_BUFFER;
	uint16_t iVideo_Buff[VGA_HEIGHT][VGA_WIDTH];
	uint16_t iX = 0;
	uint16_t iY = 0;
	uint16_t iBY = 0;
	uint16_t iMoved = 0;

	void init()
	{
		ForegroundColor(Color::White);
		BackgroundColor(Color::Black);
		iX = 0;
		iY = 0;
		Clear();
		ClearBuffer();
	}

	void Clear()
	{
		// Füllen des Bildschirms mit Leerzeichen
		for (uint32_t i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++)
		{
			iVideo[i] = (unsigned char)' ' | iColor;
		}
	}

	void ClearBuffer()
	{
		for (uint16_t iYC = 0; iYC < VGA_HEIGHT; iYC++)
		{
			for (uint16_t iXC = 0; iXC < VGA_WIDTH; iXC++)
				iVideo_Buff[iYC][iXC] = (unsigned char)' ' | iColor;
		}
	}

	void Cursor()
	{
		// The screen is 80 characters wide...
		uint16_t iCursor = iY * 80 + iX;
		Assembler::IO::outb(0x3D4, 14);					// Tell the VGA board we are setting the high cursor byte.
		Assembler::IO::outb(0x3D5, iCursor >> 8);		// Send the high cursor byte.
		Assembler::IO::outb(0x3D4, 15);					// Tell the VGA board we are setting the low cursor byte.
		Assembler::IO::outb(0x3D5, iCursor);			// Send the low cursor byte.
	}

	void Write(const char* s)
	{
		// Für jedes einzelne Zeichen wird put() aufgerufen
		while (*s != '\0')
			Putc(*s++);
	}

	void ForegroundColor(Color color)
	{
		iColor = (static_cast<uint16_t>(color) << 8) | (iColor & 0xF000);
	}

	void BackgroundColor(Color color)
	{
		iColor = (static_cast<uint16_t>(color) << 12) | (iColor & 0x0F00);
	}

	void Putc(char cC)
	{
		if (iY >= VGA_HEIGHT - 1)
		{
			if (iX >= VGA_WIDTH)
			{
				iX = 0;
				iMoved++;
				iBY++;
				if (iMoved >= VGA_HEIGHT)
				{
					iMoved = 0;
				}
				Scroll();
			}
		}
		else
		{
			if (iX >= VGA_WIDTH)
			{
				iX = 0;
				iY++;
				iBY++;
			}
		}
		if (iBY >= VGA_HEIGHT)
		{
			iBY = 0;
		}
		iVideo[iX + VGA_WIDTH * iY] = (uint16_t)cC | iColor;
		iVideo_Buff[iBY][iX] = (uint16_t)cC | iColor;
		iX++;
		Cursor();
	}

	void Scroll(void)
	{
		uint16_t iYSC = iMoved;
		uint16_t iYC = 0;
		uint16_t iXC = 0;
		for (iXC = 0; iXC < VGA_WIDTH; iXC++)
		{
			iVideo_Buff[iMoved - 1][iXC] = (unsigned char)' ' | iColor;
		}
		for (; (iYC < VGA_HEIGHT) && (iYSC < VGA_HEIGHT); iYC++, iYSC++)
		{
			for(iXC = 0; iXC < VGA_WIDTH; iXC++)
				iVideo[iYC * VGA_WIDTH + iXC] = iVideo_Buff[iYSC][iXC];
		}
		for (iYSC = 0; (iYC < VGA_HEIGHT) && (iYSC < VGA_HEIGHT); iYC++, iYSC++)
		{
			for (iXC = 0; iXC < VGA_WIDTH; iXC++)
				iVideo[iYC * VGA_WIDTH + iXC] = iVideo_Buff[iYSC][iXC];
		}
	}
}

namespace Text
{
	namespace Simple
	{
		void Write(const char* s)
		{
			// Für jedes einzelne Zeichen wird put() aufgerufen
			while (*s != '\0')
				Putc(*s++);
		}

		void Putc(char cC)
		{
			if ((iX >= VGA_WIDTH))
			{
				iX = 0;
				iY++;
			}
			if (iY >= VGA_HEIGHT)
			{
				iY = 0;
			}
			iVideo[iX + VGA_WIDTH * iY] = (uint16_t)cC | iColor;
			iX++;
			Cursor();
		}
	}
}