#include "video.h"

//Video screen;

Video::Video()
	: m_videomem((uint16_t*)0xb8000), m_off(0), m_pos(0), m_color(0x0700)
{
	//Bildschirm leeren
	clear();
}

Video::~Video() {
}

void Video::clear() {
	// Füllen des Bildschirms mit Leerzeichen
	for (int i = 0;i < (80 * 25);i++)
		m_videomem[i] = (unsigned char)' ' | m_color;

	// Zurücksetzen der Textausgabe nach links oben
	m_pos = 0;
	m_off = 0;
}

Video& Video::operator << (const char* s) {
	// Für jedes einzelne Zeichen wird put() aufgerufen
	while (*s != '\0')
		put(*s++);

	return *this;
}

Video& Video::operator << (color::type color) {
	m_color = (static_cast<uint16_t>(color) << 8) | (m_color & 0xF000);
	return *this;
}

Video& Video::operator << (const background& color) {
	m_color = (static_cast<uint16_t>(color.m_color) << 12) | (m_color & 0x0F00);
	return *this;
}

void Video::put(char c) {
	// Wenn die Textausgabe den rechten...
	if (m_pos >= 80) {
		m_pos = 0;
		m_off += 80;
	}

	// ...oder den unteren Bildschirmrand erreicht, gibt es
	// einen Umbruch bzw. es wird aufgeräumt.
	if (m_off >= (80 * 25))
		clear();

	// Setzen des Zeichens und der Farbe in den Videospeicher
	m_videomem[m_off + m_pos] = (uint16_t)c | m_color;
	m_pos++;
}