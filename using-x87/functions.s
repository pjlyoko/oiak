.data
	rejestr_kontrolny: .short 0
	wynik: .float 0.0
.bss

.text
.globl asm_stanRejestruKontrolnego, asm_stanFPU, asm_zainicjujFPU, asm_dodajPi, asm_ustawKontrolny_precyzja, asm_ustawKontrolny_zaokr
.type asm_stanRejestruKontrolnego, @function
.type asm_stanFPU, @function
.type asm_zainicjujFPU, @function
.type asm_dodajPi, @function
.type asm_ustawKontrolny_precyzja, @function
.type asm_ustawKontrolny_zaokr, @function

asm_stanRejestruKontrolnego:
	push %rbp
	mov %rsp, %rbp

	mov $0, %rax
	fstcw rejestr_kontrolny
	mov rejestr_kontrolny, %ax
	
	mov %rbp, %rsp
	pop %rbp
	ret

asm_stanFPU:
	push %rbp
	mov %rsp, %rbp
	
	mov $0, %rax
	fstsw %ax
	
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

asm_dodajPi:
	push %rbp
	mov %rsp, %rbp
	
	fldpi
	fldpi
	fadd %ST(1), %ST(0)
	
	fstp wynik
	cvtss2sd wynik, %xmm0
	
	mov %rbp, %rsp
	pop %rbp
	ret

asm_ustawKontrolny_precyzja: # TODO: zwracanie właściwej wartości
	push %rbp
	mov %rsp, %rbp
	
	mov $0, %rax
	fstcw rejestr_kontrolny
	mov rejestr_kontrolny, %ax
	
	xor $0x0300, %rax
	
	mov %ax, rejestr_kontrolny
	fldcw rejestr_kontrolny
	
	mov %rbp, %rsp
	pop %rbp
	ret

asm_ustawKontrolny_zaokr:
	push %rbp
	mov %rsp, %rbp
	
	mov $0, %rax
	fstcw rejestr_kontrolny
	mov rejestr_kontrolny, %ax
	
	xor $0x0C00, %rax
	
	mov %ax, rejestr_kontrolny
	fldcw rejestr_kontrolny
	
	mov %rbp, %rsp
	pop %rbp
	ret	
