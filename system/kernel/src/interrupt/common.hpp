

#ifndef INTERRUPT_COMMON_H
#define INTERRUPT_COMMON_H

#define INTERRUPTS		256
#define LASTFAULT		0x1F

#define FAULT00	0x00
#define FAULT01	0x01
#define FAULT02	0x02
#define FAULT03	0x03
#define FAULT04	0x04
#define FAULT05	0x05
#define FAULT06	0x06
#define FAULT07	0x07
#define FAULT08	0x08
#define FAULT09	0x09
#define FAULT10	0x0A
#define FAULT11	0x0B
#define FAULT12	0x0C
#define FAULT13	0x0D
#define FAULT14	0x0E
#define FAULT15	0x0F
#define FAULT16	0x10
#define FAULT17	0x11
#define FAULT18	0x12
#define FAULT19	0x13
#define FAULT20	0x14
#define FAULT21	0x15
#define FAULT22	0x16
#define FAULT23	0x17
#define FAULT24	0x18
#define FAULT25	0x19
#define FAULT26	0x1A
#define FAULT27	0x1B
#define FAULT28	0x1C
#define FAULT29	0x1D
#define FAULT30	0x1E
#define FAULT31	0x1F

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