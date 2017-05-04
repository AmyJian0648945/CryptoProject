
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
	uint32_t mExt[MAXLENGTH] = {0};
	uint32_t tempResult[MAXLENGTH];
	uint32_t copyOfA[MAXLENGTH];
	uint16_t mInvLastBit = 0;
	uint16_t ePosMSB = 0;
	uint16_t t = 0;
	uint16_t ei = 0;
	uint16_t wordIndex = 0;
	uint16_t posIndex = 0;
	int i;
	int k;
	uint16_t size;
	
	ePosMSB = positionMSB(e,sizeE);
	t = (sizeE<<5) - ePosMSB - 1;
	wordIndex = ePosMSB>>5;
	posIndex = ePosMSB%32;
 
	if (sizeX > sizeM)
		size = sizeX;
	else
		size = sizeM;
	
	/* xExt has the same length as mExt, more specific length = size */
	for(k=0;k<size;k++){
		if (k<(size-sizeX)){
			xExt[k] = 0x00;
		} else {
			xExt[k] = x[k-(size-sizeX)];
		}
	}
	for(k=0;k<size;k++){
		if (k<(size-sizeM)){
			mExt[k] = 0x00;
		} else {
			mExt[k] = m[k-(size-sizeM)];
		}
	}
	
	if (isBiggerThanOrEqual(xExt,mExt,size)){
		printf("problem? xExt>mExt\n");
	}

	zerosArray(R,size+1);
	R[0] = 0x0001;

	modularInverse(mExt,R,mInv,size,size+1);
	mInvLastBit = mInv[size]%2;

	copyArray32(R,A,size+1);
	modFaster(A,mExt,size+1,size);
	for(i=0;i<size;i++){
		A[i] = A[i+1];
	}
	
	modSquare(A,mExt,R2mod,size,size);
	
	zerosArray(one,size);
	one[size-1] = 0x0001;
	montMultiplication(xExt,R2mod,m,xtilde,mInvLastBit,size,size+1);
	/* mont(xExt,R2mod,mExt,mInv,xtilde,size,size+1); */
	for(i=t;i>=0;i--){
		montMultiplication(A,A,m,A,mInvLastBit,size,size+1);
		/* copyArray32(A,copyOfA,size); */
		/* mont(A,copyOfA,mExt,mInv,tempResult,size,size+1); */
		/* copyArray32(tempResult,A,size); */
		ei = (e[wordIndex]>>(31-posIndex))%2;
		if ((posIndex+1)%32 == 0){
			wordIndex += 1;
			posIndex = 0;
		} else {
			posIndex += 1;
		}
		if (ei == 1){
			montMultiplication(A,xtilde,m,A,mInvLastBit,size,size+1);
			/* mont(A,xtilde,mExt,mInv,tempResult,size,size+1); */
			/* for(k=0;k<size;k++){ */
				/* A[k] = tempResult[k]; */
			/* } */
		}
	}
	montMultiplication(A,one,m,A,mInvLastBit,size,size+1);
	copyArray32(A,result,sizeM);
	/* mont(A,one,mExt,mInv,tempResult,size,size+1); */
	/* copyArray32(tempResult,result,size); */
}


