#include "../Header/montExponentiation32.h"

void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *nInv, uint32_t *res, uint32_t SIZE, uint16_t sizeNInv, uint16_t samePointer)
{
	int i , j;
	uint32_t t[VERYLONG] = { 0 };
	uint32_t C = 0;
	uint32_t m;
	uint64_t sum = 0;
	uint32_t value = 0;

	flipArray(a,SIZE);
	flipArray(b,SIZE);
	flipArray(n,SIZE);
	flipArray(nInv,sizeNInv);

	value = nInv[0];
	/* value = (int64_t)(nInv[0]); */
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
		m = (uint32_t)  ((uint64_t)t[i] * (uint64_t)value);

		for(j = 0; j < SIZE; j++){
			sum = (uint64_t) t[i+j] + (uint64_t)m * (uint64_t)n[j] +(uint64_t)C;

			C = sum >> 32;
			t[i+j] = (uint32_t) sum;
		}
		ADD(t, i+SIZE, C, 2*SIZE+1);
	}

	for(j = 0; j <= SIZE; j++){
		res[j] = t[j+SIZE];
	}
	SUB_COND(res, n, SIZE);
	
	if (samePointer == 0){
		flipArray(a,SIZE);
	}
	flipArray(b,SIZE);
	flipArray(n,SIZE);
	flipArray(nInv,sizeNInv);
}


void ADD(uint32_t *t, int i, uint32_t C, uint16_t size){
	uint64_t sum = 0;

	while((C != 0x00000000) && (i<size)){
		sum = (uint64_t)t[i] + (uint64_t)C;
		C = sum >> 32;
		t[i] = (uint32_t) sum;
		i++;
	}
}


void SUB_COND(uint32_t *res, uint32_t *n, uint32_t SIZE){

	uint32_t n2[MEDIUM] = {0};
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
}

/* x^(e)modm
	x <= m (sizeX <= sizeM)
	x = sizeX elements
	m = sizeM elements
	e = sizeE elements
	result = sizeM elements
*/
void montExp( uint32_t *x, uint32_t *m, uint32_t *e, uint32_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE){
	
	uint32_t R[MEDIUM] = {0};	
	uint32_t A[MEDIUM] = {0};
	uint32_t mInv[MEDIUM] = {0};
 	uint32_t Rmod[MEDIUM] = {0};
	uint32_t xtilde[MEDIUM] = {0};
	uint32_t xExt[MEDIUM] = {0};
	uint32_t tempArray[MEDIUM] = {0};
	uint16_t ePosMSB = 0;
	uint16_t t = 0;
	uint16_t ei = 0;
	uint16_t wordIndex = 0;
	uint16_t posIndex = 0;
	int i;
	int k;
	/*uint16_t mInvLastBit = 0;
	uint16_t middleR = 0;*/

	ePosMSB = positionMSB(e,sizeE);
	t = 32*sizeE - ePosMSB - 1;
	wordIndex = ePosMSB>>5;
	posIndex = ePosMSB%32;

	/* xExt has the same length as m */
	for(k=0; k<(sizeM-sizeX); k++) 	 xExt[k] = 0x00;
	for(k=(sizeM-sizeX); k<sizeM; k++) xExt[k] = x[k-(sizeM-sizeX)];

	zerosArray(R,sizeM+1);
	R[0] = 0x0001;
	modularInverse(m,R,mInv,sizeM,sizeM+1);
	
	zerosArray(Rmod,sizeM);
	mod(R,m,Rmod,sizeM+1,sizeM);
	copyArray32(Rmod,A,sizeM);
	
	modSquare(Rmod,m,tempArray,sizeM,sizeM);
	
	/*mInvLastBit = mInv[sizeM]%2;
	middleR = 0;*/
	mont(xExt,tempArray,m,mInv,xtilde,sizeM,sizeM+1,0);
	/* montMultiplication(xExt,tempArray,m,xtilde,mInvLastBit,sizeM,sizeM+1,middleR); */
	for(i=t;i>=0;i--){
		for(k=0; k<sizeM; k++){
			tempArray[k] = A[k];
		}
		mont(A,tempArray,m,mInv,A,sizeM,sizeM+1,1);
		/* montMultiplication(A,tempArray,m,A,mInvLastBit,sizeM,sizeM+1,middleR); */
		ei = (e[wordIndex]>>(31-posIndex))%2;
		if ((posIndex+1)%32 == 0){
			wordIndex += 1;
			posIndex = 0;
		} else {
			posIndex += 1;
		}
		if (ei == 1){
			mont(A,xtilde,m,mInv,A,sizeM,sizeM+1,1);
			/* montMultiplication(A,xtilde,m,A,mInvLastBit,sizeM,sizeM+1,middleR); */
		}
	}
	for(k=0;k<sizeM;k++){
		tempArray[k] = 0x00;
	}
	tempArray[sizeM-1] = 0x0001;
	mont(A,tempArray,m,mInv,A,sizeM,sizeM+1,1);
	/* montMultiplication(A,tempArray,m,A,mInvLastBit,sizeM,sizeM+1,middleR); */
	for(k=0;k<sizeM;k++){
		result[k] = A[k];
	}
}

/* xyR-1modm
	0 <= x,y < m
	x = sizeM elements
	y = sizeM elements
	m = sizeM elements
	result = sizeM elements
*/
void montMultiplication( uint32_t *x, uint32_t *y, uint32_t *m, uint32_t *result, uint16_t mInvLastBit, uint16_t sizeM, uint16_t sizeR, uint16_t middleR){
	
	uint32_t yExt[MEDIUM] = {0};
	uint32_t mExt[MEDIUM] = {0};
	uint32_t A[MEDIUM] = {0};
	uint32_t tempResult[MEDIUM] = {0};
	uint16_t n = 0;
	uint16_t ui = 0;
	uint16_t xi = 0;
	uint16_t countIndex;
	uint16_t wordIndex;
	uint16_t posIndex;
	int i;
	int k;

	countIndex = sizeM*32;
	wordIndex = sizeM;
	posIndex = 31;
	
	yExt[0] = 0x00;
	for(k=0;k<sizeM;k++){
		yExt[k+1] = y[k];
	}
	mExt[0] = 0x00;
	for(k=0;k<sizeM;k++){
		mExt[k+1] = m[k];
	}
	addition(mExt,yExt, tempResult, sizeM+1);

	/* step 1 */
	zerosArray(A,sizeM+1);

	/* step 2 */
	n = (sizeR-1)*32 + middleR*16;
	for(i=0;i<n;i++){
		/* Step 2.1 */
		if (countIndex%32 == 0){
			wordIndex -= 1;
			posIndex = 31;
			countIndex -= 1;
		} else {
			posIndex -= 1;
			countIndex -= 1;
		}
		xi = (x[wordIndex]>>(31-posIndex))%2;
		ui = (A[sizeM]%2 + xi*(yExt[sizeM]%2))*mInvLastBit;
		ui = ui%2;

		/* Step 2.2 */
		if ((xi == 1) & (ui == 1)){
			addition(A,tempResult,A,sizeM+1);
		} else if (xi == 1){
			addition(A,yExt,A,sizeM+1);
		} else if (ui == 1){
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


