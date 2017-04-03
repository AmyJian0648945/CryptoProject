#define MAXLENGTH 128

uint16_t positionMSB(uint16_t *array, uint16_t size);
void from2to16(uint16_t *binaryString, uint16_t *output, uint16_t size);
void mod(uint16_t *a, uint16_t *N, uint16_t *result, uint16_t sizeA, uint16_t sizeModulus);
void squareProduct(uint16_t *a, uint16_t *product, uint16_t size);

/* 
	Turns an array of binaries (binaryString) into an array of 16-bit numbers (output).
	Size is the number of elements in binaryString.
*/
void from2to16(uint16_t *binaryString, uint16_t *output, uint16_t size){
	int k;
	int m;
	uint16_t nbOfHexadecimals = size/16;
	uint16_t remainder = size%16;
	uint16_t tempSum;
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
		// else: continue//
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
	if (comparison > 0){
		while (comparison > 0){
			subtraction(copyOfA,Nextended,copyOfA,sizeA);
			comparison = isBiggerThanOrEqual(copyOfA,Nextended,sizeA);
		}
	}
	for(i=0;i<sizeModulus;i++){
		result[i] = copyOfA[i+(sizeA-sizeModulus)];
	}
}

/*	Calculates a mod N and stores it in result; a has size+1 elements, N has size elements; result has size elements.
*/
void modSquare(uint16_t *a, uint16_t *N, uint16_t *result, uint16_t size)
{
	
	uint16_t NLonger[2*(size+1)];
	int i;
	zerosArray(NLonger,2*(size+1));
	for(i=0;i<size;i++){
		NLonger[i+size+2] = N[i];
	}
	int comparison;
	if (a[0] == 1)
		comparison = 1;	
	else
		comparison = isBiggerThanOrEqual(a,N,size+1);
	if (comparison > 0){
		while (comparison > 0){
			//printf("inside while loop, comparison = %u\n",comparison);
			subtraction(a,N,a,size+1);
			comparison = isBiggerThanOrEqual(a,N,size+1);
		}
	}
	for(i=0;i<size;i++){
		result[i] = a[i+1];
	}
}

/* Multiple-precision squaring
	Calculates the square product of input a 
	uint16_t *a = input array
	uint16_t *product = array in which to save the result
	uint16_t size = length of input array
*/
void squareProduct(uint16_t *a, uint16_t *product, uint16_t size){
	uint16_t posMSB = positionMSB(a,size);
	uint16_t copyOfA[size];
	copyArray16(a,copyOfA,size);
	uint16_t copyj[size];
	uint16_t t = size*16 - posMSB;
	int i;
	int j;
	uint16_t w[2*t];
	zerosArray(w,2*t);
	char namew[2] = "w";
	uint16_t u = 0;
	uint16_t v = 0;
	uint16_t c = 0;
	uint16_t tempsum = 0;
	uint16_t xi = 0;
	uint16_t xj = 0;

	
	for(i=0;i<t;i++){

		copyArray16(copyOfA,copyj,size);

		xi = copyOfA[size-1]%2;

		tempsum = w[2*i] + xi*xi;
		u = (tempsum>>1);
		v = tempsum%2;
		w[2*i] = v;
		c = u;

		
		for(j=i+1;j<t;j++){
			divideByTwo(copyj,size);
			xj = copyj[size-1]%2;
			tempsum = w[i+j] + 2*xj*xi + c;
			u = (tempsum>>1);
			v = tempsum%2;
			w[i+j] = v;
			c = u;
		}
		
		w[i+t] = u;
		divideByTwo(copyOfA,size);
		divideByTwo(copyj,size);
	}
	uint16_t sizeResult;
	if (2*t%16 == 0)
		sizeResult = 2*t/16;
	else
		sizeResult = 2*t/16+1;
	uint16_t result[sizeResult];
	printf("\n");
	from2to16(w,result,2*t);
	flipArray(result,sizeResult);
	char nameResult[8] = "Result";
	printArray16(result,nameResult,sizeResult);
	for(i=0;i<sizeResult;i++){
		product[i] = result[i];
	}
}

/*	Multiple-precision multiplication
	*/
void multiplication(uint16_t *a, uint16_t *b, uint16_t *product, uint16_t sizeA, uint16_t sizeB){
	
	uint16_t sizeProduct = sizeA + sizeB;
	uint16_t AposMSB = positionMSB(a,sizeA);
	uint16_t BposMSB = positionMSB(b,sizeB);
	uint16_t copyOfA[sizeA];
	copyArray16(a,copyOfA,sizeA);
	uint16_t copyOfB[sizeB];
	copyArray16(b,copyOfB,sizeB);
	uint16_t copyjA[sizeA];
	copyArray16(a,copyjA,sizeA);
	uint16_t n = sizeA*16 - AposMSB - 1;
	uint16_t t = sizeB*16 - BposMSB - 1;
	int i;
	int j;
	uint16_t w[n+t+2];
	zerosArray(w,n+t+2);
	uint16_t u = 0;
	uint16_t v = 0;
	uint16_t c = 0;
	uint16_t tempSum = 0;
	uint16_t yi = 0;
	uint16_t xj = 0;
	
	for(i=0;i<t+1;i++){
		copyArray16(copyOfA,copyjA,sizeA);
		yi = copyOfB[sizeB-1]%2;
		c = 0;
		
		for(j=0;j<n+1;j++){
			xj = copyjA[sizeA-1]%2;
			tempSum = w[i+j] + xj*yi + c;
			v = tempSum%2;
			u = (tempSum>>1);
			w[i+j] = v;
			c = u;
			divideByTwo(copyjA,sizeA);
		}
		
		w[i+n+1] = u;
		divideByTwo(copyOfB,sizeB);
	}
	
	uint16_t sizeResult;
	if ((n+t+2)%16 == 0)
		sizeResult = (n+t+2)/16;
	else
		sizeResult = (n+t+2)/16+1;
	uint16_t result[sizeResult];
	from2to16(w,result,n+t+2);
	zerosArray(product,sizeProduct);
	for(i=0;i<sizeResult;i++){
		product[sizeProduct-1-i] = result[i];
	}
}

/* Division of two numbers.
	division <- x/y
	remainder <- x%y
	posMSB_x >= posMSB_y
	size division = size x = sizeX;
	size remainder = size y = sizeY;
*/
void division(uint16_t *x, uint16_t *y, uint16_t *division, uint16_t *remainder, uint16_t sizeX, uint16_t sizeY){

	uint16_t xPosMSB = positionMSB(x,sizeX);
	uint16_t yPosMSB = positionMSB(y,sizeY);
	uint16_t copyOfX[sizeX];
	uint16_t copy2OfX[sizeX];
	uint16_t copyOfY[sizeY];
	copyArray16(y,copyOfY,sizeY);
	uint16_t n = sizeX*16 - xPosMSB - 1;
	uint16_t t = sizeY*16 - yPosMSB - 1;
	// printf("n = %u and t = %u\n",n,t);
	uint16_t q[n-t+1];
	int i;
	int j;
	// Step 1 //
	for(j=0;j<n-t+1;j++){
		q[j] = 0x00;
	}
	
	// Step 2 //
	uint16_t number[sizeX];
	uint16_t copyExtended[sizeX];
	zerosArray(copyExtended,sizeX);
	int k;
	for(k=0;k<sizeY;k++){
		copyExtended[k+(sizeX-sizeY)] = y[k];
	}
	uint16_t nbOfMults = n-t; 
	for(k=0;k<nbOfMults;k++){
		multiplyByTwo(copyExtended,sizeX);
	}
	uint16_t comparison;
	comparison = isBiggerThanOrEqual(x,copyExtended,sizeX);
	if (comparison == 1){
		while (comparison > 0){
			q[n-t] = q[n-t] + 1;
			subtraction(x,copyExtended,x,sizeX);
			multiplyByTwo(copyExtended,sizeX);
			comparison = isBiggerThanOrEqual(x,copyExtended,sizeX);
		}
	}

	// Step 3 //
	copyArray16(x,copyOfX,sizeX);
	uint16_t xi = 0;
	uint16_t nextXi = 0;
	uint16_t next2Xi = 0;
	uint16_t yt = 0;
	uint16_t yt1 = 0;
	uint16_t wordMSB = yPosMSB/16;
	uint16_t posInWord = (yPosMSB%16);
	uint16_t wordXMSB = xPosMSB/16;
	uint16_t posXInWord = (xPosMSB%16);
	yt = (copyOfY[wordMSB]>>(15-posInWord))%2;
	multiplyByTwo(copyOfY,sizeY);
	yt1 = (copyOfY[wordMSB]>>(15-posInWord))%2;
	// printf("yt = %x and yt1 = %x\n",yt,yt1);

	uint16_t times;
	uint16_t sign = 0;

	
	for(i=n;i>t;i--){
				
		// STEP 3.1 //
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
		
		// STEP 3.2 //		
		uint16_t leftSide = q[i-t-1]*(yt*2+yt1);
		uint16_t rightSide = xi*4 + nextXi*2 + next2Xi;
		if (leftSide > rightSide){
			while(leftSide>rightSide){
				q[i-t-1] = q[i-t-1]-1;
				leftSide = q[i-t-1]*(yt*2+yt1);
				rightSide = xi*4 + nextXi*2 + next2Xi;
			}
		}		

		// STEP 3.3 //
				
		zerosArray(copyExtended,sizeX);
		for(k=0;k<sizeY;k++){
		copyExtended[k+(sizeX-sizeY)] = y[k];
		}

		if (q[i-t-1] == 1){
			for(times=0;times<i-t-1;times++){
				multiplyByTwo(copyExtended,sizeX);
			}
			sign = subtractionWithSign(x,copyExtended,x,sizeX);
		}

		zerosArray(copyExtended,sizeX);
		for(k=0;k<sizeY;k++){
		copyExtended[k+(sizeX-sizeY)] = y[k];
		}
		
		// STEP 3.4 //
		if (sign == 1){
			for(times=0;times<i-t-1;times++){
				multiplyByTwo(copyExtended,sizeX);
			}
			subtraction(copyExtended,x,x,sizeX);
			q[i-t-1] = q[i-t-1] - 1;
		}

		multiplyByTwo(copyOfX,sizeX);
	}
	
	zerosArray(copyExtended,sizeX);
	for(k=0;k<sizeY;k++){
		copyExtended[k+(sizeX-sizeY)] = y[k];
	}

	uint16_t counterArray[sizeX];
	zerosArray(counterArray,sizeX);
	uint16_t sum[sizeX];
	zerosArray(sum,sizeX);
	sign = 0;
	while(sign == 0){
		sum[sizeX-1] = 1;
		if (isBiggerThanOrEqual(x,copyExtended,sizeX) != 1)
			sign = 1;
		else {
			addition(counterArray,sum,counterArray,sizeX);
			sign = subtractionWithSign(x,copyExtended,x,sizeX);
		}
	}
	
	uint16_t sizeResult;
	uint16_t result[sizeResult];
	if ((n-t+1)%16 == 0)
		sizeResult = (n-t+1)/16;
	else
		sizeResult = (n-t+1)/16+1;
	from2to16(q,result,n-t+1);
	zerosArray(division,sizeX);
	for(i=0;i<sizeResult;i++){
		division[sizeX-1-i] = result[i];
	}
	addition(division,counterArray,division,sizeX);
	for(k=0;k<sizeY;k++){
		remainder[k] = x[k+(sizeX-sizeY)];
	}
}

/* a*b mod m.
	a = sizeA elements
	b = sizeB elements
	m = sizeM elements
	result = sizeM elements (result<m);
*/
void modMult(uint16_t *a, uint16_t *b, uint16_t *m, uint16_t *result, uint16_t sizeA, uint16_t sizeB, uint16_t sizeM){
	
	uint16_t product[sizeA+sizeB];
	multiplication(a,b,product,sizeA,sizeB);

	uint16_t divisionResult[sizeA+sizeB];
	uint16_t remainder[sizeM];
	division(product,m,divisionResult,remainder,sizeA+sizeB,sizeM);
	copyArray16(remainder,result,sizeM);
}

/*
	x = sizeX elements
	m = sizeM elements
	e = sizeE elements
	result = sizeM elements
	result[sizeM-1] = 0x01;
*/
void modExp(uint16_t *x, uint16_t *m, uint16_t *e, uint16_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE){
	
	// char nameResult[7] = "result";
	// printArray16(result,nameResult,sizeM);
	// char nameE[2] = "e";
	// printArray16(e,nameE,sizeE);
	uint16_t posMSB = positionMSB(e,sizeE);
	uint16_t t = sizeE*16 - posMSB;
	
	uint16_t resultDiv[sizeE];
	uint16_t resultRem[1];
	uint16_t two[1] = { 0x02};
	division(e,two,resultDiv,resultRem,sizeE,1);
	// char nameDiv[10] = "resultDiv";
	// char nameRem[10] = "resultRem";
	// printArray16(resultDiv,nameDiv,sizeE);
	// printArray16(resultRem,nameRem,1);
	
	uint16_t xMod[sizeM];
	mod(x,m,xMod,sizeX,sizeM);
	// char nameXMod[5] = "xMod";
	// printArray16(xMod,nameXMod,sizeM);
	
	uint16_t x2Mod[sizeM];
	modMult(x,x,m,x2Mod,sizeX,sizeX,sizeM);
	// char nameX2Mod[6] = "x2Mod";
	// printArray16(x2Mod,nameX2Mod,sizeM);

	uint16_t zeros[sizeE];
	zerosArray(zeros,sizeE);
	uint16_t one[sizeE];
	zerosArray(one,sizeE);
	one[sizeE-1] = 0x01;
	// char nameOne[4] = "one";
	// printArray16(one,nameOne,sizeE);
	uint16_t begin = 1;

	while ( numberIsZero(resultDiv,sizeE) != 1){
		if (begin == 0){
			modMult(x2Mod,result,m,result,sizeM,sizeM,sizeM);
			subtraction(resultDiv,one,resultDiv,sizeE);
		}
		else {
			begin = 0;
			copyArray16(x2Mod,result,sizeM);
			subtraction(resultDiv,one,resultDiv,sizeE);
		}
	}
	
	if (resultRem[0] == 1)
		modMult(result,xMod,m,result,sizeM,sizeM,sizeM);
	

}