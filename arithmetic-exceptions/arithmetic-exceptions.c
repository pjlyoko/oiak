#include <stdio.h>

extern long int asm_statusFPU();
extern long int asm_stanRejestruKontrolnego();
extern void asm_ustawKontrolny(long int maska);
extern void asm_zainicjujFPU();

void tlumaczenieFlagStanu(long int stan) {
	int wyjatek = 0;
	if((stan & 0x0001) == 1) {
		printf("\tOperacja niepoprawna.\n");
		wyjatek = 1;
	}
	if(((stan & 0x0002) >> 1) == 1) {
		printf("\tOperand zdenormalizowany.\n");
		wyjatek = 1;
	}
	if(((stan & 0x0004) >> 2) == 1) {
		printf("\tDzielenie przez zero.\n");
		wyjatek = 1;
	}
	if(((stan & 0x0008) >> 3) == 1) {
		printf("\tNadmiar.\n");
		wyjatek = 1;
	}
	if(((stan & 0x0010) >> 4) == 1) {
		printf("\tNiedomiar.\n");
		wyjatek = 1;
	}
	if(((stan & 0x0020) >> 5) == 1) {
		printf("\tPrecyzja.\n");
		wyjatek = 1;
	}
	if(((stan & 0x0040) >> 6) == 1) {
		printf("\tStos.\n");
		wyjatek = 1;
	}
	if(((stan & 0x8000) >> 15) == 1) {
		printf("\tFPU zajęte.\n");
		wyjatek = 1;
	}
}

void tlumaczenieFlagKontrolnych(long int stan) {
	if((stan & 0x0001) == 1)
		printf("\tBedzie sprawdzany wyjatek niepoprawnej operacji.\n");
	if(((stan & 0x0002) >> 1) == 1)
		printf("\tBedzie sprawdzany wyjatek zdenormalizowanego operandu.\n");
	if(((stan & 0x0004) >> 2) == 1)
		printf("\tBedzie sprawdzany wyjatek dzielenia przez zero.\n");
	if(((stan & 0x0008) >> 3) == 1)
		printf("\tBedzie sprawdzany wyjatek nadmiaru.\n");
	if(((stan & 0x0010) >> 4) == 1)
		printf("\tBedzie sprawdzany wyjatek niedomiaru.\n");
	if(((stan & 0x0020) >> 5) == 1)
		printf("\tBedzie sprawdzany wyjatek precyzji.\n");
	
	printf("\tPrecyzja obliczen: ");
	switch((stan & 0x0300) >> 8) {
		case 0:
			printf("pojedyncza (24-bit).\n");
			break;
		case 1:
			printf("(nieuzywana).\n");
			break;
		case 2:
			printf("podwojna (53-bit).\n");
			break;
		case 3:
			printf("podwojna, rozszerzona (64-bit).\n");
			break;
		default:
			printf("Say what?!?!?!\n");
			break;
	}

	printf("\tZaokraglanie: ");
	switch((stan & 0x0C00) >> 10) {
		case 0:
			printf(" do najblizszego (round to nearest).\n");
			break;
		case 1:
			printf(" w dol (-inf).\n");
			break;
		case 2:
			printf(" w gore (+inf).\n");
			break;
		case 3:
			printf(" do zera.\n");
			break;
		default:
			printf("Say what?!?!?!\n");
			break;
	}

	if(((stan & 0x1000) >> 12) == 1)
		printf("\tBedzie sprawdzany wyjatek nieskonczonosci.\n");
}

void sprawdzanie() {
	long int s = asm_statusFPU();

	printf("Aktualny stan rejestru: %ld.\n", s);
	printf("Wyjatki:\n");
	tlumaczenieFlagStanu(s);

	printf("\n\n");
}

void stanKontrolnego() {
	long int stanRejestru = asm_stanRejestruKontrolnego();
	printf("Stan rejestru: %ld.\n", stanRejestru);
	tlumaczenieFlagKontrolnych(stanRejestru);
}

void ustawRejestrKontrolny() {
	printf("Ustawianie rejestru kontrolnego\n");
	stanKontrolnego();

	int bit = -1;
	do {
		printf("Bit do zmiany: ");
		scanf("%d", &bit);
	} while(bit < 0 || bit > 15);
	long int maska = 1;
	maska = maska << bit;
	
	asm_ustawKontrolny(maska);
}

void wywolanieWyjatku() {
	printf("Próbuję wykonać dziwną operację... ");
	asm("fldz\n");
	asm("fldpi\n");
	asm("fdivp\n");
	printf("Gotowe.\n\n");
}

void testowanieWyjatkow() {
	sprawdzanie();

	wywolanieWyjatku();

	sprawdzanie();

	printf("Inicjuję ponownie FPU... ");
	asm_zainicjujFPU();
	printf("Gotowe.\n");
	sprawdzanie();
}

int main() {
	int wybor = -1;
	do {
		printf("Wybor opcji:\n");
		printf("[1] Testuj wystąpienia wyjątków\n");
		printf("[2] Ustawienia rejestru kontrolnego\n");
		printf("[3] Sprawdź rejestr kontrolny\n");
		printf("[0] Wyjdź\n");
		
		printf("\nWybór: ");
		scanf("%d", &wybor);
		
		switch(wybor) {
			case 0:
				break;
			case 1:
				testowanieWyjatkow();
				break;
			case 2:
				ustawRejestrKontrolny();
				break;
			case 3:
				stanKontrolnego();
				break;
			default:
				wybor = -1;
				break;
		}
	} while(wybor != 0);
	
	return 0;
}
