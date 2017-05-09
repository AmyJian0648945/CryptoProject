


// void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint16_t SIZE)
// {
	// uint64_t t[3];
	// int index;
	// for(index=0; index<3; index++){
		// t[index] = 0;
	// }
	// uint32_t m[SIZE+1];
	// for(index=0; index<SIZE+1; index++){
		// m[index] = 0;
	// }
	// int i,j;
	// uint64_t sum;
	// uint32_t S;
	// uint32_t C;
	// uint64_t resultSIZE[SIZE];
	// for(index=0; index<SIZE; index++){
		// resultSIZE[index] = 0;
	// }

	// for(i=0; i<SIZE; i++){
		// for(j=0; j<i; j++){
			// sum = t[0] + (uint64_t)a[j] * (uint64_t)b[i-j];
			// S = (uint32_t)sum;
			// C = (uint32_t)(sum>>32);
			// add(t,1,C);

			// sum = (uint64_t)S + (uint64_t)m[j] * (uint64_t)n[i-j];
			// S = (uint32_t)sum;
			// C = (uint32_t)(sum>>32);
			// t[0] = (uint64_t)S;
			// add(t,1,C);
		// }

		// sum = t[0] + (uint64_t)a[i] * (uint64_t)b[0];
		// S = (uint32_t)sum;
		// C = (uint32_t)(sum>>32);
		// add(t,1,C);

		// m[i] = (uint32_t)((uint64_t)S * (uint64_t)n0[0]);
		// sum = (uint64_t)S + (uint64_t)m[i] * (uint64_t)n[0];
		// S = (uint32_t)sum;
		// C = (uint32_t)(sum>>32);
		// add(t,1,C);

		// t[0] = t[1];
		// t[1] = t[2];
		// t[2] = 0;
	// }

	// for(i=SIZE; i<2*SIZE; i++){
		// for(j=i-SIZE+1; j<SIZE; j++){
			// sum = t[0] + (uint64_t)a[j] * (uint64_t)b[i-j];
				// S = (uint32_t)sum;
				// C = (uint32_t)(sum>>32);
				// add(t,1,C);

				// sum = (uint64_t)S + (uint64_t)m[j] * (uint64_t)n[i-j];
				// S = (uint32_t)sum;
				// C = (uint32_t)(sum>>32);
				// t[0] = (uint64_t)S;
				// add(t,1,C);
		// }
		// m[i-SIZE]= t[0];
		// t[0] = t[1];
		// t[1] = t[2];
		// t[2] = 0;
	// }
	// m[SIZE] = t[0];
	// sub_cond(m,n,SIZE,resultSIZE);
// /*	for(index=0;index<SIZE;index++){
		// m[index] = resultSIZE[index];
	// }*/
	// int k;
	// for(k=0;k<SIZE;k++){
		// //res[k]=m[k];
		// res[k]=resultSIZE[k];
	// }
// }

// /* Carry addition algorithm */
// //void add(uint64_t *t, uint32_t i, uint32_t C, uint64_t *result3){
// void add(uint64_t *t, uint32_t i, uint32_t C){
	// uint64_t sum;
	// uint32_t S;
	// while (C != 0) {
		// sum = t[i] + (uint64_t)C;
		// S = (uint32_t)sum;
		// C = (uint32_t)(sum>>32);
		// t[i] = (uint64_t)S;
		// i = i+1;
	// }
	// //int index;
	// //for(index=0; index<3; index++){
		// //result3[index]=t[index];
	// //}
// }

// /* Conditional subtraction algorithm */
// void sub_cond(uint32_t *u, uint32_t *n, uint32_t SIZE, uint16_t resultSIZE){
	// uint32_t B = 0;
	// uint32_t t[SIZE];
	// int index;
	// for(index=0; index<SIZE; index++){
		// t[index] = 0;
	// }
	// int i;
	// uint32_t diff = 0;
	// for(i=0; i<SIZE; i++){
		// uint32_t diff = u[i]- n[i] - B;
		// if (u[i] >= n[i]+B){
			// B=0;
		// }
		// else  {
			// B=1;
		// }
		// t[i] = diff;
	// }
	// if (B == 0){
		// int j;
		// for(j=0;j<SIZE;j++){
			// resultSIZE[j]=t[j];
		// }
	// }
	// else {
		// int j;
		// for(j=0;j<SIZE;j++){
			// resultSIZE[j]=u[j];
		// }
	// }
// }
