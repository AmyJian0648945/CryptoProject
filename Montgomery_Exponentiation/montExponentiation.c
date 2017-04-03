#define MAXLENGTH 128

/* xyR-1modm
	0 <= x,y < m
	x = sizeM elements
	y = sizeM elements
	m = sizeM elements
	result = sizeM elements
*/
void montMultiplication( uint16_t *x, uint16_t *y, uint16_t *m, uint16_t *result, uint16_t mInvLastBit, uint16_t sizeM){
	
	uint16_t n = sizeM*16;
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
	
	// step 1 //
	zerosArray(A,sizeM+1);

	// step 2 //
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
		
		//Because xi is the last bit of the last word 
		// => shift all bits one place to the right.
		divideByTwo(copyOfX,sizeM);
	}
	
	// step 3 //
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
	
	uint16_t ePosMSB = positionMSB(e,sizeE);
	uint16_t t = 16*sizeE - ePosMSB - 1;
	uint16_t msbWord = ePosMSB/16;
	uint16_t posWord = ePosMSB%16;
	uint16_t R[MAXLENGTH] = {0};	
	uint16_t Rmod[MAXLENGTH] = {0};
	uint16_t A[MAXLENGTH] = {0};	
	uint16_t mInvLastBit = 0;
	uint16_t mInv[MAXLENGTH] = {0};
	uint16_t Rmod2[MAXLENGTH] = {0};
	uint16_t R2mod[MAXLENGTH] = {0};
	uint16_t one[MAXLENGTH] = {0};
	uint16_t xtilde[MAXLENGTH] = {0};
	
	uint16_t xExt[MAXLENGTH] = {0};
	int i;
	int k;
	uint16_t ei = 0;
	
	printArray16(e,"e",sizeE);
	printf("ePosMSB = %u and t = %u and msbWord = %u and posWord = %u\n",ePosMSB,t,msbWord,posWord);

	
	/* xExt has the same length as m */
	for(k=0;k<sizeM;k++){
		if (k<(sizeM-sizeX)){
			xExt[k] = 0x00;
		} else {
			xExt[k] = x[k];
		}
	}
	
	zerosArray(R,sizeM+1);
	R[0] = 0x0001;

	
	modularInverse(m,R,mInv,sizeM,sizeM+1);

	printArray16(R,"R",sizeM+1);
	
	mod(R,m,Rmod,sizeM+1,sizeM);
	copyArray16(Rmod,A,sizeM);
	
	zerosArray(R,sizeM+1);
	R[0] = 0x0001;	
	squareProduct(Rmod,Rmod2,sizeM);
	printArray16(Rmod2,"squareProduct",2*sizeM);
	//multiplication(Rmod,Rmod,Rmod2,sizeM,sizeM);
	mod(Rmod2,m,R2mod,2*sizeM,sizeM);
	printArray16(R2mod,"Rsquaremodm",sizeM);

	zerosArray(R,sizeM+1);
	R[0] = 0x0001;
	
	// uint16_t mExt[MAXLENGTH] = {0};
	// uint16_t xExt2[MAXLENGTH] = {0};
	// mExt[0] = 0x00;
	// for(i=0;i<sizeM;i++){
		// mExt[i+(sizeR-sizeM)] = m[i];
		// xExt2[i+(sizeR-sizeM)] = xExt[i];
	// }
	// montMultiplication(R,R,mExt,R2mod,mInvLastBit,sizeR);
	// printArray16(R2mod,"R2mod",sizeM);
	
	one[sizeM-1] = 0x0001;
	
	montMultiplication(xExt,R2mod,m,xtilde,mInvLastBit,sizeM);
	
	for(i=t;i>=0;i--){
		
		montMultiplication(A,A,m,A,mInvLastBit,sizeM);
		ei = (e[msbWord]>>(15-posWord))%2;
		printf("ei = %u\n",ei);
		if (ei == 1){
			montMultiplication(A,xtilde,m,A,mInvLastBit,sizeM);
		}
		
		multiplyByTwo(e,sizeE);
	}
	montMultiplication(A,one,m,A,mInvLastBit,sizeM);
	
	for(i=0;i<sizeM;i++){
		result[i] = A[i];
	}
}