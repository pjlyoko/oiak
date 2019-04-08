# WARNING!
# The code **is not completed**!

.data
SYSEXIT      = 60
SYSREAD      = 0
SYSWRITE     = 1
STDIN        = 0
STDOUT       = 1
EXIT_SUCCESS = 0

BUFLEN       = 1024
BUFLEN_RES   = 256

.bss
.comm buf_in, 1
.comm buffer, BUFLEN
.comm buf_out, BUFLEN_RES

.text

.global _start

_start:
# Wczytywanie pojedynczych znaków, aż trafimy na '\n'
# Wczytane znaki dopisujemy do buffer

mov $0, %r15 # Licznik wczytywanych znaków
#TODO: Czyszczenie bufora liczb

_wczytanie:
mov $SYSREAD, %rax
mov $STDIN, %rdi
mov $buf_in, %rsi
mov $1, %rdx
syscall

# Jeśli nie udało się wczytać znaku, zakończyliśmy wczytywanie.
# Powinien nastąpić koniec programu.
# TODO: Na pewno?
cmp $0, %rax
je koniec

# buf_in -> %r14b
mov $0, %rsi
movb buf_in, %r14b

# %r14b == '\n' ? goto przetwarzanie_liczby : continue;
cmp $'\n', %r14b
je przetwarzanie_liczby

# $r14b -> buffer[%r15]
movb %r14b, buffer(, %r15, 1)
inc %r15

jmp _wczytanie

# W %r15 zapisano liczbę wczytanych znaków ASCII.
przetwarzanie_liczby:
# Do tego, co masz, dodaj cyfrę, a całość pomnóż przez 10.
mov $254, %r8 # wskazywanie, gdzie pisać w buforze wyjściowym
mov $10, %r10  # Baza dziesiętna tylko w %r10 :-)
mov $0, %r13   # Licznik **UPTO**
mov $0, %r14   # Cyfra
mov $0, %rax   # Początkowa suma częściowa
mov $0, %r12   # Przechowywanie sumy

# Przetwórz pierwszy znak. Później mnóż i dodawaj.
movb buffer(, %r13, 1), %r14b
sub $'0', %r14b
mov %r14, %r12

inc %r13
cmp %r15, %r13
je koniec_przetwarzania

petla_przetwarzania:
	mov %r12, %rax
	mul %r10
	
	# TODO: Jeśli nastąpiło przepełnienie, trzeba to obsłużyć.
	jnc dalej
	nop
	# Obsługa przepełnienia
	# Rejestr %rax jest pełny i należy go zapisać do wyjścia.
	
	dalej:
	movb buffer(, %r13, 1), %r14b
	sub $'0', %r14b
	add %r14, %rax
	
	mov %rax, %r12

	inc %r13
	cmp %r15, %r13
	jne petla_przetwarzania

koniec_przetwarzania:
movq %r12, buf_out(, %r8, 1)

wypisywanie:
mov $SYSWRITE, %rax
mov $STDOUT, %rdi
mov $buf_out, %rsi
mov $BUFLEN_RES, %rdx
syscall


jmp _start

# Zakończenie programu
koniec:
mov $SYSEXIT, %rax
mov $EXIT_SUCCESS, %rdi
syscall
