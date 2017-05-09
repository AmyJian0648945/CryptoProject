#include "../Header/montExponentiation32.h"

// void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *nInv, uint32_t *res, uint32_t SIZE, uint16_t sizeNInv, uint16_t samePointer)
// {
	// int i , j;
	// uint32_t t[MAXLENGTH] = { 0 };
	// uint32_t C = 0;
	// uint32_t m;
	// /*uint64_t mul;*/
	// uint64_t sum = 0;
	// int64_t value = 0;
	
	// flipArray(a,SIZE);
	// flipArray(b,SIZE);
	// flipArray(n,SIZE);
	// flipArray(nInv,sizeNInv);

	// value = nInv[0];
	// value = (int64_t)(nInv[0]);
	// value = -value;
	

	// for(i = 0; i < SIZE; i++){
		// C = 0;
		// for(j = 0; j < SIZE; j++){
			// sum = (uint64_t) t[i+j] + (uint64_t)a[j]*(uint64_t)b[i] + (uint64_t)C;

			// t[i+j] = (uint32_t) sum;
			// C = sum >> 32;
		// }
		// t[i + SIZE] = C;
	// }

	// for(i = 0; i < SIZE; i++){
		// C = 0;
		// /*mul =  ((uint64_t)t[i] * value) ;*/
		// m = (uint32_t)  ((uint64_t)t[i] * value);

		// for(j = 0; j < SIZE; j++){
			// sum = (uint64_t) t[i+j] + (uint64_t)m * (uint64_t)n[j] +(uint64_t)C;
			// /*S = (uint32_t) sum;*/
			// C = sum >> 32;
			// t[i+j] = (uint32_t) sum;
		// }
		// ADD(t, i+SIZE, C);
	// }

	// for(j = 0; j <= SIZE; j++){
		// res[j] = t[j+SIZE];
	// }
	// SUB_COND(res, n, SIZE);
	// /* flipArray(res, SIZE); */
	
	// if (samePointer == 0){
		// flipArray(a,SIZE);
	// }
	// flipArray(b,SIZE);
	// flipArray(n,SIZE);
	// flipArray(nInv,sizeNInv);
// }


// void ADD(uint32_t *t, int i, uint32_t C){
	// uint64_t sum = 0;

	// while(C != 0x00000000){
		// sum = (uint64_t)t[i] + (uint64_t)C;
		// C = sum >> 32;
		// /*S = (uint32_t) sum;*/
		// t[i] = (uint32_t) sum;
		// i++;
	// }
// }


// void SUB_COND(uint32_t *res, uint32_t *n, uint32_t SIZE){
// /* 	uint32_t B = 0x00000000;
	// uint32_t sub = 0;
	// uint32_t t[MAXLENGTH] = {0};
	// int i = 0;

	// for(i = 0; i < SIZE; i++){
		// sub = res[i] - n[i] - B;

		// if(res[i] >= (n[i] + B)) {
			// B = 0;
			// t[i] = sub;
		// }
		// else {
			// B = 1;
			// t[i] = sub;
		// }
	// }

	// if(B == 0){
		// for(i = 0; i < SIZE; i++){
			// res[i] = t[i];
		// }
	// } */
	
	// uint32_t n2[MAXLENGTH] = {0};
	// int i;
	// n2[0] = 0x00;

	// for(i=0;i<SIZE;i++) n2[i+1] = n[SIZE-i-1];

	// flipArray(res,SIZE+1);
	// if (isBiggerThanOrEqual(res,n2,SIZE+1)){

		// subtraction(res,n2,res,SIZE+1);
		// for(i=0;i<SIZE;i++) res[i] = res[i+1];
	// } 
	// else {
		// for(i=0;i<SIZE;i++) res[i] = res[i+1];	
	// }
	// /* flipArray(res,SIZE); */
// }



void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE)
{
	uint64_t t[3];
	int index;
	for(index=0; index<3; index++){
		t[index] = 0;
	}
	uint32_t m[SIZE+1];
	for(index=0; index<SIZE+1; index++){
		m[index] = 0;
	}
	int i,j;
	uint64_t sum;
	uint32_t S;
	uint32_t C;
	uint64_t resultSIZE[SIZE];
	for(index=0; index<SIZE; index++){
		resultSIZE[index] = 0;
	}

	for(i=0; i<SIZE; i++){
		for(j=0; j<i; j++){
			sum = t[0] + (uint64_t)a[j] * (uint64_t)b[i-j];
			S = (uint32_t)sum;
			C = (uint32_t)(sum>>32);
			add(t,1,C);

			sum = (uint64_t)S + (uint64_t)m[j] * (uint64_t)n[i-j];
			S = (uint32_t)sum;
			C = (uint32_t)(sum>>32);
			t[0] = (uint64_t)S;
			add(t,1,C);
		}

		sum = t[0] + (uint64_t)a[i] * (uint64_t)b[0];
		S = (uint32_t)sum;
		C = (uint32_t)(sum>>32);
		add(t,1,C);

		m[i] = (uint32_t)((uint64_t)S * (uint64_t)n0[0]);
		sum = (uint64_t)S + (uint64_t)m[i] * (uint64_t)n[0];
		S = (uint32_t)sum;
		C = (uint32_t)(sum>>32);
		add(t,1,C);

		t[0] = t[1];
		t[1] = t[2];
		t[2] = 0;
	}

	for(i=SIZE; i<2*SIZE; i++){
		for(j=i-SIZE+1; j<SIZE; j++){
			sum = t[0] + (uint64_t)a[j] * (uint64_t)b[i-j];
				S = (uint32_t)sum;
				C = (uint32_t)(sum>>32);
				add(t,1,C);

				sum = (uint64_t)S + (uint64_t)m[j] * (uint64_t)n[i-j];
				S = (uint32_t)sum;
				C = (uint32_t)(sum>>32);
				t[0] = (uint64_t)S;
				add(t,1,C);
		}
		m[i-SIZE]= t[0];
		t[0] = t[1];
		t[1] = t[2];
		t[2] = 0;
	}
	m[SIZE] = t[0];
	sub_cond(m,n,SIZE,resultSIZE);
/*	for(index=0;index<SIZE;index++){
		m[index] = resultSIZE[index];
	}*/
	int k;
	for(k=0;k<SIZE;k++){
		//res[k]=m[k];
		res[k]=resultSIZE[k];
	}
}

/* Carry addition algorithm */
//void add(uint64_t *t, uint32_t i, uint32_t C, uint64_t *result3){
void add(uint64_t *t, uint32_t i, uint32_t C){
	uint64_t sum;
	uint32_t S;
	while (C != 0) {
		sum = t[i] + (uint64_t)C;
		S = (uint32_t)sum;
		C = (uint32_t)(sum>>32);
		t[i] = (uint64_t)S;
		i = i+1;
	}
	//int index;
	//for(index=0; index<3; index++){
		//result3[index]=t[index];
	//}
}

/* Conditional subtraction algorithm */
void sub_cond(uint32_t *u, uint32_t *n, uint32_t SIZE, uint64_t *resultSIZE){
	uint32_t B = 0;
	uint32_t t[SIZE];
	int index;
	for(index=0; index<SIZE; index++){
		t[index] = 0;
	}
	int i;
	uint32_t diff = 0;
	for(i=0; i<SIZE; i++){
		uint32_t diff = u[i]- n[i] - B;
		if (u[i] >= n[i]+B){
			B=0;
		}
		else  {
			B=1;
		}
		t[i] = diff;
	}
	if (B == 0){
		int j;
		for(j=0;j<SIZE;j++){
			resultSIZE[j]=t[j];
		}
	}
	else {
		int j;
		for(j=0;j<SIZE;j++){
			resultSIZE[j]=u[j];
		}
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
	/* uint16_t mPosMSB = 0; */
	/* uint16_t mMSBWord = 0; */
	uint16_t ei = 0;
	uint16_t wordIndex = 0;
	uint16_t posIndex = 0;
	int i;
	int k;
	uint16_t mInvLastBit = 0;
	uint16_t middleR = 0;

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
	
	/* mPosMSB = positionMSB(m,sizeM); */
	/* mMSBWord = mPosMSB/32; */
	
	zerosArray(R,sizeM+1);
	R[0] = 0x0001;
	modularInverse(m,R,mInv,sizeM,sizeM+1);
	
	zerosArray(Rmod,sizeM);
	mod(R,m,Rmod,sizeM+1,sizeM);
	copyArray32(Rmod,A,sizeM);
/* 	for(k=0; k<(sizeM-sizeM); k++) 	 A[k] = 0x00;
	for(k=(sizeM-sizeM); k<sizeM; k++) A[k] = Rmod[k-(sizeM-sizeM)]; */
	
	modSquare(Rmod,m,tempArray,sizeM,sizeM);
/* 	for(k=0; k<(sizeM-sizeM); k++) 	 R2mod[k] = 0x00; */
/* 	for(k=(sizeM-sizeM); k<sizeM; k++) R2mod[k] = tempArray[k-(sizeM-sizeM)]; */
	
	mInvLastBit = mInv[sizeM]%2;
	middleR = 0;
	/* mont(xExt,tempArray,m,mInv,xtilde,sizeM,sizeM+1,0); */
	montMultiplication(xExt,tempArray,m,xtilde,mInvLastBit,sizeM,sizeM+1,middleR);
	for(i=t;i>=0;i--){
		for(k=0; k<sizeM; k++){
			tempArray[k] = A[k];
		}
		/* mont(A,tempArray,m,mInv,A,sizeM,sizeM+1,1); */
		montMultiplication(A,tempArray,m,A,mInvLastBit,sizeM,sizeM+1,middleR);
		ei = (e[wordIndex]>>(31-posIndex))%2;
		if ((posIndex+1)%32 == 0){
			wordIndex += 1;
			posIndex = 0;
		} else {
			posIndex += 1;
		}
		if (ei == 1){
			/* mont(A,xtilde,m,mInv,A,sizeM,sizeM+1,1); */
			montMultiplication(A,xtilde,m,A,mInvLastBit,sizeM,sizeM+1,middleR);
		}
	}
	for(k=0;k<sizeM;k++){
		tempArray[k] = 0x00;
	}
	tempArray[sizeM-1] = 0x0001;
	/* mont(A,tempArray,m,mInv,A,sizeM,sizeM+1,1); */
	montMultiplication(A,tempArray,m,A,mInvLastBit,sizeM,sizeM+1,middleR);
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
	
	/* uint32_t copyOfX[MAXLENGTH] = {0}; */
	uint32_t yExt[MAXLENGTH] = {0};
	uint32_t mExt[MAXLENGTH] = {0};
	uint32_t A[MAXLENGTH] = {0};
	uint32_t tempResult[MAXLENGTH] = {0};
	uint16_t n = 0;
	uint16_t ui = 0;
	uint16_t xi = 0;
	int i;
	int k;
	uint16_t countIndex;
	uint16_t wordIndex;
	uint16_t posIndex;

	countIndex = sizeM*32;
	wordIndex = sizeM;
	posIndex = 31;
	/* copyArray32(x,copyOfX,sizeM); */
	/* xi = x[sizeM-1]%2; */
	
	
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
	/* n = sizeM*32; */
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
		/* xi = copyOfX[sizeM-1]%2; */
		ui = (A[sizeM]%2 + xi*(yExt[sizeM]%2))*mInvLastBit;
		ui = ui%2;

		/* Step 2.2 */
		/* if (xi == 1){
			addition(A,yExt,A,sizeM+1);
		}
		if (ui == 1){
			addition(A,mExt,A,sizeM+1);
		} */
		if (xi == 1 & ui == 1){
			addition(A,tempResult,A,sizeM+1);
		} else if (xi == 1){
			addition(A,yExt,A,sizeM+1);
		} else if (ui == 1){
			addition(A,mExt,A,sizeM+1);
		}
		divideByTwo(A,sizeM+1);
		
		/* Because xi is the last bit of the last word 
		 => shift all bits one place to the right.*/
		/* divideByTwo(copyOfX,sizeM); */
	}

	/* step 3 */
	if (isBiggerThanOrEqual(A,mExt,sizeM+1) == 1){
		subtraction(A,mExt,A,sizeM+1);
	}

	for(k=0;k<sizeM;k++){
		result[k] = A[k+1];
	}

}


