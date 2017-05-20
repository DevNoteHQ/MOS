
[bits 32]
[extern init]
[extern abort]
[extern start_ctors]
[extern end_ctors]
[extern start_dtors]
[extern end_dtors]

; multiboot flag bitmasks
MB_FLAGS_ALIGN equ 0x1
MB_FLAGS_MMAP  equ 0x2
MB_FLAGS_VIDEO equ 0x4
MB_FLAGS_AOUT  equ 0x8000

; multiboot constants
MB_ALIGN          equ 8
MB_MAGIC          equ 0xE85250D6
MB_ARCH_I386      equ 0
MB_TAG_TERMINATOR equ 0
MB_TAG_INFO       equ 1
MB_TAG_ALIGN      equ 6
MB_INFO_MODULES   equ 3
MB_INFO_MMAP      equ 6

; includes initialization code and lower-half data
[section .multiboot align=MB_ALIGN]
; the multiboot header
mb_hdr_start:
	dd MB_MAGIC
	dd MB_ARCH_I386
	dd (mb_hdr_end - mb_hdr_start)
	dd (0 - MB_MAGIC - MB_ARCH_I386 - (mb_hdr_end - mb_hdr_start)) & 0xFFFFFFFF

	mb_tag_info_start:
		dw MB_TAG_INFO
		dw 0
		dd (mb_tag_info_end - mb_tag_info_start)
		dd MB_INFO_MODULES
		dd MB_INFO_MMAP
	mb_tag_info_end:

	mb_tag_align_start:
		dw MB_TAG_ALIGN
		dw 0
		dd (mb_tag_align_end - mb_tag_align_start)
	mb_tag_align_end:

	mb_tag_terminator_start:
		dw MB_TAG_TERMINATOR
		dw 0
		dd (mb_tag_terminator_end - mb_tag_terminator_start)
	mb_tag_terminator_end:
mb_hdr_end:

[section .data]
align 0x1000
GDT64:                           ; Global Descriptor Table (64-bit).
    .Null: equ $ - GDT64         ; The null descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 0                         ; Granularity.
    db 0                         ; Base (high).
    .Code: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 00100000b                 ; Granularity.
    db 0                         ; Base (high).
    .Data: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    .Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.

[section .text]
STACKSIZE  equ 0x4000

[global start]
start:
	cli
	mov edi, eax
	mov esi, ebx
	; push edi
	; push esi

	mov eax, 0x80000000    ; Set the A-register to 0x80000000.
	cpuid                  ; CPU identification.
	cmp eax, 0x80000001    ; Compare the A-register with 0x80000001.
	jb .NoLongMode         ; It is less, there is no long mode.

	mov eax, 0x80000001    ; Set the A-register to 0x80000001.
	cpuid                  ; CPU identification.
	test edx, 1 << 29      ; Test if the LM-bit, which is bit 29, is set in the D-register.
	jz .NoLongMode         ; They aren't, there is no long mode.

	mov edi, 0x1000			; Set the destination index to 0x1000.
    mov cr3, edi			; Set control register 3 to the destination index.
    xor eax, eax			; Nullify the A-register.
    mov ecx, 4096			; Set the C-register to 4096.
    rep stosd				; Clear the memory.
    mov edi, cr3			; Set the destination index to control register 3.

	mov DWORD [edi], 0x2003      ; Set the uint32_t at the destination index to 0x2003.
    add edi, 0x1000              ; Add 0x1000 to the destination index.
    mov DWORD [edi], 0x3003      ; Set the uint32_t at the destination index to 0x3003.
    add edi, 0x1000              ; Add 0x1000 to the destination index.

	mov ebx, 0x00000083			; Set the B-register to 0x000000083. 0x83 = PS = 1 (=> 2MiB Page) R/W = 1, P = 1
    mov ecx, 256				; Set the C-register to 256.
 
.SetEntry:
	mov DWORD [edi], ebx		; Set the uint32_t at the destination index to the B-register.
	add ebx, 0x200000			; Add 0x1000 to the B-register.
	add edi, 8					; Add eight to the destination index.
	loop .SetEntry				; Set the next entry.

	mov eax, cr4				; Set the A-register to control register 4.
	or eax, 1 << 5				; Set the PAE-bit, which is the 6th bit (bit 5).
	mov cr4, eax				; Set control register 4 to the A-register.

	mov ecx, 0xC0000080          ; Set the C-register to 0xC0000080, which is the EFER MSR.
	rdmsr                        ; Read from the model-specific register.
	or eax, 1 << 8               ; Set the LM-bit which is the 9th bit (bit 8).
	wrmsr                        ; Write to the model-specific register.

	mov eax, cr0                 ; Set the A-register to control register 0.
	or eax, 1 << 31              ; Set the PG-bit, which is the 32nd bit (bit 31).
	mov cr0, eax                 ; Set control register 0 to the A-register.

	lgdt [GDT64.Pointer]         ; Load the 64-bit global descriptor table.
	jmp GDT64.Code:Realm64       ; Set the code segment and enter 64-bit long mode.

.NoLongMode:
	cli
	hlt

[BITS 64]
Realm64:
	cli                           ; Clear the interrupt flag.
	mov ax, GDT64.Data            ; Set the A-register to the data descriptor.
	mov ds, ax                    ; Set the data segment to the A-register.
	mov es, ax                    ; Set the extra segment to the A-register.
	mov fs, ax                    ; Set the F-segment to the A-register.
	mov gs, ax                    ; Set the G-segment to the A-register.
	mov ss, ax                    ; Set the stack segment to the A-register.
	
	mov rsp, stack+STACKSIZE      ; set up the stack

	; call the kernel
	; - the arguments were moved into EDI and ESI at the start
	; - the DF has been reset by the code above - no CLD is required
	
	static_ctors_loop:
		mov rbx, start_ctors
		jmp .test
	.body:
		call [rbx]
		add rbx,4
	.test:
		cmp rbx, end_ctors
		jb .body
		push rbx
		call init                      ; call kernel proper
 
	static_dtors_loop:
		mov rbx, start_dtors
		jmp .test
	.body:
		call [rbx]
		add rbx,4
	.test:
		cmp rbx, end_dtors
		jb .body

	jmp abort

section .bss
align 32
stack:
	resb STACKSIZE