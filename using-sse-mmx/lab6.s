.data

.bss
	.comm war1, 16
	.comm war2, 16
	.comm czteryrazydwa, 16
.text

.globl asm_rdtsc, asm_obliczenie
.type asm_rdtsc, @function
.type asm_obliczenie, @function

asm_rdtsc:
	push %rbp
	mov %rsp, %rbp
	
	rdtsc
	shl $32, %rdx
	or %rdx, %rax
	
	mov %rbp, %rsp
	pop %rbp
	ret

asm_obliczenie:
	push %rbp
	mov %rsp, %rbp
	
	mov %rdi, %r11	# Adres wartosci1
	mov %rsi, %r12	# Adres wartosci2
	mov %rdx, %r13	# Adres wyniku
	mov %rcx, %r14	# Adres stałych
	
	mov $0, %rdi
	mov $0, %rsi
	mov $0, %rax
	
	movaps (%r14), %xmm2
	
	przyg_wyniku:
	movaps (%r11), %xmm0
	movaps (%r12), %xmm1
	paddd %xmm1, %xmm0
	le_test:
	pmulld %xmm2, %xmm0
	mam_wynik:
	
	movaps %xmm0, (%r13)
	
	add $16, %r11
	add $16, %r12
	add $16, %r13
	add $4, %rdi

	cmp $4000, %rdi
	jl przyg_wyniku
	
	mov %rbp, %rsp
	pop %rbp
	ret

