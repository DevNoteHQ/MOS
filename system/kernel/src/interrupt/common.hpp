

#ifndef INTERRUPT_COMMON_H
#define INTERRUPT_COMMON_H

#define INTERRUPTS		256
#define LASTFAULT		0x1F
#define LASTIRQ			0x37
#define LASTSYSCALL		0xF9

#define NOT_INTR 0xFA

/* IPIs */
#define IPI_PANIC 0xFB
#define IPI_TLB   0xFC

/* LAPIC LVT interrupts */
#define LVT_TIMER 0xFD
#define LVT_ERROR 0xFE

/* LAPIC spurious interrupt */
#define SPURIOUS 0xFF

#endif