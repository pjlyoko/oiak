# Laboratorium 5

**Koniecznie sprawdzać kod asemblerowy generowany przez kompilator C.**

## Zadanie 1 (1 p.)
Spowodować 2 wyjątki, jeden inny niż /0, INV.
Pokazać różnicę rejestru flag.

## Zadanie 2 (1 p.)
Zmienić prezycję obliczeń i pokazać na przykładzie działania (przedstawić bity w reprezentacji).
W rejestrze kontrolnym ustawić odpowiednie bity odpowiedzialne za precyzję oraz wykonać działania tak, aby widoczna była różnica.

## Zadanie 3 (1 p.)
Zmienić tryb zaokrąglania i pokazać na przykładzie działania (przedstawić bity w reprezentacji).
Tak dobrać działanie, aby móc powiedzieć, jakie bity zostały użyte do zaokrąglania.

## Zadanie 4 (2 p.)
Równoległość na poziomie instrukcji (ang. Instruction Level Parallelism, ILP).
Napisać dwie sekwencje takich instrukcji, aby w jednej było dużo zależności jak w pierwszym przykładzie, a w drugiej — aby było ich mało, jak w drugim przykładzie.
Ciągi powinny być dość długie (najlepiej dodawanie i mnożenie), argumenty powinny znajdować się w rejestrach — w obu sekwencjach powinno być tyle samo takich samych instrukcji.
```
Przykład 1.
| a = b + c
| d = a * e
równol. a, d niemożliwa, d zależne od a

Przykład 2.
| a = b + c
| d = e * f
równol. a, d możliwa, niezależne od siebie
```
