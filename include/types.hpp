#ifndef TYPESC_H
#define TYPESC_H

#define true 1
#define false 0

typedef unsigned char 	uchar;
typedef unsigned short 	ushort;
typedef unsigned int 	uint;
typedef unsigned long long 	ulong;

typedef unsigned char byte;

typedef uint32_t irq_t;
typedef uint8_t intr_t;

typedef uint32_t cpu_acpi_id_t;
typedef uint32_t cpu_lapic_id_t;

typedef uint8_t ioapic_id_t;

#ifdef __cplusplus

enum class Color
{
	Black = 0x00,
	Blue = 0x01,
	Green = 0x02,
	Cyan = 0x03,
	Red = 0x04,
	Magenta = 0x05,
	Brown = 0x06,
	LightGray = 0x07,
	DarkGray = 0x08,
	LightBlue = 0x09,
	LightGreen = 0x0A,
	LightCyan = 0x0B,
	LightRed = 0x0C,
	LightMagenta = 0x0D,
	Yellow = 0x0E,
	White = 0x0F
};

#endif


#endif