.data
	s0: .asciz "L%d:\n\tWays: %d,\n\tPartitions: %d,\n\tLine size: %d,\n\tSets: %d\n\n\tSize: %d kB\n\tType: %s\n\n"
	s1: .asciz "Data Cache"
	s2: .asciz "Instruction Cache"
	s3: .asciz "Unified Cache"

.text
.global main
.type main, @function

# rdi, rsi, rdx, rcx, r8, r9, stack...

main:
	push %rbp
	mov %rsp, %rbp
	
	mov $0, %r12

petla:
	# RAX = 0x4 -- Deterministic Cache Parameters Leaf
	mov $0x4, %rax
	mov %r12, %rcx

	cpuid
	
	inc %r12
	cmp $0, %rax
	je finish

# cache level -- RAX bits 07-05
	mov %rax, %r10
	mov $0x7, %r11
	shr $5, %r10
	and %r10, %r11
	mov %r11, %rsi
	
# cache type -- RAX bits 04-00
	mov %rax, %r10
	mov $0xF, %r11
	and %r10, %r11
	cmp $1, %r11
	je data_cache
	cmp $2, %r11
	je instr_cache
	cmp $3, %r11
	je unif_cache
	data_cache:
		push $s1
		jmp dalej
	instr_cache:
		push $s2
		jmp dalej
	unif_cache:
		push $s3
	dalej:
	
# $s0
	mov $s0, %rdi
	
# sets -- RCX, ** add one to the return value to get the result
	mov %rcx, %r9
	inc %r9

# line_size -- RBX bits 11-00, ** add one to the return value to get the result
	mov %rbx, %r10
	mov $0xfff, %r11
	and %r10, %r11
	mov %r11, %r8
	inc %r8
	
# partitions -- RBX bits 21-12, ** add one to the return value to get the result
	mov %rbx, %r10
	shr $12, %r10
	mov $0x3ff, %r11
	and %r10, %r11
	mov %r11, %rcx
	inc %rcx
	
# ways -- RBX bits 31-22, ** add one to the return value to get the result
	mov %rbx, %r10
	shr $22, %r10
	mov %r10, %rdx
	inc %rdx

# size = ways (+1) * partitions (+1) * line_size (+1) * sets (+1)
	push %rdx
	mov %rdx, %rax
	mul %rcx
	mul %r8
	mul %r9
	
	mov $1024, %r15
	div %r15
	pop %rdx
	push %rax
		
	xor %rax, %rax
	call printf
	
	pop %rax
	pop %r11
	
	jmp petla

finish:
	mov %rbp, %rsp
	pop %rbp
