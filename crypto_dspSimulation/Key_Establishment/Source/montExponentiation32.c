#include "../Header/montExponentiation32.h"
/*
 * montgomery.c
 *
 */

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


void SUB_COND(uint32_t *res, uint32_t *n, uint16_t size){
/* 	uint32_t B = 0x00000000;
	uint32_t sub = 0;
	uint32_t t[32] = {0};
	int i = 0;


	for(i = 0; i < size; i++){
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
		for(i = 0; i < size; i++){
			res[i] = t[i];
		}
	} */
	
	if (isBiggerThanOrEqual(res,n,size)){
		subtraction(res,n,res,size);
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



	/* // t = a * b */
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

	/* // mod */
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
		/* //xil_printf("  SUM IS S = %x  C = %x",S,C ); */
		ADD(t, i+SIZE, C);
	}

	/* // output */
	for(j = 0; j <= SIZE; j++){
		res[j] = t[j+SIZE];
	}
	SUB_COND(res, n, SIZE);


}



/* xyR-1modm
	0 <= x,y < m
	x = sizeM elements
	y = sizeM elements
	m = sizeM elements
	result = sizeM elements
*/
void montMultiplication( uint32_t *x, uint32_t *y, uint32_t *m, uint32_t *result, uint16_t mInvLastBit, uint16_t sizeM, uint16_t sizeR){
	
	uint32_t yExt[MAXLENGTH] = {0};
	uint32_t mExt[MAXLENGTH] = {0};
	uint32_t A[MAXLENGTH] = {0};
	uint16_t n = 0;
	uint16_t ui = 0;
	uint16_t xi = 0;
	uint16_t countIndex = 0;
	uint16_t wordIndex = 0;
	uint16_t posIndex = 0;
	int i;
	int k;

	yExt[0] = 0x00;
	for(k=0;k<sizeM;k++){
		yExt[k+1] = y[k];
	}
	mExt[0] = 0x00;
	for(k=0;k<sizeM;k++){
		mExt[k+1] = m[k];
	}

	/* step 1 */
	/* zerosArray(A,sizeM+1); */

	countIndex = sizeM<<5;
	wordIndex = sizeM;
	posIndex = 0;
	
	/* step 2 */
	/* n = sizeM*32; */
	n = (sizeR-1)<<5;
	for(i=0;i<n;i++){
		/* Step 2.1 */
		if (countIndex%32 == 0){
			wordIndex -= 1;
			posIndex = 31;
		} else {
			posIndex -= 1;
		}
		countIndex -= 1;
		xi = (x[wordIndex]>>(31-posIndex))%2;
		ui = (A[sizeM]%2 + xi*(yExt[sizeM]%2))*mInvLastBit;
		ui = ui%2;

		/* Step 2.2 */
		if (xi == 1){
			addition(A,yExt,A,sizeM+1);
		}
		if (ui == 1){
			addition(A,mExt,A,sizeM+1);
		}
		divideByTwo(A,sizeM+1);
	}

	/* step 3 */
	if (isBiggerThanOrEqual(A,mExt,sizeM+1) == 1){
		subtraction(A,mExt,A,sizeM+1);
	}

	for(k=0;k<sizeM;k++){
		result[k] = A[k+1];
	}

}

/* x^(e)modm
	x <= m (sizeX <= sizeM)
	x = sizeX elements
	m = sizeM elements
	e = sizeE elements
	result = sizeM elements
*/
void montExp( uint32_t *x, uint32_t *m, uint32_t *e, uint32_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE){
	
	uint32_t R[MAXLENGTH] = {0};	
	uint32_t A[MAXLENGTH] = {0};
	uint32_t mInv[MAXLENGTH] = {0};
	uint32_t R2mod[MAXLENGTH] = {0};
	uint32_t one[MAXLENGTH] = {0};
	uint32_t xtilde[MAXLENGTH] = {0};
	uint32_t xExt[MAXLENGTH] = {0};
	/* uint16_t mInvLastBit = 0; */
	uint16_t ePosMSB = 0;
	uint16_t t = 0;
	uint16_t mPosMSB = 0;
	uint16_t mMSBWord = 0;
	/* uint16_t sizeR = 0; */
	uint16_t ei = 0;
	uint16_t wordIndex = 0;
	uint16_t posIndex = 0;
	int i;
	int k;
	/* sizeR = words of R that are not equal to zero;
	actual length of R is equal to sizeM+1 */

	ePosMSB = positionMSB(e,sizeE);
	t = (sizeE<<5) - ePosMSB - 1;
	wordIndex = ePosMSB>>5;
	posIndex = ePosMSB%32;
 
	/* xExt has the same length as m */
	for(k=0;k<sizeM;k++){
		if (k<(sizeM-sizeX)){
			xExt[k] = 0x00;
		} else {
			xExt[k] = x[k-(sizeM-sizeX)];
		}
	}
	
	mPosMSB = positionMSB(m,sizeM);
	mMSBWord = mPosMSB>>5;
	/* sizeR = sizeM-mMSBWord+1; */
	
	zerosArray(R,sizeM+1);
	R[mMSBWord] = 0x0001;
	
	modularInverse(m,R,mInv,sizeM,sizeM+1);
	/* mInvLastBit = mInv[sizeM]%2; */
	
	mod(R,m,A,sizeM+1,sizeM);
	
	modSquare(A,m,R2mod,sizeM,sizeM);

	one[sizeM-1] = 0x0001;
	/* montMultiplication(xExt,R2mod,m,xtilde,mInvLastBit,sizeM,sizeR); */
	mont(xExt,R2mod,m,mInv,xtilde,sizeM);
	for(i=t;i>=0;i--){
		/* montMultiplication(A,A,m,A,mInvLastBit,sizeM,sizeR); */
		mont(A,A,m,mInv,A,sizeM);
		ei = (e[wordIndex]>>(31-posIndex))%2;
		if ((posIndex+1)%32 == 0){
			wordIndex += 1;
			posIndex = 0;
		} else {
			posIndex += 1;
		}
		if (ei == 1){
			/* montMultiplication(A,xtilde,m,A,mInvLastBit,sizeM,sizeR); */
			mont(A,xtilde,m,mInv,A,sizeM);
		}
	}
	/* montMultiplication(A,one,m,A,mInvLastBit,sizeM,sizeR); */
	mont(A,one,m,mInv,A,sizeM);
	copyArray32(A,result,sizeM);
}


