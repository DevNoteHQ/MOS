.code64
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	.code64
	
	mov $stack_top, %esp
	.extern init
	call init

	cli
1:	hlt
	jmp 1b

.size _start, . - _start