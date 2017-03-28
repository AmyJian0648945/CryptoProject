/* xyR-1modm
	0 <= x,y < m
	x = sizeM elements
	y = sizeM elements
	m = sizeM elements
*/
void montMul( uint16_t *x, uint16_t *y, uint16_t *m, uint16_t *result, uint16_t mInvLastBit, uint16_t sizeM){
	
	uint16_t mPosMSB = positionMSB(m,sizeM);
	uint16_t n = sizeM*16 - mPosMSB;
	int i;
	
	uint16_t yExt[sizeM+1];
	int k;
	yExt[0] = 0x00;
	for(k=0;k<sizeM;k++){
		yExt[k+1] = y[k];
	}
	uint16_t mExt[sizeM+1];
	mExt[0] = 0x00;
	for(k=0;k<sizeM;k++){
		mExt[k+1] = m[k];
	}

	uint16_t A[sizeM+1];
	uint16_t ui = 0;
	uint16_t xi = 0;
	// step 1 //
	zerosArray(A,sizeM+1);
	// step 2 //
	for(i=0;i<n;i++){
		xi = x[sizeM-1]%2;
		ui = (A[sizeM]%2 + xi*(y[sizeM-1]%2))*mInvLastBit;
		ui = ui%2;
		
		if (xi == 1){
			addition(A,yExt,A,sizeM+1);
		}
		if (ui == 1){
			addition(A,mExt,A,sizeM+1);
		}
		divideByTwo(A,sizeM+1);
		divideByTwo(x,sizeM);
	}
	// step 3 //
	if (isBiggerThanOrEqual(A,mExt,sizeM+1)){
		subtractionShort(A,mExt,A,sizeM+1);
	}
	
	for(k=0;k<sizeM;k++){
		result[k] = A[k+1];
	}
}

/* x^(e)modm
*/
void montExp( uint16_t *x, uint16_t *m, uint16_t *e, uint16_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE){
	
	uint16_t ePosMSB = positionMSB(e,sizeE);
	uint16_t t = 16*sizeE - ePosMSB - 1;
	uint16_t msbWord = ePosMSB/16;
	uint16_t posWord = ePosMSB%16;
	// printf(" ePosMSB = %u and t = %u \n",ePosMSB,t);
	// printf(" msbWord = %u and posWord = %u \n",msbWord,posWord);
	
	uint16_t xExt[sizeM];
	int i;
	int k;
	for(k=0;k<sizeM;k++){
		if (k<(sizeM-sizeX)){
			xExt[k] = 0x00;
		} else {
			xExt[k] = x[k];
		}
	}
	// char nameM[2] = "m";
	// printArray(m,nameM,sizeM);
	uint16_t mPosMSB = positionMSB(m,sizeM);
	uint16_t l = 16*sizeM - mPosMSB;
	uint16_t nbBitsR = l+1;
	uint16_t msbWordR = nbBitsR/16;
	uint16_t msbPosR = nbBitsR%16;
	// printf(" mPosMSB = %u and l = %u \n",mPosMSB,l);
	// printf(" nbBitsR = %u and msbWordR = %u and msbPosR = %u \n",nbBitsR,msbWordR,msbPosR);
	
	uint16_t mInv[sizeM];
	uint16_t R[sizeM+1];
	zerosArray(R,sizeM+1);
	// R[0] = 0x0001;
	R[sizeM+1-1-msbWordR] = (0x01)<<(msbPosR-1);
	char nameR[2] = "R";
	printArray(R,nameR,sizeM+1);
	modularInverseShort(m,R,mInv,sizeM,sizeM+1);
	char nameInv[5] = "mInv";
	printArray(mInv,nameInv,sizeM);
	
	uint16_t Rmod[sizeM];
	mod(R,m,Rmod,sizeM+1,sizeM);
	uint16_t Rmod2[2*sizeM];
	// squareProduct(Rmod,Rmod2,sizeM);
	multiplication(Rmod,Rmod,Rmod2,sizeM,sizeM);
	uint16_t R2mod[sizeM];
	mod(Rmod2,m,R2mod,2*sizeM,sizeM);
	char nameRmod[5] = "Rmod";
	char nameR2mod[6] = "R2mod";
	printArray(Rmod,nameRmod,sizeM);
	printArray(R2mod,nameR2mod,sizeM);

	uint16_t mInvLastBit = mInv[sizeM-1]%2;
	// printf(" mInvLastBit = %u\n",mInvLastBit);

	uint16_t xtilde[sizeM];
	uint16_t A[sizeM];
	uint16_t one[sizeM];
	zerosArray(one,sizeM);
	one[sizeM-1] = 0x0001;
	copyArray(Rmod,A,sizeM);
	// char nameA[2] = "A";
	// printArray(A,nameA,sizeM);
	montMul(x,R2mod,m,xtilde,mInvLastBit,sizeM);
	
	uint16_t ei = 0;
	// printf(" t = %u\n",t);
	for(i=t;i>=0;i--){
		printf(" i = %u\n",i);
		montMul(A,A,m,A,mInvLastBit,sizeM);
		ei = (e[msbWord]>>(15-posWord))%2;
		printf(" ei = %u\n",ei);
		if (ei == 1){
			montMul(A,xtilde,m,A,mInvLastBit,sizeM);
		}
		multiplyByTwo(e,sizeE);
	}
	montMul(A,one,m,A,mInvLastBit,sizeM);
	
	copyArray(A,result,sizeM);
	// printArray(A,nameA,sizeM);

}