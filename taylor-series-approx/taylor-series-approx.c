#include <stdio.h>

extern double asm_TaylorIt(double x);

int main() {
	float x = 0.0f;
	printf("Podaj x: ");
	scanf("%f", &x);

	printf("Wartość ln(1+%f) to %f.\n\n", x, asm_TaylorIt(x));

	return 0;
}