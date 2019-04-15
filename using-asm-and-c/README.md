# Laboratorium 4

## Zadanie 1 (1 p.)
Napisz kod w asm wywołujący funkcje `scanf` i `printf` dla argumentów (int, char *). Funkcja `main`.
Przy użycia `scanf` odczytać zmienne typu `int` i `char *`, odczytany tekst wypisać przy użyciu `printf`.
Podczas linkowania należy dołączyć bibliotekę języka C. Używając gcc, biblioteka jest dołączana automagicznie.

## Zadanie 2 (1 p.)
Funkcja w asm zgodnia z ABI — `rdtsc`.
Jest w procesorze rejestr `tsc` (64b.). Rozkaz `rdtsc` odczytuje stan tego licznika i umieszcza wynik w parze rejestrów `edx`:`eax`.
Na etapie sprawdzania funkcji kompilować z parametrem `-O3` (wysoki poziom optymalizacji, co może sprawić, że błędnie napisana funkcja będzie zachowywać się „dziwnie”).

```
gcc -O3 -c 

gcc 
	-c — only compile
	-O3 — "Optimize yet more"
```

**Ważne**. `rdtsc` jest funkcją _nieserializującą_ i może się zakończyć przed wcześniejszymi instrukcjami. Dlatego przed użyciem tego rozkazu należy wykonać jakąś instrukcję _serializującą_, np. `cpuid`.

## Zadanie 3 (1 p.)
Zmienna C używana z poziomu asm (short, char []) i odwrotnie (int, char *).
Może się przydać `gcc -S`, który pokaże kod C przetłumaczony na asm. Zmienne **muszą** być globalne — inaczej nie będą dostępne.
2 pliki źródłowe.

## Zadanie 4 (2 p.)
Pomiar czasu trwania:
- operacji na rejestrze,
- operacji na pamięci,
- funkcji `write`,
- funkcji `printf`.
Wykonać serię pomiarów („tyle pomiarów, ile można zobaczyć jednym rzutem oka”), sprawdzić, jak te wyniki się układają.
