# Laboratorium 2

## Zadanie 0
Sklonować repozytorium SVN lokalnie. Utwórz plik, dodaj go do centralnego repozytorium, wykonaj commit, sprawdź, czy jest na serwerze.

## Zadanie 1
- Ze standardowego strumienia wejściowego odczytaj dowolnie długi ciąg bajtów. 
- W każdym bajcie odwróć kolejność bitów.
- Zmienione bajty (wszystkie!) wypisać na standardowy strumień wyjściowy.

Użyć [danych na stronie ZAK](zak.iiar.pwr.edu.pl/materials/architektura/laboratorium AK2/Dane/revBits.tar.gz) dla uzyskania danych wejściowych i oczekiwanych wyjść.

```bash
as program.s -g -o program.o
ld program.o -o program
```
-- lub --
```bash
as reverse-bits.s -g -o reverse-bits.o && ld reverse-bits.o -o reverse-bits
./reverse-bits < rand1M.in > result; diff result rand1M_revBits.out
```
