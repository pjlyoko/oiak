# Laboratorium 6

## Zadanie 1 (5 p.)
Korzystając z [dostarczonego kodu programu](http://zak.iiar.pwr.edu.pl/materials/architektura/laboratorium%20AK2/MMX/emboss.tar.bz2), uzupełnić funkcję, która będzie nakładać na rysunek efekt płaskorzeźby. W tym celu należy każdy piksel obrazu (**z wyjątkiem pikseli w „ramce”** (pierwszy/ostatni wiersz/kolumna) — nie dotyczy to tego laboratorium) przetworzyć, wykonując następującą operację:

Niech sytuacja wyjściowa wygląda tak:
```
a b c
d e f
g h i
```
gdzie `e` jest przetwarzanym pikselem, a pozostałe znaki - pikselami dookoła niego. Traktując ten zestaw pikseli jak macierz 3&times;3, należy ją **pomnożyć skalarnie** (policzyć iloczyn skalarny) przez macierz:
```
-1  1  0
-1  0  1
 0  1  1
```

Otrzymany wynik jest nową wartością piksela.

Do obliczeń należy użyć rozszerzenia `SSE`.