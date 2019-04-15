.data
SYSWRITE     = 1
STDOUT       = 1

buf_dane: .ascii "Przykladowy tekst."
buf_dane_len = .-buf_dane

.bss
.comm buffer, 8

.text

.globl asm_register_operation, asm_memory_operation, asm_write, asm_printf
.type asm_register_operation, @function
.type asm_memory_operation, @function
.type asm_write, @function
.type asm_printf, @function

asm_register_operation:
	push %rbp
	mov %rsp, %rbp
	
	mov $0xFFFF, %rax
	
	mov %rbp, %rsp
	pop %rbp
	ret

asm_memory_operation:
	push %rbp
	mov %rsp, %rbp
	
	xor %rax, %rax
	mov $0xFFFF, %rcx
	mov %rcx, buffer(, %rax, 1)
	
	mov %rbp, %rsp
	pop %rbp
	ret

asm_write:
	push %rbp
	mov %rsp, %rbp
	
	mov $SYSWRITE, %rax
	mov $STDOUT, %rdi
	mov $buf_dane, %rsi
	mov $buf_dane_len, %rdx
	syscall
	
	mov %rbp, %rsp
	pop %rbp
	ret

asm_printf:
	push %rbp
	mov %rsp, %rbp
	push %rbx
	
	mov $buf_dane, %rdi
	xor %rax, %rax
	call printf

	pop %rbx
	mov %rbp, %rsp
	pop %rbp
	ret

