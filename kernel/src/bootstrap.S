.code32

# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global bootstrap

bootstrap:
	
	mov $0x80000001, %eax
	cpuid                 			# CPUID Funktion 0x8000_0001 aufrufen
	and $0x20000000, %edx  			# LM-Bit isolieren
	test %edx, %edx         		# Wenn EDX jetzt 0 ist, war das LM-Bit nicht gesetzt
	jz long_unsupported   			# Long Mode nicht unterstützt!
 
	mov $0x00000001, %eax
	cpuid                 			# CPUID Funktion 0x0000_0001 aufrufen
	and $0x00000040, %edx  			# PAE-Bit isolieren
	test %edx, %edx         		# Wenn EDX jetzt 0 ist, war das PAE-Bit nicht gesetzt
	jz long_unsupported   			# Long Mode nicht unterstützt!
	jmp long_supported    			# Long Mode unterstützt!
	
	long_unsupported:
		cli
		hlt
	
	long_supported:
		mov %cr4, %eax            	# CR4 einlesen
		or $0x20, %eax            	# Physical Address Extension-Bit setzen
		mov %eax, %cr4            	# CR4 beschreiben
		
		mov $0x300000, %edi       	# Pagingstrukturen liegen bei 0x300000
 
		mov $0x30100F, %eax       	# Eintrag für die Page Directory Pointer Table
		stosl
		mov $0x03FF, %ecx
		xor %eax, %eax
		rep stosl               	# Rest mit Nullen auffüllen
 
		mov $0x30200F, %eax       	# Eintrag für die Page Directory Table
		stosl
		mov $0x03FF, %ecx
		xor %eax, %eax
		rep stosl               	# Rest mit Nullen auffüllen
 
		mov $0x0200, %ecx
		mov $0x008B, %esi         	# Die Attribute für die Einträge im Page Directory
 
		map.loop:               	# Hier werden die ersten 512 MiB Identity-Mapped
		mov %esi, %eax            	# Page eintragen
		stosl
		xor %eax, %eax            	# Jeder Eintrag besteht aus 8 Byte, also die oberen 4 auffüllen
		stosl
		add $0x200000, %esi       	# Wir benutzen hier 2 MiB Pages
		sub 1, %ecx
		jnz map.loop
 
		mov $0x300000, %eax       	# Die Adresse des Page Map Level 4 hier eintragen
		mov %eax, %cr3
 
		mov $0xC0000080, %ecx     	# Wir brauchen Zugriff aus das MSR-Register 0xC0000080
		rdmsr                   	# MSR-Register einlesen
		or $0x00000100, %eax			# Long Mode einschalten
		wrmsr                   	# MSR-Register beschreiben
 
		mov %cr0, %eax            	# CR0 einlesen
		or $0x80000000, %eax      	# Das Paging-Bit setzen
		mov %eax, %cr0	        	# CR0 beschreiben, ab jetzt sind wir im Long Mode
 
		jmp _start				# Far Jmp in 64-Bit Code Segment
	
