
#include <terminal/text.hpp>
#include <mm/phy32.hpp>

#define VIDEO_BUFFER 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define PAGES 5


namespace Text
{
	uint16_t iColor = 0;
	uint16_t *iVideo = 0;
	uint16_t iVideo_Buff[VGA_WIDTH * VGA_HEIGHT * PAGES];
	uint iX = 0;
	uint iY = 0;
	uint iScroll = 0;
	uint iMoved = 0;
	uint iPageRows = PAGES * VGA_HEIGHT;
	bool bMoved = false;

	void init()
	{
		iVideo = (uint16_t*)aphy32_to_virt(VIDEO_BUFFER);
		Clear();
		ForegroundColor(Color::White);
		BackgroundColor(Color::Black);
	}

	void Clear()
	{
		// Füllen des Bildschirms mit Leerzeichen
		for (int i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++)
		{
			iVideo[i] = (unsigned char)' ' | iColor;
		}
		for (int i = 0; i < (VGA_WIDTH * VGA_HEIGHT * PAGES); i++)
		{
			iVideo_Buff[i] = (unsigned char)' ' | iColor;
		}
		// Zurücksetzen der Textausgabe nach links oben
		iX = 0;
		iY = 0;
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
		int tmp;

		if (iY >= VGA_HEIGHT)
		{
			if ((iX >= VGA_WIDTH))
			{
				iX = 0;
				if (iScroll < iPageRows)
				{
					iScroll++;
				}
				else
				{
					iMoved++;
				}
				Scroll();
			}
		}
		else
		{
			if ((iX >= VGA_WIDTH))
			{
				iX = 0;
				iY++;
				iScroll++;
			}
		}
		iVideo[iX + VGA_WIDTH * iY] = (uint16_t)cC | iColor;
		iVideo_Buff[iX + VGA_WIDTH * iScroll++] = (uint16_t)cC | iColor;
		iX++;
	}

	void Scroll()
	{
		uint iSCount = iMoved * VGA_WIDTH;
		uint iCount = 0;
		for (; (iCount < VGA_WIDTH * VGA_HEIGHT) && (iSCount < VGA_WIDTH * VGA_HEIGHT); iCount++, iSCount++)
		{
			iVideo[iCount] = iVideo_Buff[iSCount + iScroll * VGA_WIDTH];
		}
		for (iSCount = 0; (iCount < VGA_WIDTH * VGA_HEIGHT) && (iSCount < iMoved * VGA_WIDTH); iCount++, iSCount++)
		{
			iVideo[iCount] = iVideo_Buff[iSCount + iScroll * VGA_WIDTH];
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
			int tmp;

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
		}
	}
}