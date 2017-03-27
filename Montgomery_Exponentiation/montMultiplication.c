/*
 * montgomery.c
 *
 */

void ADD(uint16_t *t, int i, uint16_t C){
	uint32_t sum;
	uint16_t S;

	while(C != 0x00000000){
		sum = (uint32_t)t[i] + (uint32_t)C;
		S = (uint16_t) sum;
		C = sum >> 32;

		t[i] = S;
		i++;
	}
}


void SUB_COND(uint16_t *res, uint16_t *n, uint16_t SIZE){
	uint16_t B = 0x00000000;
	uint16_t sub = 0;
	uint16_t t[32] = {0};
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

void mont(uint16_t *a, uint16_t *b, uint16_t *n, uint16_t *n0, uint16_t *res, uint16_t SIZE)
{
	int i , j;
	uint16_t t[65] = { 0 };
	uint16_t C = 0, S = 0;
	uint16_t m;
	uint32_t mul;
	uint32_t sum = 0;



	// t = a * b
	for(i = 0; i < SIZE; i++){
		C = 0;
		for(j = 0; j < SIZE; j++){
			sum = (uint32_t) t[i+j] + (uint32_t)a[j]*(uint32_t)b[i] + (uint32_t)C;

			S = (uint16_t) sum;
			C = sum >> 32;
			t[i+j] = S;
		}
		t[i + SIZE] = C;
	}

	// mod
	for(i = 0; i < SIZE; i++){
		C = 0;
		mul =  ((uint32_t)t[i] *  (uint32_t)n0[0]) ;
		m = (uint16_t) mul;

		for(j = 0; j < SIZE; j++){
			sum = (uint32_t) t[i+j] + (uint32_t)m * (uint32_t)n[j] +(uint32_t)C;
			S = (uint16_t) sum;
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


















