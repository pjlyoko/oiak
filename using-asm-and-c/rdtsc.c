#include <stdio.h>

extern unsigned long long int asm_rdtsc();

int main() {
	int a = 1;
	unsigned int counter = 0;
	for(; a < 10; ++a) {
		counter += a;
		counter /= a;
		printf("%u %llu\n", counter, asm_rdtsc());
	}
	fprintf(stderr, "%llu\n", asm_rdtsc());
	return 0;
}
