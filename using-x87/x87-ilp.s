.data

.bss

.text
.globl _start

_start:
push %rbp
mov %rsp, %rbp
push %rbx
push %r12
push %r13
push %r14
push %r15

mov $12, %r12
mov $13, %r13
mov $14, %r14
mov $15, %r15

mov $0, %rax
add %r15, %rax
add %r14, %rbx
add %r13, %rcx
add %r14, %rdx

add %rax, %rcx
add %rbx, %rdx
add %r12, %r14
add %r13, %r15

mul %r12
add %rax, %r15
mul %r13
add %rax, %r14

pop %r15
pop %r14
pop %r13
pop %r12
pop %rbx



mov %rbp, %rsp
pop %rbp
ret	
