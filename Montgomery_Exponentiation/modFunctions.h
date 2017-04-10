#ifndef MODFUNCTIONS_H
#define MODFUNCTIONS_H

#define MAXLENGTH 128

uint16_t positionMSB(uint16_t *array, uint16_t size);
void from2to16(uint16_t *binaryString, uint16_t *output, uint16_t size);
void mod(uint16_t *a, uint16_t *N, uint16_t *result, uint16_t sizeA, uint16_t sizeModulus);
void squareProduct(uint16_t *a, uint16_t *product, uint16_t size);
void multiplication(uint16_t *x, uint16_t *y, uint16_t *product, uint16_t sizeX, uint16_t sizeY);
void division(uint16_t *x, uint16_t *y, uint16_t *resultDiv, uint16_t *resultRem, uint16_t sizeX, uint16_t sizeY);

/* 
	Turns an array of binaries (binaryString) into an array of 16-bit numbers (output).
	Size is the number of elements in binaryString.
*/
void from2to16(uint16_t *binaryString, uint16_t *output, uint16_t size){
	int k;
	int m;
	uint16_t nbOfHexadecimals = 0;
	uint16_t remainder = 0;
	uint16_t tempSum = 0;
	
	nbOfHexadecimals = size/16;
	remainder = size%16;
	for(k=0;k<nbOfHexadecimals;k++){
		tempSum = 0;
		for(m=0;m<16;m++){
			tempSum += binaryString[16*k+m]<<m;
		}
		output[k] = tempSum;
	}
	tempSum = 0;
	for(m=0;m<remainder;m++){
		tempSum += binaryString[nbOfHexadecimals*16+m]<<m;
	}
	output[nbOfHexadecimals] = tempSum;
}

/*	Calculates the position of the most significant bit in the input array.
	Size is the number of elements in the input array.
*/
uint16_t positionMSB(uint16_t *array, uint16_t size){
	
	uint16_t result = 0;
	int i;
	int index = 0;
	int lastOne = 0;
	uint16_t word = 0;
	
	for(i=0;i<size;i++){
		if (array[i] != 0){
			word = array[i];
			for(index=0;index<16;index++){
				word = array[i]>>index;
				if (word%2 != 0)
					lastOne = index;
			}
			result = i*16+(15-lastOne);
			return result;
		}
		/* else: continue*/
	}
	return size*16;
}

/*	Calculates a mod N and stores it in result; a has sizeA elements, N has sizeModulus elements; result has sizeModulus elements. (with sizeA >= sizeModulus).
*/
void mod(uint16_t *a, uint16_t *N, uint16_t *result, uint16_t sizeA, uint16_t sizeModulus){
	
	uint16_t Nextended[MAXLENGTH] = {0};
	uint16_t copyOfA[MAXLENGTH] = {0};
	uint16_t comparison = 0;
	int i;

	zerosArray(Nextended,sizeA);
	for(i=0;i<sizeModulus;i++){
		Nextended[i+(sizeA-sizeModulus)] = N[i];
	}
	copyArray16(a,copyOfA,sizeA);
	
	comparison = isBiggerThanOrEqual(copyOfA,Nextended,sizeA);
	while (comparison > 0){
		subtraction(copyOfA,Nextended,copyOfA,sizeA);
		comparison = isBiggerThanOrEqual(copyOfA,Nextended,sizeA);
	}
	for(i=0;i<sizeModulus;i++){
		result[i] = copyOfA[i+(sizeA-sizeModulus)];
	}
}

/* Multiple-precision squaring
	Calculates the square product of input a 
	uint16_t *a = input array
	uint16_t *product = array in which to save the result
	uint16_t sizeX = length of input array
*/
void squareProduct(uint16_t *a, uint16_t *product, uint16_t sizeX){
	uint16_t posMSB = positionMSB(a,sizeX);
	uint16_t copyOfA[MAXLENGTH] = {0};
	uint16_t copy2[MAXLENGTH] = {0};
	uint16_t t = sizeX*16 - posMSB;
	uint16_t sizeProduct = 2*sizeX;
	int i;
	int j;
	uint16_t w[MAXLENGTH] = {0};
	uint16_t u = 0;
	uint16_t v = 0;
	uint16_t c = 0;
	uint16_t tempsum = 0;
	uint16_t xi = 0;
	uint16_t xj = 0;
	uint16_t sizeResult;
	uint16_t result[MAXLENGTH] = {0};

	copyArray16(a,copyOfA,sizeX);
	zerosArray(w,2*t);

	for(i=0;i<t;i++){

		copyArray16(copyOfA,copy2,sizeX);

		xi = copyOfA[sizeX-1]%2;

		tempsum = w[2*i] + xi*xi;
		v = tempsum%2;
		u = (tempsum>>1);
		w[2*i] = v;
		c = u;

		
		for(j=i+1;j<t;j++){
			divideByTwo(copy2,sizeX);
			xj = copy2[sizeX-1]%2;
			tempsum = w[i+j] + 2*xj*xi + c;
			v = tempsum%2;
			u = (tempsum>>1);
			w[i+j] = v;
			c = u;
		}
		
		w[i+t] = u;
		divideByTwo(copyOfA,sizeX);
	}

	if (2*t%16 == 0)
		sizeResult = 2*t/16;
	else
		sizeResult = 2*t/16+1;

	from2to16(w,result,2*t);
	for(i=0;i<sizeResult;i++){
		product[sizeProduct-1-i] = result[i];
	}
}

/*	Multiple-precision multiplication
	*/
void multiplication(uint16_t *a, uint16_t *b, uint16_t *product, uint16_t sizeA, uint16_t sizeB){
	
	uint16_t sizeProduct = sizeA + sizeB;
	uint16_t AposMSB = positionMSB(a,sizeA);
	uint16_t BposMSB = positionMSB(b,sizeB);
	uint16_t copyOfA[MAXLENGTH] = {0};
	uint16_t copyOfB[MAXLENGTH] = {0};
	uint16_t copy2A[MAXLENGTH] = {0};
	uint16_t n = sizeA*16 - AposMSB - 1;
	uint16_t t = sizeB*16 - BposMSB - 1;
	int i;
	int j;
	uint16_t w[MAXLENGTH] = {0};
	uint16_t u = 0;
	uint16_t v = 0;
	uint16_t c = 0;
	uint16_t tempSum = 0;
	uint16_t yi = 0;
	uint16_t xj = 0;	
	uint16_t sizeResult = 0;
	uint16_t result[MAXLENGTH] = {0};
	
	copyArray16(a,copyOfA,sizeA);
	copyArray16(b,copyOfB,sizeB);
	copyArray16(a,copy2A,sizeA);
	
	/* Step 1 */
	zerosArray(w,n+t+2);
	
	for(i=0;i<t+1;i++){
		copyArray16(copyOfA,copy2A,sizeA);
		yi = copyOfB[sizeB-1]%2;
		c = 0;
		
		for(j=0;j<n+1;j++){
			xj = copy2A[sizeA-1]%2;
			tempSum = w[i+j] + xj*yi + c;
			v = tempSum%2;
			u = (tempSum>>1);
			w[i+j] = v;
			c = u;
			divideByTwo(copy2A,sizeA);
		}
		
		w[i+n+1] = u;
		divideByTwo(copyOfB,sizeB);
	}

	if ((n+t+2)%16 == 0)
		sizeResult = (n+t+2)/16;
	else
		sizeResult = (n+t+2)/16+1;
	from2to16(w,result,n+t+2);
	zerosArray(product,sizeProduct);
	for(i=0;i<sizeResult;i++){
		product[sizeProduct-1-i] = result[i];
	}
}

/* Division of two numbers: x/y.
	division <- x/y
	remainder <- x%y
	posMSB_x >= posMSB_y
	size division = size x = sizeX;
	size remainder = size y = sizeY;
*/
void division(uint16_t *x, uint16_t *y, uint16_t *divisionResult, uint16_t *remainder, uint16_t sizeX, uint16_t sizeY){

	uint16_t xPosMSB = positionMSB(x,sizeX);
	uint16_t yPosMSB = positionMSB(y,sizeY);
	uint16_t copyOfX[MAXLENGTH] = {0};
	uint16_t copy2OfX[MAXLENGTH] = {0};
	uint16_t copyOfY[MAXLENGTH] = {0};
	uint16_t n = sizeX*16 - xPosMSB - 1;
	uint16_t t = sizeY*16 - yPosMSB - 1;
	uint16_t q[MAXLENGTH] = {0};
	uint16_t copyOfX3[MAXLENGTH] = {0};
	int k;
	int i;
	int j;		
	uint16_t sizeResult = 0;
	uint16_t result[MAXLENGTH] = {0};
	uint16_t yExt[MAXLENGTH] ={0};
	uint16_t nbOfMults = n-t; 
	uint16_t comparison = 0;
	uint16_t xi = 0;
	uint16_t nextXi = 0;
	uint16_t next2Xi = 0;
	uint16_t yt = 0;
	uint16_t yt1 = 0;
	uint16_t wordMSB = yPosMSB/16;
	uint16_t posInWord = (yPosMSB%16);
	uint16_t wordXMSB = xPosMSB/16;
	uint16_t posXInWord = (xPosMSB%16);
	uint16_t times = 0;
	uint16_t sign = 0;
	uint16_t leftSide = 0;
	uint16_t rightSide = 0;
	uint16_t counterArray[MAXLENGTH] = {0};
	uint16_t sum[MAXLENGTH] = {0};
	
	copyArray16(y,copyOfY,sizeY);
	copyArray16(x,copyOfX3,sizeX);
	copyArray16(x,copyOfX,sizeX);

	/* Step 1 */
	for(j=0;j<n-t+1;j++){
		q[j] = 0;
	}
	
	/* Step 2 */
	zerosArray(yExt,sizeX);
	for(k=0;k<sizeY;k++){
		yExt[k+(sizeX-sizeY)] = y[k];
	}

	for(k=0;k<nbOfMults;k++){
		multiplyByTwo(yExt,sizeX);
	}

	comparison = isBiggerThanOrEqual(copyOfX3,yExt,sizeX);
	while (comparison > 0){
		q[n-t] = q[n-t] + 1;
		subtraction(copyOfX3,yExt,copyOfX3,sizeX);
		comparison = isBiggerThanOrEqual(copyOfX3,yExt,sizeX);
	}

	/* Step 3 */
	yt = (copyOfY[wordMSB]>>(15-posInWord))%2;
	multiplyByTwo(copyOfY,sizeY);
	yt1 = (copyOfY[wordMSB]>>(15-posInWord))%2;

	for(i=n;i>t;i--){
		/* STEP 3.1 */
		copyArray16(copyOfX,copy2OfX,sizeX);
		xi = (copyOfX[wordXMSB]>>(15-posXInWord))%2;		
		multiplyByTwo(copy2OfX,sizeX);
		nextXi = (copy2OfX[wordXMSB]>>(15-posXInWord))%2;
		multiplyByTwo(copy2OfX,sizeX);
		next2Xi = (copy2OfX[wordXMSB]>>(15-posXInWord))%2;
		
		if ( xi == yt ){
			q[i-t-1] = 1;
		}
		else {
			q[i-t-1] = (2*xi + nextXi)/yt;
		}
		
		/* STEP 3.2 */
		leftSide = q[i-t-1]*(yt*2+yt1);
		rightSide = xi*4 + nextXi*2 + next2Xi;
		if (leftSide > rightSide){
			while(leftSide>rightSide){
				q[i-t-1] = q[i-t-1]-1;
				leftSide = q[i-t-1]*(yt*2+yt1);
				rightSide = xi*4 + nextXi*2 + next2Xi;
			}
		}

		/* STEP 3.3 */
				
		zerosArray(yExt,sizeX);
		for(k=0;k<sizeY;k++){
			yExt[k+(sizeX-sizeY)] = y[k];
		}

		if (q[i-t-1] == 1){
			for(times=0;times<i-t-1;times++){
				multiplyByTwo(yExt,sizeX);
			}
			sign = subtractionWithSign(copyOfX3,yExt,copyOfX3,sizeX);
		}

		/* STEP 3.4 */
		if (sign == 1){
			subtraction(yExt,copyOfX3,copyOfX3,sizeX);
			q[i-t-1] = q[i-t-1] - 1;
		}
		multiplyByTwo(copyOfX,sizeX);
		sign = 0;
	}

	zerosArray(yExt,sizeX);
	for(k=0;k<sizeY;k++){
		yExt[k+(sizeX-sizeY)] = y[k];
	}
	
	zerosArray(counterArray,sizeX);
	zerosArray(sum,sizeX);
	sign = 0;
	sign = isBiggerThanOrEqual(copyOfX3,yExt,sizeX);
	while(sign == 1){
		sum[sizeX-1] = 1;
		addition(counterArray,sum,counterArray,sizeX);
		subtraction(copyOfX3,yExt,copyOfX3,sizeX);
		sign = isBiggerThanOrEqual(copyOfX3,yExt,sizeX);
	}

	if ((n-t+1)%16 == 0)
		sizeResult = (n-t+1)/16;
	else
		sizeResult = (n-t+1)/16+1;
	from2to16(q,result,n-t+1);

	zerosArray(divisionResult,sizeX);
	for(i=0;i<sizeResult;i++){
		divisionResult[sizeX-1-i] = result[i];
	}
	addition(divisionResult,counterArray,divisionResult,sizeX);
	zerosArray(remainder,sizeX);
	for(k=0;k<sizeY;k++){
		remainder[k] = copyOfX3[k+(sizeX-sizeY)];
	}
}

/* a*b mod m.
	a = sizeA elements
	b = sizeB elements
	m = sizeM elements
	result = sizeM elements (result<m);
*/
void modMult(uint16_t *a, uint16_t *b, uint16_t *m, uint16_t *result, uint16_t sizeA, uint16_t sizeB, uint16_t sizeM){
	
	uint16_t product[MAXLENGTH] = {0};
	uint16_t divisionResult[MAXLENGTH] = {0};
	uint16_t remainder[MAXLENGTH] = {0};

	zerosArray(product,sizeA+sizeB);
	multiplication(a,b,product,sizeA,sizeB);
	division(product,m,divisionResult,remainder,sizeA+sizeB,sizeM);

	copyArray16(remainder,result,sizeM);

}

void modSquare(uint16_t *a, uint16_t *m, uint16_t *result, uint16_t sizeA, uint16_t sizeM){
	
	uint16_t modA[MAXLENGTH] = {0};
	uint16_t squareResult[MAXLENGTH] = {0};
	uint16_t mExt[MAXLENGTH] = {0};
	int i;
	
	mod(a,m,modA,sizeA,sizeM);
	
	squareProduct(modA,squareResult,sizeM);
	
	zerosArray(mExt,2*sizeM);
	for(i=0;i<sizeM;i++){
		mExt[sizeM+i] = m[i];
	}
	/* while (isBiggerThanOrEqual(squareResult,mExt,2*sizeM) == 1){
		subtraction(squareResult,mExt,squareResult,2*sizeM);
	} */
	mod(squareResult,mExt,squareResult,2*sizeM,2*sizeM);
	for(i=0;i<sizeM;i++){
		result[i] = squareResult[sizeM+i];
	}
}

/*
	x = sizeX elements
	m = sizeM elements
	e = sizeE elements
	result = sizeM elements
*/
void modExp(uint16_t *x, uint16_t *m, uint16_t *e, uint16_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE){
	
	uint16_t posMSB = positionMSB(e,sizeE);
	uint16_t t = sizeE*16 - posMSB - 1;
	uint16_t msbWord = 0;
	uint16_t posWord = 0;
	uint16_t copyOfE[MAXLENGTH] = {0};
	uint16_t xMod[MAXLENGTH] = {0};
	uint16_t begin = 1;
	uint16_t ei = 0;
	int i;
	
	copyArray16(e,copyOfE,sizeE);
	msbWord = posMSB/16;
	posWord = posMSB%16;
	
	mod(x,m,xMod,sizeX,sizeM);
	
	zerosArray(result,sizeM);
	result[sizeM-1] = 0x01;

	/* Left-to-right binary exponentiation */
	begin = 1;
	for(i=t;i>=0;i--){
		modSquare(result,m,result,sizeM,sizeM);
		ei = (copyOfE[msbWord]>>(15-posWord))%2;
		if (ei == 1){
			if (begin == 0)
				/* The program has issues with (1*xMod)% modm */
				modMult(result,xMod,m,result,sizeM,sizeM,sizeM);
			else
				copyArray16(xMod,result,sizeM);
		}
		begin = 0;
		multiplyByTwo(copyOfE,sizeE);
	}
}

#endif