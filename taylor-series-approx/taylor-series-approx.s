.data
	max_iter: .int 100
.bss
	.comm counter, 4
	.comm result, 10
.text

.globl asm_TaylorIt
.type asm_TaylorIt, @function

asm_TaylorIt:
	push %rbp
	mov %rsp, %rbp

	push %rdi
	push %rsi
	mov $1, %rdi
	mov $1, %rsi
	
	test:
	sub $8, %rsp
	movsd %xmm0, (%rsp)
	fldz						# ST(0) = zero - suma całkowita

	ladowanie:
	fldl (%rsp)					# ST(0) = argument
								# ST(1) = suma całkowita

	poczatek_petli:
	fld1	 					# ST(0) = suma częściowa
								# ST(1) = argument
								# ST(2) = suma całkowita
	
	mov $1, %rsi
	mnozenie:
	fmul %ST(1), %ST(0)			# ST(0) = x*x*...
	inc %rsi
	cmp %rdi, %rsi
	jle mnozenie

	mov %rdi, counter
	fild counter				# ST(0) = n
								# ST(1) = suma częściowa
								# ST(2) = argument
								# ST(3) = suma całkowita

	test2:
	fxch
	fdivp						# ST(0) = ST(1) / ST(0) + pop

								# zatem:
								# ST(0) = suma częściowa
								# ST(1) = argument
								# ST(2) = suma całkowita

	mov %rdi, %rax
	mov $0, %rdx
	mov $2, %rbx
	div %rbx
	cmp $0, %rdx
	jne dalej
		fchs					# wyraz parzysty - zmiana znaku, ST(0) = -ST(0)
	
	dalej:
	fadd %ST(0), %ST(2)	
	fstp %ST(0)					# ST(0) = argument
								# ST(1) = suma całkowita

	po_dodaniu:
	inc %rdi
	mov max_iter, %r9
	cmp %rdi, %r9
	jge poczatek_petli

	koniec:
	fstp %ST(0)
	fstp result
	cvtss2sd result, %xmm0

	pop %rsi
	pop %rdi

	mov %rbp, %rsp
	pop %rbp
	ret	
