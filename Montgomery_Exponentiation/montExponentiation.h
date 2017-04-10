#ifndef	MONTEXPONENTIATION_H
#define MONTEXPONENTIATION_H

#define MAXLENGTH 128

/* xyR-1modm
	0 <= x,y < m
	x = sizeM elements
	y = sizeM elements
	m = sizeM elements
	result = sizeM elements
*/
void montMultiplication( uint16_t *x, uint16_t *y, uint16_t *m, uint16_t *result, uint16_t mInvLastBit, uint16_t sizeM, uint16_t sizeR){
	
	uint16_t n = 0;
	uint16_t copyOfX[MAXLENGTH] = {0};
	uint16_t yExt[MAXLENGTH] = {0};
	int i;
	int k;
	uint16_t mExt[MAXLENGTH] = {0};
	
	uint16_t A[MAXLENGTH] = {0};
	uint16_t ui = 0;
	uint16_t xi = 0;
	
	copyArray16(x,copyOfX,sizeM);
	xi = x[sizeM-1]%2;
	
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

	/* step 2 */
	/* n = sizeM*16; */
	n = (sizeR-1)*16;
	for(i=0;i<n;i++){
		/* Step 2.1 */
		xi = copyOfX[sizeM-1]%2;
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
		
		/* Because xi is the last bit of the last word 
		 => shift all bits one place to the right.*/
		divideByTwo(copyOfX,sizeM);
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
void montExp( uint16_t *x, uint16_t *m, uint16_t *e, uint16_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE){
	
	uint16_t ePosMSB = 0;
	uint16_t t = 0;
	uint16_t msbWord = 0;
	uint16_t posWord = 0;
	uint16_t mPosMSB = 0;
	uint16_t mMSBWord = 0;
	uint16_t sizeR = 0;
	uint16_t R[MAXLENGTH] = {0};	
	uint16_t Rmod[MAXLENGTH] = {0};
	uint16_t A[MAXLENGTH] = {0};	
	uint16_t mInvLastBit = 0;
	uint16_t mInv[MAXLENGTH] = {0};
	uint16_t R2mod[MAXLENGTH] = {0};
	uint16_t one[MAXLENGTH] = {0};
	uint16_t xtilde[MAXLENGTH] = {0};
	uint16_t copyOfE[MAXLENGTH] = {0};
	
	uint16_t xExt[MAXLENGTH] = {0};
	int i;
	int k;
	uint16_t ei = 0;
	
	ePosMSB = positionMSB(e,sizeE);
	t = 16*sizeE - ePosMSB - 1;
	msbWord = ePosMSB/16;
	posWord = ePosMSB%16;
	copyArray16(e,copyOfE,sizeE);
	
	/* xExt has the same length as m */
	for(k=0;k<sizeM;k++){
		if (k<(sizeM-sizeX)){
			xExt[k] = 0x00;
		} else {
			xExt[k] = x[k];
		}
	}
	
	mPosMSB = positionMSB(m,sizeM);
	mMSBWord = mPosMSB/16;
	sizeR = sizeM-mMSBWord+1;

	/* zerosArray(R,sizeM+1);
	R[0] = 0x0001; */
	
	zerosArray(R,sizeM+1);
	R[mMSBWord] = 0x0001;

	mod(R,m,Rmod,sizeM+1,sizeM);
	modSquare(Rmod,m,R2mod,sizeM,sizeM);
	copyArray16(Rmod,A,sizeM);
	
	modularInverse(m,R,mInv,sizeM,sizeM+1);
	mInvLastBit = mInv[sizeM]%2;

	one[sizeM-1] = 0x0001;
	montMultiplication(xExt,R2mod,m,xtilde,mInvLastBit,sizeM,sizeR);
	for(i=t;i>=0;i--){
	
		montMultiplication(A,A,m,A,mInvLastBit,sizeM,sizeR);
		ei = (copyOfE[msbWord]>>(15-posWord))%2;
		if (ei == 1){
			montMultiplication(A,xtilde,m,A,mInvLastBit,sizeM,sizeR);
		}
		multiplyByTwo(copyOfE,sizeE);
	}
	montMultiplication(A,one,m,A,mInvLastBit,sizeM,sizeR);
	for(i=0;i<sizeM;i++){
		result[i] = A[i];
	}
}

#endif