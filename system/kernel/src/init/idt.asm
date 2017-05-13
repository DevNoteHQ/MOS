

[global idtr_install]
idtr_install:
	push rbp
	mov rbp, rsp
	lidt [rdi]
	pop rbp
	ret