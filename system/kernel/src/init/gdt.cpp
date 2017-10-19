// Used for creating GDT segment descriptors in 64-bit integer form.

#include <init/gdt.hpp>
#include <init/tss.hpp>
#include <cpu/msr.hpp>

// Each define here is for a specific flag in the descriptor.
// Refer to the intel documentation for a description of what each one does.
#define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07) // Present
#define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)

#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(1)     | SEG_SIZE(0) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD

#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(0) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR

#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(1)     | SEG_SIZE(0) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD

#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(0) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR


#define GDT_ENTRIES 5
#define TSS_ENTRIES 1 //Temporary until i can get CPU-Count and Set a Entry for each CPU
#define ENTRIES (GDT_ENTRIES + 2 * TSS_ENTRIES)

#define TSS_FLAG 0x89

//#define TSS_LIMIT 0x67

namespace GDT
{
	uint64_t GDT64 = 0;
	uint64_t *gdt = &GDT64;

	void Set(int i, uint32_t base, uint32_t limit, uint16_t flag)
	{
		// Create the high 32 bit segment
		gdt[i] = limit & 0x000F0000;         // Set limit bits 19:16
		gdt[i] |= (flag << 8) & 0x00F0FF00;         // Set type, p, dpl, s, g, d/b, l and avl fields
		gdt[i] |= (base >> 16) & 0x000000FF;         // Set base bits 23:16
		gdt[i] |= base & 0xFF000000;         // Set base bits 31:24

												 // Shift by 32 to allow for low part of segment
		gdt[i] <<= 32;

		// Create the low 32 bit segment
		gdt[i] |= base << 16;                       // Set base bits 15:0
		gdt[i] |= limit & 0x0000FFFF;               // Set limit bits 15:0
	}

	void SetTSS(int i, uint64_t base, uint32_t limit, uint16_t flag)
	{
		gdt[i] = limit & 0x000F0000;         // Set limit bits 19:16
		gdt[i] |= (base >> 16) & 0x000000FF;         // Set base bits 23:16
		gdt[i] |= base & 0xFF000000;         // Set base bits 31:24
	}

	void Remake(void)
	{
		memset(gdt, 0, ENTRIES);

		uint64_t tss_base = (uint64_t)TSS::tss;
		uint32_t tss_limit = sizeof(*TSS::tss);

		Set(0, 0, 0, 0);
		Set(1, 0, 0xFFFFFFFF, (GDT_CODE_PL0));
		Set(2, 0, 0xFFFFFFFF, (GDT_DATA_PL0));
		Set(3, 0, 0xFFFFFFFF, (GDT_CODE_PL3));
		Set(4, 0, 0xFFFFFFFF, (GDT_DATA_PL3));
		SetTSS(5, tss_base, tss_limit, TSS_FLAG);

		uint64_t gs_base = msr_read(MSR_GS_BASE);

		GDTR_t gdtr;
		gdtr.limit = ENTRIES * 8 - 1;
		gdtr.pointer = gdt;

		reload(&gdtr, 0x0008, 0x0010);

		msr_write(MSR_GS_BASE, gs_base);
		msr_write(MSR_GS_KERNEL_BASE, gs_base);
	}
}

