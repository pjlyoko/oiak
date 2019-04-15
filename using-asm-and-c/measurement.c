#include <stdio.h>

extern unsigned long long int asm_rdtsc();
extern unsigned int asm_register_operation(), asm_write(), asm_printf();

int main() {
	unsigned long long int t1_start, t1, t2_start, t2, t3_start, t3, t4_start, t4;
	int test, a = 0;
	
//	for(; a < 10; ++a) {
		t1_start = asm_rdtsc();
		test = asm_register_operation();
		t1 = asm_rdtsc() - t1_start;
		
		t2_start = asm_rdtsc();
		test = asm_memory_operation();
		t2 = asm_rdtsc() - t2_start;
		
		t3_start = asm_rdtsc();
		test = asm_write();
		t3 = asm_rdtsc() - t3_start;
	
		t4_start = asm_rdtsc();
		test = asm_printf();
		t4 = asm_rdtsc() - t4_start;
		
		fprintf(stderr, "%llu;%llu;%llu;%llu\n", t1, t2, t3, t4);
//	}
	return 0;
}
