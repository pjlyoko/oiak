.data
	rejestr_kontrolny: .short 0
.bss

.text

.globl asm_statusFPU, asm_stanRejestruKontrolnego, asm_ustawKontrolny, asm_zainicjujFPU
.type asm_statusFPU, @function
.type asm_stanRejestruKontrolnego, @function
.type asm_ustawKontrolny, @function
.type asm_zainicjujFPU, @function

asm_statusFPU:
	push %rbp
	mov %rsp, %rbp
	
	mov $0, %rax
	fstsw %ax
	
	mov %rbp, %rsp
	pop %rbp
	ret	

asm_stanRejestruKontrolnego:
	push %rbp
	mov %rsp, %rbp

	mov $0, %rax
	fstcw rejestr_kontrolny
	mov rejestr_kontrolny, %ax
	
	mov %rbp, %rsp
	pop %rbp
	ret

asm_ustawKontrolny:
	push %rbp
	mov %rsp, %rbp
	
	mov $0, %rax
	fstcw rejestr_kontrolny
	mov rejestr_kontrolny, %ax
	
	xor %rdi, %rax
	
	mov %ax, rejestr_kontrolny
	fldcw rejestr_kontrolny
	
	mov %rbp, %rsp
	pop %rbp
	ret	

asm_zainicjujFPU:
	push %rbp
	mov %rsp, %rbp
	
	fninit
	
	mov %rbp, %rsp
	pop %rbp
	ret
