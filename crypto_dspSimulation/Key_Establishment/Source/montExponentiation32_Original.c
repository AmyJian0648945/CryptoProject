#include "../Header/montExponentiation32.h"

/* xyR-1modm
	0 <= x,y < m
	x = sizeM elements
	y = sizeM elements
	m = sizeM elements
	result = sizeM elements
*/
void montMultiplication( uint32_t *x, uint32_t *y, uint32_t *m, uint32_t *result, uint16_t mInvLastBit, uint16_t sizeM, uint16_t sizeR){
	
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

	/* step 1 */
	zerosArray(A,sizeM+1);

	/* step 2 */
	/* n = sizeM*32; */
	n = (sizeR-1)*32;
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
void montExp( uint32_t *x, uint32_t *m, uint32_t *e, uint32_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE){
	
	uint32_t R[MAXLENGTH] = {0};	
	uint32_t Rmod[MAXLENGTH] = {0};
	uint32_t A[MAXLENGTH] = {0};
	uint32_t mInv[MAXLENGTH] = {0};
	uint32_t R2mod[MAXLENGTH] = {0};
	uint32_t one[MAXLENGTH] = {0};
	uint32_t xtilde[MAXLENGTH] = {0};
	uint32_t copyOfE[MAXLENGTH] = {0};
	uint32_t xExt[MAXLENGTH] = {0};
	uint16_t mInvLastBit = 0;
	uint16_t ePosMSB = 0;
	uint16_t t = 0;
	uint16_t msbWord = 0;
	uint16_t posWord = 0;
	uint16_t mPosMSB = 0;
	uint16_t mMSBWord = 0;
	uint16_t sizeR = 0;
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
 
	/* xExt has the same length as m */
	for(k=0;k<sizeM;k++){
		if (k<(sizeM-sizeX)){
			xExt[k] = 0x00;
		} else {
			xExt[k] = x[k-(sizeM-sizeX)];
		}
	}
	
	mPosMSB = positionMSB(m,sizeM);
	mMSBWord = mPosMSB/32;
	sizeR = sizeM-mMSBWord+1;
	
	zerosArray(R,sizeM+1);
	R[mMSBWord] = 0x0001;
	
	zerosArray(Rmod,sizeM);
	mod(R,m,Rmod,sizeM+1,sizeM);
	copyArray32(Rmod,A,sizeM);
	
	modSquare(Rmod,m,R2mod,sizeM,sizeM);
	
	modularInverse(m,R,mInv,sizeM,sizeM+1);
	mInvLastBit = mInv[sizeM]%2;

	one[sizeM-1] = 0x0001;
	montMultiplication(xExt,R2mod,m,xtilde,mInvLastBit,sizeM,sizeR);
	for(i=t;i>=0;i--){
		montMultiplication(A,A,m,A,mInvLastBit,sizeM,sizeR);
		ei = (copyOfE[msbWord]>>(31-posWord))%2;
		if (ei == 1){
			montMultiplication(A,xtilde,m,A,mInvLastBit,sizeM,sizeR);
		}
		multiplyByTwo(copyOfE,sizeE);
	}
	montMultiplication(A,one,m,A,mInvLastBit,sizeM,sizeR);
	copyArray32(A,result,sizeM);
}


