
#ifndef INTERRUPT_APIC_HPP
#define INTERRUPT_APIC_HPP

#define MSR_X2APIC_MMIO 0x800

#define APIC_BASE_ENABLED 0x800
#define APIC_BASE_X2_MODE 0x400
#define APIC_BASE_BSP     0x100

/* common registers */
#define APIC_TPR        0x08
#define APIC_EOI        0x0B
#define APIC_SVR        0x0F
#define APIC_ESR        0x28
#define APIC_LVT_TIMER  0x32
#define APIC_LVT_LINT0  0x35
#define APIC_LVT_LINT1  0x36
#define APIC_LVT_ERROR  0x37
#define APIC_TIMER_ICR  0x38
#define APIC_TIMER_CCR  0x39
#define APIC_TIMER_DCR  0x3E

/* xAPIC only registers */
#define XAPIC_ICRL      0x30
#define XAPIC_ICRH      0x31

/* x2APIC only registers */
#define X2APIC_ICR      0x30
#define X2APIC_SELF_IPI 0x3F

/* LVT flags */
#define LVT_MASKED			0x00010000
#define LVT_TYPE_FIXED		0x00000000
#define LVT_TYPE_SMI		0x00000200
#define LVT_TYPE_NMI		0x00000400
#define LVT_TYPE_EXTINT		0x00000700
#define LVT_DELIVS			0x00001000
#define LVT_REMOTE_IRR		0x00004000
#define LVT_TRIGGER_LEVEL	0x00008000
#define LVT_TRIGGER_EDGE	0x00000000
#define LVT_TIMER_TSC		0x00040000
#define LVT_TIMER_PERIODIC	0x00020000
#define LVT_TIMER_ONE_SHOT	0x00000000

/* SVR flags */
#define SVR_ENABLED 0x100

/* ICR flags */
#define ICR_TYPE_FIXED        0x00000000
#define ICR_TYPE_SMI          0x00000200
#define ICR_TYPE_NMI          0x00000400
#define ICR_TYPE_INIT         0x00000500
#define ICR_TYPE_STARTUP      0x00000600
#define ICR_PHYSICAL          0x00000000
#define ICR_LOGICAL           0x00000800
#define ICR_DELIVS            0x00001000
#define ICR_DEASSERT          0x00000000
#define ICR_ASSERT            0x00004000
#define ICR_TRIGGER_EDGE      0x00000000
#define ICR_TRIGGER_LEVEL     0x00008000
#define ICR_DEST_SELF         0x00040000
#define ICR_DEST_ALL          0x00080000
#define ICR_DEST_ALL_EXC_SELF 0x000C0000

/* DCR values */
#define DCR_1   0xB
#define DCR_2   0x0
#define DCR_4   0x1
#define DCR_8   0x2
#define DCR_16  0x3
#define DCR_32  0x8
#define DCR_64  0x9
#define DCR_128 0xA

namespace Interrupt::APIC {
	extern uint32_t *MMIO;
	void Init();
	void Write(size_t reg, uint64_t val);
	uint64_t Read(size_t reg);
	extern bool X2APIC;
}

#endif