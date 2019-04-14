#include <stdio.h>

extern long int asm_rdtsc();
extern void asm_obliczenie(int *wartosci1, int *wartosci2, int *wynik2, int *stale);

int wartosci1[4000], wartosci2[4000], wynik1[4000], wynik2[4000], stala, stale[4];

void obliczenie() {
	int i = 0;
	for(; i < 4000; ++i) {
		wynik1[i] = (wartosci1[i] + wartosci2[i]) * stala;
	}
}

int main() {
	int i = 0;
	long int czas1, czas2, czas_gen, czas_rez1, czas_rez2;
	stala = 2;
	stale[0] = stale[1] = stale[2] = stale[3] = stala;
	
	czas1 = asm_rdtsc();
	for(; i < 4000; ++i) {
		wartosci1[i] = rand() % 50000;
		wartosci2[i] = rand() % 50000;
	}
	czas2 = asm_rdtsc();
	czas_gen = czas2 - czas1;
	printf("Czas generowania danych: %ld cykli.\n\n", czas_gen);
	
	czas1 = asm_rdtsc();
	obliczenie();
	czas2 = asm_rdtsc();
	czas_rez1 = czas2 - czas1;
	printf("Czas wykonywania obliczeń w C: %ld cykli.\n", czas_rez1);

	czas1 = asm_rdtsc();
	asm_obliczenie(wartosci1, wartosci2, wynik2, stale);
	czas2 = asm_rdtsc();
	czas_rez2 = czas2 - czas1;
	printf("Czas wykonywania obliczeń w asm: %ld cykli.\n", czas_rez2);
	
	printf("\nPorównuję... ");
	int flaga = 0;
	for(i = 0; i < 4000; ++i) {
		if(wynik1[i] != wynik2[i]) {
			flaga = 1;
			printf("Niezgodność na pozycji %d.\n", i);
		}
	}
	if(flaga == 0)
		printf("Gotowe. Brak niezgodności.");
	
	printf("\n\n\n");
//	printf("%ld;%ld;%ld\n\n", czas_gen, czas_rez1, czas_rez2);




	return 0;
}
