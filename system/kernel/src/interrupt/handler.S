
[extern exception]
[extern hwinterrupt]
[extern swinterrupt]

; fault without error entry code
%macro fault 1
[global fault%1]
fault%1:
	push 0
	push %1
	jmp _exception
%endmacro

; fault with error entry code
%macro fault_err 1
[global fault%1]
fault%1:
	push %1
	jmp _exception
%endmacro

; irq entry code
%macro irq 2
[global irq%1]
irq%1:
	push 0
	push %2
	jmp _hwinterrupt
%endmacro

; irq entry code
%macro swintr 2
[global swinterrupt%1]
swinterrupt%1:
	push 0
	push %2
	jmp _swinterrupt
%endmacro

%macro save 0
	; save the register file
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rbp
	push rdi
	push rsi
	push rdx
	push rcx
	push rbx
	push rax

	; check if we are switching from user mode to supervisor mode
	mov rax, [rsp + 152]
	and rax, 0x3000
	jz .supervisor_enter

	; restore the kernel's GS base if we are going from user to supervisor mode
	swapgs

.supervisor_enter:
	; increment mask count as we configure all interrupts to mask IF
	; automatically in the IDT
	inc qword [gs:8]

	; call the C routine for dispatching an interrupt
	cld          ; amd64 SysV ABI states the DF must be cleared by the caller
	mov rdi, rsp ; first argument points to the processor state
	mov rbp, 0   ; terminate stack traces here

%endmacro

%macro restore 0
	; decrement mask count
	dec qword [gs:8]

	; check if we are switching from supervisor to user mode
	mov rax, [rsp + 152]
	and rax, 0x3000
	jz .supervisor_exit

	; switch back to the user's GS base if we are going from supervisor to user mode
	swapgs

.supervisor_exit:
  ; restore the register file
	pop rax
	pop rbx
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	pop rbp
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15

	; pop the error code and interrupt id
	add rsp, 16

%endmacro
	
_exception:
	save
	call exception
	restore
	iretq

_hwinterrupt:
	save
	call hwinterrupt
	restore
	iretq

swinterrupt:
	save
	call swinterrupt
	restore
	iretq



fault     0
fault     1
fault     2
fault     3
fault     4
fault     5
fault     6
fault     7
fault_err 8
fault     9
fault_err 10
fault_err 11
fault_err 12
fault_err 13
fault_err 14
fault     15
fault     16
fault_err 17
fault     18
fault     19
fault     20
fault     21
fault     22
fault     23
fault     24
fault     25
fault     26
fault     27
fault     28
fault     29
fault     30
fault     31

irq 0,  32
irq 1,  33
irq 2,  34
irq 3,  35
irq 4,  36
irq 5,  37
irq 6,  38
irq 7,  39
irq 8,  40
irq 9,  41
irq 10, 42
irq 11, 43
irq 12, 44
irq 13, 45
irq 14, 46
irq 15, 47
irq 16, 48
irq 17, 49
irq 18, 50
irq 19, 51
irq 20, 52
irq 21, 53
irq 22, 54
irq 23, 55

swintr 0,  56
swintr 1,  57
swintr 2,  58
swintr 3,  59
swintr 4,  60
swintr 5,  61
swintr 6,  62
swintr 7,  63
swintr 8,  64
swintr 9,  65
swintr 10, 66
swintr 11, 67
swintr 12, 68
swintr 13, 69
swintr 14, 70
swintr 15, 71
swintr 16, 72
swintr 17, 73
swintr 18, 74
swintr 19, 75
swintr 20, 76
swintr 21, 77
swintr 22, 78
swintr 23, 79