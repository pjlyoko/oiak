.data
SYSEXIT      = 60
SYSREAD      = 0
SYSWRITE     = 1
STDIN        = 0
STDOUT       = 1
EXIT_SUCCESS = 0

.bss
.comm znak, 1

.text

.global _start

_start:
# Wczytywanie pojedynczego znaku
mov $SYSREAD, %rax
mov $STDIN, %rdi
mov $znak, %rsi
mov $1, %rdx
syscall

# Uzyskanie informacji o ilości wczytanych znaków
mov %rax, %r9 # Ilość wczytanych znaków do %r9

# Jeśli nie wczytano znaku, koniec
cmp $0, %r9
je koniec

# Przeniesienie znaku do manipulacji do %r10
mov $0, %rsi
movb znak, %r10b # Wczytany znak do %r10

# Odwrócenie bitów
mov $0, %r11
rolb $1, %r10b
rcrb $1, %r11b
rolb $1, %r10b
rcrb $1, %r11b
rolb $1, %r10b
rcrb $1, %r11b
rolb $1, %r10b
rcrb $1, %r11b
rolb $1, %r10b
rcrb $1, %r11b
rolb $1, %r10b
rcrb $1, %r11b
rolb $1, %r10b
rcrb $1, %r11b
rolb $1, %r10b
rcrb $1, %r11b


# Zmieniony znak wraca do bufora
mov %r11, znak(, %rsi, 1)

# Wypisanie znaku
mov $SYSWRITE, %rax
mov $STDOUT, %rdi
mov $znak, %rsi
mov $1, %rdx
syscall

# I powrót
jmp _start

# Zakończenie programu
koniec:
mov $SYSEXIT, %rax
mov $EXIT_SUCCESS, %rdi
syscall
