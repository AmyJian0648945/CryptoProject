#include "../Header/montExponentiation32.h"

void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *nInv, uint32_t *res, uint32_t SIZE, uint16_t sizeNInv, uint16_t samePointer)
{
	int i , j;
	uint32_t t[MAXLENGTH] = { 0 };
	uint32_t C = 0;
	uint32_t m;
	/*uint64_t mul;*/
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

			t[i+j] = (uint32_t) sum;
			C = sum >> 32;
		}
		t[i + SIZE] = C;
	}

	for(i = 0; i < SIZE; i++){
		C = 0;
		/*mul =  ((uint64_t)t[i] * value) ;*/
		m = (uint32_t)  ((uint64_t)t[i] * value);

		for(j = 0; j < SIZE; j++){
			sum = (uint64_t) t[i+j] + (uint64_t)m * (uint64_t)n[j] +(uint64_t)C;
			/*S = (uint32_t) sum;*/
			C = sum >> 32;
			t[i+j] = (uint32_t) sum;
		}
		ADD(t, i+SIZE, C);
	}

	for(j = 0; j <= SIZE; j++){
		res[j] = t[j+SIZE];
	}
	SUB_COND(res, n, SIZE);
	/* flipArray(res, SIZE); */
	
	if (samePointer == 0){
		flipArray(a,SIZE);
	}
	flipArray(b,SIZE);
	flipArray(n,SIZE);
	flipArray(nInv,sizeNInv);
}


void ADD(uint32_t *t, int i, uint32_t C){
	uint64_t sum = 0;

	while(C != 0x00000000){
		sum = (uint64_t)t[i] + (uint64_t)C;
		C = sum >> 32;
		/*S = (uint32_t) sum;*/
		t[i] = (uint32_t) sum;
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
	
	uint32_t n2[MAXLENGTH] = {0};
	int i;
	n2[0] = 0x00;

	for(i=0;i<SIZE;i++) n2[i+1] = n[SIZE-i-1];

	flipArray(res,SIZE+1);
	if (isBiggerThanOrEqual(res,n2,SIZE+1)){

		subtraction(res,n2,res,SIZE+1);
		for(i=0;i<SIZE;i++) res[i] = res[i+1];
	} 
	else {
		for(i=0;i<SIZE;i++) res[i] = res[i+1];	
	}
	/* flipArray(res,SIZE); */
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
 	uint32_t Rmod[MAXLENGTH] = {0};
/* 	uint32_t R2mod[LENGTH] = {0}; */
/* 	uint32_t one[LENGTH] = {0}; */
	uint32_t xtilde[LENGTH] = {0};
	uint32_t xExt[LENGTH] = {0};
	/* uint32_t mExt[LENGTH] = {0}; */
	uint32_t tempArray[LENGTH] = {0};
/* 	uint16_t size = 0; */
	uint16_t ePosMSB = 0;
	uint16_t t = 0;
	uint16_t mPosMSB = 0;
	uint16_t mMSBWord = 0;
	uint16_t ei = 0;
	uint16_t wordIndex = 0;
	uint16_t posIndex = 0;
	int i;
	int k;

	ePosMSB = positionMSB(e,sizeE);
	t = 32*sizeE - ePosMSB - 1;
	wordIndex = ePosMSB>>5;
	posIndex = ePosMSB%32;
	
/*  	if (sizeX > sizeM) size = sizeX;
	else
		size = sizeM; */
	
	
	/* xExt has the same length as m */
	for(k=0; k<(sizeM-sizeX); k++) 	 xExt[k] = 0x00;
	for(k=(sizeM-sizeX); k<sizeM; k++) xExt[k] = x[k-(sizeM-sizeX)];

	/* for(k=0; k<(size-sizeM); k++) 	 mExt[k] = 0x00; */
	/* for(k=(size-sizeM); k<size; k++) mExt[k] = m[k-(size-sizeM)]; */
	
	mPosMSB = positionMSB(m,sizeM);
	mMSBWord = mPosMSB/32;
	
	zerosArray(R,sizeM+1);
	R[mMSBWord] = 0x0001;
	modularInverse(m,R,mInv,sizeM,sizeM+1);
	
	zerosArray(Rmod,sizeM);
	mod(R,m,Rmod,sizeM+1,sizeM);
	copyArray32(Rmod,A,sizeM);
/* 	for(k=0; k<(sizeM-sizeM); k++) 	 A[k] = 0x00;
	for(k=(sizeM-sizeM); k<sizeM; k++) A[k] = Rmod[k-(sizeM-sizeM)]; */
	
	modSquare(Rmod,m,tempArray,sizeM,sizeM);
/* 	for(k=0; k<(sizeM-sizeM); k++) 	 R2mod[k] = 0x00; */
/* 	for(k=(sizeM-sizeM); k<sizeM; k++) R2mod[k] = tempArray[k-(sizeM-sizeM)]; */
	
	mont(xExt,tempArray,m,mInv,xtilde,sizeM,sizeM+1,0);
	for(i=t;i>=0;i--){
		for(k=0; k<sizeM; k++){
			tempArray[k] = A[k];
		}
		mont(A,tempArray,m,mInv,A,sizeM,sizeM+1,1);
		ei = (e[wordIndex]>>(31-posIndex))%2;
		if ((posIndex+1)%32 == 0){
			wordIndex += 1;
			posIndex = 0;
		} else {
			posIndex += 1;
		}
		if (ei == 1){
			mont(A,xtilde,m,mInv,A,sizeM,sizeM+1,1);
		}
	}
	for(k=0;k<sizeM;k++){
		tempArray[k] = 0x00;
	}
	tempArray[sizeM-1] = 0x0001;
	mont(A,tempArray,m,mInv,A,sizeM,sizeM+1,1);
	for(k=0;k<sizeM;k++){
		result[k] = A[k];
	}
}


