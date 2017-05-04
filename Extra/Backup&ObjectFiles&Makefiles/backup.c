#include "../Header/montExponentiation32.h"
/* 
void mont( uint32_t *x, uint32_t *y, uint32_t *n, uint32_t *nInv, uint32_t *result, uint16_t sizeM, uint16_t sizeMInv){
 	uint32_t t[3] = {0};
	uint32_t m[MAXLENGTH] = {0};
	uint64_t sum;
	uint32_t carrier;
	uint32_t partSum;
	int32_t nInv0;
	int i;
	int j;
	
	nInv0 = nInv[sizeMInv-1];

	for(i=0;i<sizeM;i++){
		for(j=0;j<i;j++){
			sum = (uint64_t)t[0] + (uint64_t)(x[j]*y[i-j]);
			partSum = (uint32_t)sum;
			carrier = (uint32_t)(sum>>32);
			add(t,1,carrier);
			
			sum = (uint64_t)partSum + (uint64_t)(m[j]*n[i-j]);
			partSum = (uint32_t)sum;
			carrier = (uint32_t)(sum>>32);
			t[0] = partSum;
			add(t,1,carrier);
		}
		
		sum = (uint64_t)t[0] + (uint64_t)(x[i]*y[0]);
		partSum = (uint32_t)sum;
		carrier = (uint32_t)(sum>>32);
		add(t,1,carrier);
		
		m[i] = (uint32_t)(partSum*nInv0);
		sum = (uint64_t)partSum + (uint64_t)(m[i]*n[0]);
		partSum = (uint32_t)sum;
		carrier = (uint32_t)(sum>>32);
		add(t,1,carrier);
		t[0] = t[1];
		t[1] = t[2];
		t[2] = 0x00;
		
	}
	
	for(i=sizeM;i<2*sizeM;i++){
		for(j=i-sizeM+1;j<sizeM;j++){
			sum = (uint64_t)t[0] + (uint64_t)(x[j]*y[i-j]);
			partSum = (uint32_t)sum;
			carrier = (uint32_t)(sum>>32);
			add(t,1,carrier);
			sum = (uint64_t)partSum + (uint64_t)(m[j]*n[i-j]);
			partSum = (uint32_t)sum;
			carrier = (uint32_t)(sum>>32);
			t[0] = partSum;
			add(t,1,carrier);
		}
		
		m[i-sizeM] = t[0];
		t[0] = t[1];
		t[1] = t[2];
		t[2] = 0;
	}

	m[sizeM] = t[0];
	sub_cond(m,n,result,sizeM);
}
 */
/* void mont( uint32_t *x, uint32_t *y, uint32_t *n, uint32_t *nInv, uint32_t *result, uint16_t size, uint16_t sizeMInv){
	uint32_t t[MAXLENGTH] = {0};
	uint32_t S = 0;
	uint32_t C;
	uint64_t sum;
	uint32_t m;
	uint32_t nInv0;
	int i;
	int j;
	uint32_t u[MAXLENGTH] = {0};
	
	nInv0 = -nInv[sizeMInv-1];
	for(i=0;i<size;i++){
		C = 0;
		for(j=0;j<size;j++){
			sum = (uint64_t)t[i+j] + (uint64_t)(x[j]*y[i]) + (uint64_t)C;
			S = (uint32_t)sum;
			C = (uint32_t)(sum>>32);
			t[i+j] = S;
		}
		
		t[i+size] = C;
	}
	
	for(i=0;i<size;i++){
		C = 0;
		m = (uint32_t)t[i]*nInv0;
		for(j=0;j<size;j++){
			sum = (uint64_t)t[i+j] + (uint64_t)(m*n[j]) + (uint64_t)C;
			S = (uint32_t)sum;
			C = (uint32_t)(sum>>32);
			t[i+j] = S;
		}
		add(t,i+size,C);
	}
	for(j=0;j<size;j++){
		u[j] = t[j+size];
	}
	sub_cond(u,n,result,size);
}
 */


/* 
void add( uint32_t *t, uint16_t i, uint32_t carrier){
	uint64_t sum = 0;
	while (carrier != 0){
		sum = (uint64_t)t[i] + (uint64_t)carrier;
		t[i] = (uint32_t) sum;
		carrier = (uint32_t)(sum>>32);
		i = i+1;
	}
}

void sub_cond( uint32_t *u, uint32_t *n, uint32_t *result, uint16_t sizeM){
	uint32_t copyOfU[MAXLENGTH] = {0};
	uint32_t nExt[MAXLENGTH] = {0};
	int i;
	nExt[sizeM] = 0;
	for(i=0;i<sizeM;i++){
		nExt[i] = n[i];
	}
	copyArray32(u,copyOfU,sizeM+1);
	flipArray(copyOfU, sizeM+1);
	flipArray(nExt, sizeM+1);
	if (isBiggerThanOrEqual(copyOfU,nExt,sizeM+1)){
		subtraction(copyOfU,nExt,copyOfU,sizeM+1);
		flipArray(copyOfU, sizeM+1);
	} else {
		flipArray(copyOfU, sizeM+1);
	}
	for(i=0;i<sizeM;i++){
		result[i] = copyOfU[i];
	}
}
 */

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
	uint32_t sumYM[MAXLENGTH] = {0};
/* 	uint32_t tempSum[MAXLENGTH] = {0}; */
	uint16_t n;
	uint16_t ui;
	uint16_t xi;
	uint16_t y0;
	uint16_t countIndex;
	uint16_t wordIndex;
	uint16_t posIndex;
/* 	uint16_t cond1;
	uint16_t cond2; */
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
	zerosArray(A,sizeM+1);

	countIndex = sizeM<<5;
	wordIndex = sizeM;
	posIndex = 0;
	
	addition(yExt,mExt,sumYM,sizeM+1);
	y0 = y[sizeM-1]%2;
	
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
		ui = (A[sizeM]%2 + xi*y0)*mInvLastBit;
		ui = ui%2;

		/* Step 2.2 */
		if (xi == 1){
			addition(A,yExt,A,sizeM+1);
		}
		if (ui == 1){
			addition(A,mExt,A,sizeM+1);
		}
/* 		cond1 = (xi==1);
		cond2 = (ui==1);
		if ( cond1 & cond2){
			addition(A,sumYM,A,sizeM+1);
		} else if (cond1){
			addition(A,yExt,A,sizeM+1);
		} else if (cond2){
			addition(A,mExt,A,sizeM+1);
		} */
		
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
	
	uint32_t R[MAXLENGTH];	
	uint32_t A[MAXLENGTH];
	uint32_t mInv[MAXLENGTH];
	uint32_t R2mod[MAXLENGTH];
	uint32_t one[MAXLENGTH];
	uint32_t xtilde[MAXLENGTH];
	uint32_t xExt[MAXLENGTH];
	/* uint16_t mInvLastBit; */
	uint32_t montResult[MAXLENGTH] = {0};
	uint16_t ePosMSB;
	uint16_t t;
	uint16_t mPosMSB;
	uint16_t mMSBWord;
	/* uint16_t sizeR; */
	uint16_t ei;
	uint16_t wordIndex;
	uint16_t posIndex;
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
	
/* 	if (isBiggerThan(xExt,m,sizeM)){
		printf("message > modulus\n; sizeM=%u",sizeM);
		mod(xExt,m,xExt,sizeM,sizeM);
	} */
	
	mPosMSB = positionMSB(m,sizeM);
	mMSBWord = mPosMSB>>5;
	/* sizeR = sizeM-mMSBWord+1; */
	
	zerosArray(R,sizeM+1);
	R[mMSBWord] = 0x0001;
	
	modularInverse(m,R,mInv,sizeM,sizeM+1);
	/* mInvLastBit = mInv[sizeM]%2; */
	mod(R,m,A,sizeM+1,sizeM);
	
	modSquare(A,m,R2mod,sizeM,sizeM);

	zerosArray(one, sizeM);
	one[sizeM-1] = 0x0001;
	/* montMultiplication(xExt,R2mod,m,xtilde,mInvLastBit,sizeM,sizeR); */
	mont(xExt,R2mod,m,mInv,montResult,sizeM);
	copyArray32(montResult,xtilde,sizeM);
	/* printArray32(A,"A",sizeM); */
	/* printArray32(montResult,"montResult",sizeM); */
	for(i=t;i>=0;i--){
		/* montMultiplication(A,A,m,A,mInvLastBit,sizeM,sizeR); */
		mont(A,A,m,mInv,montResult,sizeM);
		/* printArray32(montResult,"montResult",sizeM); */
		copyArray32(montResult,A,sizeM);
		ei = (e[wordIndex]>>(31-posIndex))%2;
		if ((posIndex+1)%32 == 0){
			wordIndex += 1;
			posIndex = 0;
		} else {
			posIndex += 1;
		}
		if (ei == 1){
			/* montMultiplication(A,xtilde,m,A,mInvLastBit,sizeM,sizeR); */
			mont(A,xtilde,m,mInv,montResult,sizeM);
			copyArray32(montResult,A,sizeM);
		}
	}
	/* montMultiplication(A,one,m,A,mInvLastBit,sizeM,sizeR);
	copyArray32(A,result,sizeM); */
/* 	mont(A,one,m,mInv,montResult,sizeM);
	copyArray32(montResult,A,sizeM);
	copyArray32(A,result,sizeM); */
}


