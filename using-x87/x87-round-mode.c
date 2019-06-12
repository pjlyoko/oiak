#include <stdio.h>

short asm_stanRejestruKontrolnego(), asm_stanFPU();
void asm_zainicjujFPU(), asm_ustawKontrolny_zaokr();
double asm_dodajPi();

void tlumaczenieFlagKontrolnych(short stan) {
	if((stan & 0x01) == 1)
		printf("\t[0] Bedzie sprawdzany wyjatek niepoprawnej operacji.\n");
	if(((stan & 0x02) >> 1) == 1)
		printf("\t[1] Bedzie sprawdzany wyjatek zdenormalizowanego operandu.\n");
	if(((stan & 0x04) >> 2) == 1)
		printf("\t[2] Bedzie sprawdzany wyjatek dzielenia przez zero.\n");
	if(((stan & 0x08) >> 3) == 1)
		printf("\t[3] Bedzie sprawdzany wyjatek nadmiaru.\n");
	if(((stan & 0x10) >> 4) == 1)
		printf("\t[4] Bedzie sprawdzany wyjatek niedomiaru.\n");
	if(((stan & 0x20) >> 5) == 1)
		printf("\t[5] Bedzie sprawdzany wyjatek precyzji.\n");
	
	printf("\t[9-8] Precyzja obliczen: ");
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

	printf("\t[11-10] Zaokraglanie: ");
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
		printf("\t[12] Bedzie sprawdzany wyjatek nieskonczonosci.\n");
}

void tlumaczenieFlagStanu(short stan) {
	if((stan & 0x0001) == 1) {
		printf("\t[0] Operacja niepoprawna.\n");
	}
	if(((stan & 0x0002) >> 1) == 1) {
		printf("\t[1] Operand zdenormalizowany.\n");
	}
	if(((stan & 0x0004) >> 2) == 1) {
		printf("\t[2] Dzielenie przez zero.\n");
	}
	if(((stan & 0x0008) >> 3) == 1) {
		printf("\t[3] Nadmiar.\n");
	}
	if(((stan & 0x0010) >> 4) == 1) {
		printf("\t[4] Niedomiar.\n");
	}
	if(((stan & 0x0020) >> 5) == 1) {
		printf("\t[5] Precyzja.\n");
	}
	if(((stan & 0x0040) >> 6) == 1) {
		printf("\t[6] Stos.\n");
	}
	if(((stan & 0x8000) >> 15) == 1) {
		printf("\t[15] FPU zajęte.\n");
	}
}


int main() {
	asm_zainicjujFPU();

	short stan = asm_stanRejestruKontrolnego();
	printf("Stan: %#04x.\n", stan);
	tlumaczenieFlagKontrolnych(stan);
	
	printf("%21.19e\n", asm_dodajPi());
	asm_ustawKontrolny_zaokr();
	
	stan = asm_stanRejestruKontrolnego();
	printf("Stan: %#04x.\n", stan);
	tlumaczenieFlagKontrolnych(stan);

	printf("%21.19e\n", asm_dodajPi());

	return 0;
}
