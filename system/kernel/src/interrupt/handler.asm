
[extern exception]
[extern hwinterrupt]
[extern swinterrupt]
[extern swinterrupt]

; fault without error entry code
%macro fault
[global fault%1]
fault%1:
	push 0
	jmp _exception
%endmacro

; fault with error entry code
%macro fault_err 1
[global fault%1]
fault%1:
	jmp _exception
%endmacro

; irq entry code
%macro irq 1
[global irq%1]
irq%1:
	push 0
	jmp _hwinterrupt
%endmacro

; syscall entry code
%macro swintr 1
[global swinterrupt%1]
swinterrupt%1:
	push 0
	jmp _swinterrupt
%endmacro

; special entry code
%macro special 1
[global special%1]
special%1:
	push 0
	jmp _special
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

_swinterrupt:
	save
	call swinterrupt
	restore
	iretq

_special:
	save
	call spechandler
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

irq 32
irq 33
irq 34
irq 35
irq 36
irq 37
irq 38
irq 39
irq 40
irq 41
irq 42
irq 43
irq 44
irq 45
irq 46
irq 47
irq 48
irq 49
irq 50
irq 51
irq 52
irq 53
irq 54
irq 55

swintr 56
swintr 57
swintr 58
swintr 59
swintr 60
swintr 61
swintr 62
swintr 63
swintr 64
swintr 65
swintr 66
swintr 67
swintr 68
swintr 69
swintr 70
swintr 71
swintr 72
swintr 73
swintr 74
swintr 75
swintr 76
swintr 77
swintr 78
swintr 79


special 250
special 251
special 252
special 253
special 254
special 255