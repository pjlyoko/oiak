.data

.text

.globl asm_rdtsc
.type asm_rdtsc, @function

asm_rdtsc:
	push %rbp
	mov %rsp, %rbp
	push %rbx
	
	mov $0, %rax
	cpuid
	rdtsc

	shl $32, %rdx
	or %rdx, %rax
	
	pop %rbx
	mov %rbp, %rsp
	pop %rbp
	ret
