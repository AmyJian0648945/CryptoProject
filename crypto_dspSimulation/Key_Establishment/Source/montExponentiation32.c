#include "../Header/montExponentiation32.h"

void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *nInv, uint32_t *res, uint32_t SIZE, uint16_t sizeNInv)
{
	int i , j;
	uint32_t t[MAXLENGTH] = { 0 };
	uint32_t C = 0, S = 0;
	uint32_t m;
	uint64_t mul;
	uint64_t sum = 0;
	int64_t value = 0;
	
	flipArray(a,SIZE);
	flipArray(b,SIZE);
	flipArray(n,SIZE);
	flipArray(nInv,sizeNInv);

	value = nInv[0];
	value = (int64_t)(nInv[0]);
	value = -value;
	

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

	for(i = 0; i < SIZE; i++){
		C = 0;
		mul =  ((uint64_t)t[i] * value) ;
		m = (uint32_t) mul;

		for(j = 0; j < SIZE; j++){
			sum = (uint64_t) t[i+j] + (uint64_t)m * (uint64_t)n[j] +(uint64_t)C;
			S = (uint32_t) sum;
			C = sum >> 32;
			t[i+j] = S;
		}
		ADD(t, i+SIZE, C);
	}

	for(j = 0; j <= SIZE; j++){
		res[j] = t[j+SIZE];
	}
	SUB_COND(res, n, SIZE);
	flipArray(res, SIZE);
	
	flipArray(a,SIZE);
	flipArray(b,SIZE);
	flipArray(n,SIZE);
	flipArray(nInv,sizeNInv);
}


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
/* 	uint32_t B = 0x00000000;
	uint32_t sub = 0;
	uint32_t t[MAXLENGTH] = {0};
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
	} */
	
	uint32_t n2[MAXLENGTH];
	int i;
	n2[0] = 0x00;
	for(i=0;i<SIZE;i++){
		n2[i+1] = n[SIZE-i-1];
	}
	flipArray(res,SIZE+1);
	if (isBiggerThanOrEqual(res,n2,SIZE+1)){
		subtraction(res,n2,res,SIZE+1);
		for(i=0;i<SIZE;i++){
			res[i] = res[i+1];
		}
	} else {
		for(i=0;i<SIZE;i++){
			res[i] = res[i+1];
		}
	}
	flipArray(res,SIZE);
}

/* xyR-1modm
	0 <= x,y < m
	x = sizeM elements
	y = sizeM elements
	m = sizeM elements
	result = sizeM elements
*/
/* void montMultiplication( uint32_t *x, uint32_t *y, uint32_t *m, uint32_t *result, uint16_t mInvLastBit, uint16_t sizeM, uint16_t sizeR){
	
	uint32_t copyOfX[MAXLENGTH] = {0};
	uint32_t yExt[MAXLENGTH] = {0};
	uint32_t mExt[MAXLENGTH] = {0};
	uint32_t A[MAXLENGTH] = {0};
	uint16_t n = 0;
	uint16_t ui = 0;
	uint16_t xi = 0;
	int i;
	int k;

	copyArray32(x,copyOfX,sizeM);
	xi = x[sizeM-1]%2;
	
	yExt[0] = 0x00;
	for(k=0;k<sizeM;k++){
		yExt[k+1] = y[k];
	}
	mExt[0] = 0x00;
	for(k=0;k<sizeM;k++){
		mExt[k+1] = m[k];
	}

	// step 1
	zerosArray(A,sizeM+1);

	// step 2
	// n = sizeM*32;
	n = (sizeR-1)*32;
	for(i=0;i<n;i++){
		// Step 2.1
		xi = copyOfX[sizeM-1]%2;
		ui = (A[sizeM]%2 + xi*(yExt[sizeM]%2))*mInvLastBit;
		ui = ui%2;

		// Step 2.2
		if (xi == 1){
			addition(A,yExt,A,sizeM+1);
		}
		if (ui == 1){
			addition(A,mExt,A,sizeM+1);
		}
		divideByTwo(A,sizeM+1);
		
		// Because xi is the last bit of the last word 
		 // => shift all bits one place to the right.
		divideByTwo(copyOfX,sizeM);
	}

	// step 3
	if (isBiggerThanOrEqual(A,mExt,sizeM+1) == 1){
		subtraction(A,mExt,A,sizeM+1);
	}

	for(k=0;k<sizeM;k++){
		result[k] = A[k+1];
	}

} */

/* x^(e)modm
	x <= m (sizeX <= sizeM)
	x = sizeX elements
	m = sizeM elements
	e = sizeE elements
	result = sizeM elements
*/
void montExp( uint32_t *x, uint32_t *m, uint32_t *e, uint32_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE){
	
	uint32_t R[MAXLENGTH] = {0};	
	uint32_t Rmod[MAXLENGTH] = {0};
	uint32_t A[MAXLENGTH] = {0};
	uint32_t mInv[MAXLENGTH] = {0};
	uint32_t R2mod[LENGTH] = {0};
	uint32_t one[LENGTH] = {0};
	uint32_t xtilde[LENGTH] = {0};
	uint32_t copyOfE[MAXLENGTH] = {0};
	uint32_t xExt[LENGTH] = {0};
	uint32_t mExt[LENGTH] = {0};
	uint32_t tempResult[LENGTH] = {0};
	uint32_t copyOfA[LENGTH] = {0};
	uint16_t size = 0;
	/* uint16_t mInvLastBit = 0; */
	uint16_t ePosMSB = 0;
	uint16_t t = 0;
	uint16_t msbWord = 0;
	uint16_t posWord = 0;
	uint16_t mPosMSB = 0;
	uint16_t mMSBWord = 0;
	/* uint16_t sizeR = 0; */
	uint16_t ei = 0;
	int i;
	int k;
	/* sizeR = words of R that are not equal to zero;
	actual length of R is equal to sizeM+1 */

	ePosMSB = positionMSB(e,sizeE);
	t = 32*sizeE - ePosMSB - 1;
	msbWord = ePosMSB/32;
	posWord = ePosMSB%32;
	copyArray32(e,copyOfE,sizeE);
 
	if (sizeX > sizeM){
		size = sizeX;
	} else {
		size = sizeM;
	}
	
	/* xExt has the same length as m */
	/*
	for(k=0;k<size;k++){
		if (k<(size-sizeX)){
			xExt[k] = 0x00;
		} else {
			xExt[k] = x[k-(size-sizeX)];
		}
	}*/
	for(k=0; k<(size-sizeX); k++) 	 xExt[k] = 0x00;
	for(k=(size-sizeX); k<size; k++) xExt[k] = x[k-(size-sizeX)];
	/*
	for(k=0;k<size;k++){
		if (k<(size-sizeM)){
			mExt[k] = 0x00;
		} else {
			mExt[k] = m[k-(size-sizeM)];
		}
	}*/
	for(k=0; k<(size-sizeM); k++) 	 mExt[k] = 0x00;
	for(k=(size-sizeM); k<size; k++) mExt[k] = m[k-(size-sizeM)];
	
	mPosMSB = positionMSB(m,sizeM);
	mMSBWord = mPosMSB/32;
	/* sizeR = sizeM-mMSBWord+1; */
	
	zerosArray(R,sizeM+1);
	R[mMSBWord] = 0x0001;
	
	zerosArray(Rmod,sizeM);
	mod(R,m,Rmod,sizeM+1,sizeM);
	/* copyArray32(Rmod,A,sizeM); */
	/*
	for(k=0;k<size;k++){
		if (k<(size-sizeM)){
			A[k] = 0x00;
		} else {
			A[k] = Rmod[k-(size-sizeM)];
		}
	}*/
	for(k=0; k<(size-sizeM); k++) 	 A[k] = 0x00;
	for(k=(size-sizeM); k<size; k++) A[k] = Rmod[k-(size-sizeM)];
	
	modSquare(Rmod,m,tempResult,sizeM,sizeM);
	/*
	for(k=0;k<size;k++){
		if (k<(size-sizeM)){
			R2mod[k] = 0x00;
		} else {
			R2mod[k] = tempResult[k-(size-sizeM)];
		}
	}*/
	for(k=0; k<(size-sizeM); k++) 	 R2mod[k] = 0x00;
	for(k=(size-sizeM); k<size; k++) R2mod[k] = tempResult[k-(size-sizeM)];
	
	modularInverse(m,R,mInv,sizeM,sizeM+1);
	/* mInvLastBit = mInv[sizeM]%2; */

	one[size-1] = 0x0001;
	/* montMultiplication(xExt,R2mod,mExt,xtilde,mInvLastBit,size,sizeR); */
	mont(xExt,R2mod,mExt,mInv,xtilde,size,sizeM+1);
	for(i=t;i>=0;i--){
		/* montMultiplication(A,A,mExt,A,mInvLastBit,size,sizeR); */
		for(k=0; k<size; k++){
			copyOfA[k] = A[k];
		}
		mont(A,copyOfA,mExt,mInv,tempResult,size,sizeM+1);
		for(k=0;k<size;k++){
			A[k] = tempResult[k];
		}
		ei = (copyOfE[msbWord]>>(31-posWord))%2;
		if (ei == 1){
			/* montMultiplication(A,xtilde,mExt,A,mInvLastBit,size,sizeR); */
			mont(A,xtilde,mExt,mInv,tempResult,size,sizeM+1);
			for(k=0;k<size;k++){
				A[k] = tempResult[k];
			}
		}
		multiplyByTwo(copyOfE,sizeE);
	}
	/* montMultiplication(A,one,mExt,A,mInvLastBit,size,sizeR); */
	mont(A,one,mExt,mInv,tempResult,size,sizeM+1);
	for(k=0;k<size;k++){
		result[k] = tempResult[k];
	}
	/* // copyArray32(A,result,size); */
}


