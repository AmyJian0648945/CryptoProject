/*
 * montgomery.c
 *
 */

#include "montgomery.h"

void ADD(uint32_t *t, int i, uint32_t C){
	uint64_t sum;
	uint32_t S;

	while(C != 0x00000000){
		sum = (uint64_t)t[i] + (uint64_t)C;
		S = (uint32_t) sum;
		C = sum >> 32;

		t[i] = S;
		i++;
	}
}


void SUB_COND(uint32_t *res, uint32_t *n, uint32_t SIZE){
	uint32_t B = 0x00000000;
	uint32_t sub = 0;
	uint32_t t[32] = {0};
	int i = 0;


	for(i = 0; i < SIZE; i++){
		sub = res[i] - n[i] - B;

		if(res[i] >= (n[i] + B)) {
			B = 0;
			t[i] = sub;
		}
		else {
			B = 1;
			t[i] = sub;
		}
	}

	if(B == 0){
		for(i = 0; i < SIZE; i++){
			res[i] = t[i];
		}
	}
}

void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE)
{
	int i , j;
	uint32_t t[65] = { 0 };
	uint32_t C = 0, S = 0;
	uint32_t m;
	uint64_t mul;
	uint64_t sum = 0;



	// t = a * b
	for(i = 0; i < SIZE; i++){
		C = 0;
		for(j = 0; j < SIZE; j++){
			sum = (uint64_t) t[i+j] + (uint64_t)a[j]*(uint64_t)b[i] + (uint64_t)C;

			S = (uint32_t) sum;
			C = sum >> 32;
			t[i+j] = S;
		}
		t[i + SIZE] = C;
	}

	// mod
	for(i = 0; i < SIZE; i++){
		C = 0;
		mul =  ((uint64_t)t[i] *  (uint64_t)n0[0]) ;
		m = (uint32_t) mul;

		for(j = 0; j < SIZE; j++){
			sum = (uint64_t) t[i+j] + (uint64_t)m * (uint64_t)n[j] +(uint64_t)C;
			S = (uint32_t) sum;
			C = sum >> 32;
			t[i+j] = S;
		}
		//xil_printf("  SUM IS S = %x  C = %x",S,C );
		ADD(t, i+SIZE, C);
	}

	// output
	for(j = 0; j <= SIZE; j++){
		res[j] = t[j+SIZE];
	}
	SUB_COND(res, n, SIZE);


}


















