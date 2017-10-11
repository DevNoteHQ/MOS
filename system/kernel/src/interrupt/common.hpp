

#ifndef INTERRUPT_COMMON_H
#define INTERRUPT_COMMON_H

#define INTERRUPTS		256
#define LASTFAULT		0x1F

#define IRQ00	0x20
#define IRQ01	0x21
#define IRQ02	0x22
#define IRQ03	0x23
#define IRQ04	0x24
#define IRQ05	0x25
#define IRQ06	0x26
#define IRQ07	0x27
#define IRQ08	0x28
#define IRQ09	0x29
#define IRQ10	0x2A
#define IRQ11	0x2B
#define IRQ12	0x2C
#define IRQ13	0x2D
#define IRQ14	0x2E
#define IRQ15	0x2F
#define IRQ16	0x30
#define IRQ17	0x31
#define IRQ18	0x32
#define IRQ19	0x33
#define IRQ20	0x34
#define IRQ21	0x35
#define IRQ22	0x36
#define IRQ23	0x37

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