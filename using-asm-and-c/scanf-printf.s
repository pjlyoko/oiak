.data
SYSEXIT = 60
EXIT_SUCCESS = 0
buf_format_wejscia: .asciz "%d %s"

.bss
.comm liczba, 4
.comm tekst, 50

.text
.global main

main:
push %rbp
mov %rsp, %rbp
push %rbx

#movq $0, %rax	# 0 arg. zmiennoprzecinkowych
xor %rax, %rax
movq $buf_format_wejscia, %rdi	# arg. 1 - format wczytywania
movq $liczba, %rsi	# arg. 2 - wsk. na miejsce do zapisania
movq $tekst, %rdx	# arg. 3 - wsk. na miejsce do zapisania
call scanf

mov $buf_format_wejscia, %rdi
mov liczba, %rsi
mov $tekst, %rdx
xor %rax, %rax
call printf

pop %rbx
mov %rbp, %rsp
pop %rbp
xor %rax, %rax
ret
