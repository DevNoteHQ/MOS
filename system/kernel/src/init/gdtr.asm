
[global gdtr_install]
gdtr_install:
	push rbp
	mov rbp, rsp
	lgdt [rdi]
	mov ax, dx
	mov ss, ax
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov rax, qword .trampoline
	push rsi
	push rax
	o64 retf
.trampoline:
	pop rbp
	ret