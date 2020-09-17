
#include <mm/vmm/conv.hpp>

#include "console.hpp"
#include "text.hpp"

#define VIDEO_BUFFER 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define PAGES 5

namespace Text {
	uint16_t iColor = 0;
	uint16_t *iVideo = 0;
	
	uint16_t iX = 0;
	uint16_t iY = 0;

	void Init() {
		iVideo = VMM::ToVMA_I(VIDEO_BUFFER);
		ForegroundColor(Color::LightGray);
		BackgroundColor(Color::Black);
		iX = 0;
		iY = 0;
		Clear();
	}

	void Clear() {
		// F�llen des Bildschirms mit Leerzeichen
		for (uint32_t i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++) {
			iVideo[i] = (unsigned char)' ' | iColor;
		}
	}

	void Cursor() {
		// The screen is 80 characters wide...
		uint16_t iCursor = iY * 80 + iX;
		IO::outb(0x3D4, 14);					// Tell the VGA board we are setting the high cursor byte.
		IO::outb(0x3D5, iCursor >> 8);		// Send the high cursor byte.
		IO::outb(0x3D4, 15);					// Tell the VGA board we are setting the low cursor byte.
		IO::outb(0x3D5, iCursor);			// Send the low cursor byte.
	}

	void Write(const char* s) {
		// F�r jedes einzelne Zeichen wird put() aufgerufen
		while (*s != '\0') {
			Putc(*s++);
		}
	}

	void Write(char cC) {
		Putc(cC);
	}

	void WriteLine(const char* s) {
		// F�r jedes einzelne Zeichen wird put() aufgerufen
		while (*s != '\0') {
			Putc(*s++);
		}
		Putc('\n');
	}

	void WriteLine(char cC) {
		Putc(cC);
		Putc('\n');
	}

	void ForegroundColor(Color color) {
		iColor = (static_cast<uint16_t>(color) << 8) | (iColor & 0xF000);
	}

	void BackgroundColor(Color color) {
		iColor = (static_cast<uint16_t>(color) << 12) | (iColor & 0x0F00);
	}

	void Putc(char cC) {
		switch (cC) {
		case 0x7F:
			if (iX == 0) {
				if(iY != 0) {
					iY--;
					iX = VGA_WIDTH - 1;
					Putc(' ');
					iX = VGA_WIDTH - 1;
					Cursor();
				}
			} else {
				iX--;
				Putc(' ');
				iX--;
				Cursor();
			}
			break;
		case '\n':
			iX = 0;
			if (iY >= VGA_HEIGHT - 1) {
				Scroll();
			} else {
				iY++;
			}
			Cursor();
			break;
		case '\0':
			break;
		default:
			if (iY >= VGA_HEIGHT - 1) {
				if (iX >= VGA_WIDTH) {
					iX = 0;
					Scroll();
				}
			} else {
				if (iX >= VGA_WIDTH) {
					iX = 0;
					iY++;
				}
			}
			iVideo[iX + VGA_WIDTH * iY] = (uint16_t)cC | iColor;
			iX++;
			Cursor();
			break;
		}
	}

	void Scroll() {
		uint16_t iYC = 0;
		uint16_t iXC = 0;
		for (; (iYC < (VGA_HEIGHT - 1)); iYC++) {
			for (iXC = 0; iXC < VGA_WIDTH; iXC++)
				iVideo[iYC * VGA_WIDTH + iXC] = iVideo[(iYC + 1) * VGA_WIDTH + iXC];
		}
		for (iXC = 0; iXC < VGA_WIDTH; iXC++) {
			iVideo[(VGA_HEIGHT - 1) * VGA_WIDTH + iXC] = (unsigned char)' ' | iColor;
		}
	}

	void UpdateScreenColor() {
		for (uint32_t i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++) {
			iVideo[i] |= iColor;
		}
	}
}