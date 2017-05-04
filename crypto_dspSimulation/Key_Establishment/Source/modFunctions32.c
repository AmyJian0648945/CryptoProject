#include "../Header/modFunctions32.h"

/*
	Turns an array of binaries (binaryString) into an array of 32-bit numbers (output).
	Size is the number of elements in binaryString.
*/
void from2to32(uint16_t *binaryString, uint32_t *output, uint16_t size){
	
	uint16_t nbOfHexadecimals = 0;
	uint32_t remainder = 0;
	uint32_t tempSum = 0;
	int k;
	int m;

	nbOfHexadecimals = size>>5;
	remainder = size%32;
	for(k=0;k<nbOfHexadecimals;k++){
		tempSum = 0;
		for(m=0;m<32;m++){
			tempSum += binaryString[(k<<5)+m]<<m;
		}
		output[k] = tempSum;
	}
	tempSum = 0;
	for(m=0;m<remainder;m++){
		tempSum += binaryString[(nbOfHexadecimals<<5)+m]<<m;
	}
	output[nbOfHexadecimals] = tempSum;
}

/*	
	Calculates the position of the most significant bit in the input array.
	Size is the number of elements in the input array.
	The position is calculated from the left. Function returns 0 if the first digit of the word at index 0
	is the most significant bit. Function returns size*16-1 if the last digit of the word at index size-1
	is the most significant bit.
	If array is zero (number is 0), the value size*16-1 is returned, same as if the number had been equal to 1
	(msb is the last bit). 
*/
uint16_t positionMSB(uint32_t *array, uint16_t size){
	
	uint32_t result = 0;
	int index = 0;
	int lastOne = 0;
	uint16_t word = 0;
	int i;
	
	for(i=0;i<size;i++){
		if (array[i] != 0){
			word = array[i];
			for(index=0;index<32;index++){
				word = array[i]>>index;
				if (word%2 != 0)
					lastOne = index;
			}
			result = (i<<5)+(31-lastOne);
			return result;
		}
		/* else: continue*/
	}
	return (size<<5)-1;
}

/*	a mod N
	Calculates a mod N and stores it in result;
			a has sizeA elements,
			N has sizeModulus elements;
			result has sizeModulus elements.
*/
void mod(uint32_t *a, uint32_t *N, uint32_t *result, uint16_t sizeA, uint16_t sizeModulus){
	
	uint32_t Nextended[MAXLENGTH] = {0};
	uint32_t copyOfA[MAXLENGTH] = {0};
	uint16_t comparison = 0;
	uint16_t size = 0;
	int i;
	
	if (sizeA > sizeModulus)
		size = sizeA;
	else
		size = sizeModulus;
	
	for(i=0;i<sizeModulus;i++){
		Nextended[i+(size-sizeModulus)] = N[i];
	}
	for(i=0;i<sizeA;i++){
		copyOfA[i+(size-sizeA)] = a[i];
	}
	
	comparison = isBiggerThanOrEqual(copyOfA,Nextended,size);
	while (comparison > 0){
		subtraction(copyOfA,Nextended,copyOfA,size);
		comparison = isBiggerThanOrEqual(copyOfA,Nextended,size);
	}
	for(i=0;i<sizeModulus;i++){
		result[i] = copyOfA[i+(size-sizeModulus)];
	}
}

/* Multiple-precision squaring: product = a^2
	Calculates the square product of input a 
	uint16_t *a = input array
	uint16_t *product = array in which to save the result
	uint16_t sizeX = length of input array
*/
void squareProduct(uint32_t *a, uint32_t *product, uint16_t sizeX){
	
	uint32_t copyOfA[MAXLENGTH] = {0};
	uint16_t w[MAXIMUMLENGTH] = {0};
	uint32_t result[MAXLENGTH] = {0};
	uint16_t posMSB = 0;
	uint16_t t = 0;
	uint16_t sizeProduct = 0;
	/*uint16_t u = 0;
	uint16_t v = 0;*/
	uint16_t c = 0;
	uint16_t tempsum = 0;
	uint16_t xi = 0;
	uint16_t xj = 0;
	uint16_t sizeResult = 0;
 	uint16_t countIndex = 0;
	uint16_t wordIndex = 0;
	uint16_t posIndex = 0;
 	uint16_t countIndex2 = 0;
	uint16_t wordIndex2 = 0;
	uint16_t posIndex2 = 0;
	int i;
	int j;
	posMSB = positionMSB(a,sizeX);
	t = (sizeX<<5) - posMSB;
	sizeProduct = sizeX<<1;
	copyArray32(a,copyOfA,sizeX);
	zerosArray16(w,2*t);
	
 	countIndex = sizeX<<5;
	wordIndex = sizeX;
	posIndex = 0;
	
	for(i=0; i<t; i++){
		/* Loop statements for array */
		posIndex -= 1;
		if (countIndex%32 == 0){ wordIndex -= 1; posIndex = 31; } 
		countIndex -= 1;

		xi = (copyOfA[wordIndex] >> ( 31-posIndex))%2;
		tempsum = w[2*i] + xi*xi;

		w[2*i] = tempsum%2;
		c = tempsum>>1;
		
 		countIndex2 = countIndex;
		wordIndex2 = wordIndex;
		posIndex2 = posIndex;

		for(j=i+1; j<t; j++){
			/* Loop statements */
			posIndex2 -= 1;
			if (countIndex2%32 == 0){ wordIndex2 -= 1; posIndex2 = 31; } 
			countIndex2 -= 1;

			xj = (copyOfA[wordIndex2]>>(31-posIndex2))%2;
			tempsum = w[i+j] + 2*xj*xi + c;
			
			w[i+j] = tempsum%2;
			c = (tempsum>>1); 
		}

		w[i+t] = c;
	}

	if (2*t % 32 == 0) sizeResult = t>>4;
	else sizeResult = (t>>4)+1;

	from2to32(w,result,t<<1);
	zerosArray(product,sizeProduct);
	for(i=0;i<sizeResult;i++){
		product[sizeProduct-1-i] = result[i];
	}
}

/*	Multiple-precision multiplication: product = a*b
	*/
/* void multiplication(uint32_t *a, uint32_t *b, uint32_t *product, uint16_t sizeA, uint16_t sizeB){
	
	uint32_t result[MAXLENGTH] = {0};
	uint16_t w[MAXIMUMLENGTH] = {0};
	uint16_t sizeProduct = 0;
	uint16_t AposMSB = 0;
	uint16_t BposMSB = 0;
	uint16_t n = 0;
	uint16_t t = 0;
	uint16_t u = 0;
	uint16_t v = 0;
	uint16_t c = 0;
	uint16_t tempSum = 0;
	uint16_t yi = 0;
	uint16_t xj = 0;
	uint16_t sizeResult = 0;
	uint16_t countIndex = 0;
	uint16_t wordIndex = 0;
	uint16_t posIndex = 0;
	uint16_t countIndex2 = 0;
	uint16_t wordIndex2 = 0;
	uint16_t posIndex2 = 0;
	int i;
	int j;
	
	sizeProduct = sizeA + sizeB;
	AposMSB = positionMSB(a,sizeA);
	BposMSB = positionMSB(b,sizeB);
	n = (sizeA<<5) - AposMSB - 1;
	t = (sizeB<<5) - BposMSB - 1;
	
	zerosArray16(w,n+t+2);
	
	countIndex = sizeB<<5;
	wordIndex = sizeB;
	posIndex = 0;
	
	for(i=0;i<t+1;i++){
		if (countIndex%32 == 0){
			wordIndex -= 1;
			posIndex = 31;
		} else {
			posIndex -= 1;
		}
		countIndex -= 1;
		yi = (b[wordIndex]>>(31-posIndex))%2;
		c = 0;
		
		countIndex2 = sizeA<<5;
		wordIndex2 = sizeA;
		posIndex2 = 0;
		
		for(j=0;j<n+1;j++){
			
			if (countIndex2%32 == 0){
				wordIndex2 -= 1;
				posIndex2 = 31;
			} else {
				posIndex2 -= 1;
			}
			countIndex2 -= 1;
			xj = (a[wordIndex2]>>(31-posIndex2))%2;
			tempSum = w[i+j] + xj*yi + c;
			v = tempSum%2;
			u = (tempSum>>1);
			w[i+j] = v;
			c = u;
		}
		
		w[i+n+1] = u;
	}

	if ((n+t+2)%32 == 0)
		sizeResult = (n+t+2)>>5;
	else
		sizeResult = ((n+t+2)>>5)+1;
	from2to32(w,result,n+t+2);
	zerosArray(product,sizeProduct);
	for(i=0;i<sizeResult;i++){
		product[sizeProduct-1-i] = result[i];
	}
} */

/* a*b mod m.
	a = sizeA elements
	b = sizeB elements
	m = sizeM elements
	result = sizeM elements (result<m);
*/
/* void modMult(uint32_t *a, uint32_t *b, uint32_t *m, uint32_t *result, uint16_t sizeA, uint16_t sizeB, uint16_t sizeM){
	
	uint32_t product[MAXLENGTH] = {0};
	int i;

	zerosArray(product,sizeA+sizeB);
	multiplication(a,b,product,sizeA,sizeB);

	modFaster(product, m, sizeA+sizeB, sizeM);
	for(i=0;i<sizeM;i++){
		result[i] = product[(sizeA+sizeB-sizeM)+i];
	}
} */

/*	a^2 mod m
	input:
		array a
		array m
		array result (to store computed result)
		sizeA = length of array a
		sizeM = length of array m
	output: void; a^2 mod m is stored in result.
		size result = sizeM
*/
void modSquare(uint32_t *a, uint32_t *m, uint32_t *result, uint16_t sizeA, uint16_t sizeM){
	
	uint32_t modA[MAXLENGTH] = {0};
	uint32_t copyOfA[MAXLENGTH] = {0};
	uint32_t squareResult[MAXLENGTH] = {0};
	int i;

	copyArray32(a,copyOfA,sizeA);
	mod(a, m, modA, sizeA, sizeM);
/* 	modFaster(copyOfA,m,sizeA,sizeM);
	for(i=0;i<sizeM;i++){
		modA[i] = copyOfA[(sizeA-sizeM)+i];
	} */
	
	/* zerosArray(squareResult,2*sizeM); */
	squareProduct(modA,squareResult,sizeM);
	
	modFaster(squareResult,m,2*sizeM,sizeM);
	for(i=0;i<sizeM;i++){
		result[i] = squareResult[sizeM+i];
	}

}

/* x mod m
	input:
		x array
		m array
		sizeX	number of elements in array x
		sizeM	number of elements in array m
	output:
		x <- x mod m
*/
void modFaster( uint32_t *x, uint32_t *m, uint16_t sizeX, uint16_t sizeM){
	
	uint32_t mExt[MAXLENGTH] = {0};
	uint32_t copyOfM[MAXLENGTH] = {0};	
	uint16_t xPosMSB = 0;
	uint16_t mPosMSB = 0;
	uint16_t posBackwards = 0;
	uint16_t comparison = 0;
	uint16_t mPosReverse = 0;
	uint16_t variable = 0;
	int i;
	int n;
	
	zerosArray(mExt,sizeX);
	zerosArray(copyOfM,sizeX);
	n = sizeX-sizeM;
	for(i=0; i<sizeM; i++){
		mExt[n+i] = copyOfM[n+i] = m[i];
	}
	
	xPosMSB = positionMSB(x,sizeX);
	mPosMSB = positionMSB(m,sizeM);
	mPosReverse = 32*sizeM - mPosMSB;
	posBackwards = 32*sizeX - xPosMSB - 1;
	variable = posBackwards - mPosReverse + 2;
	
	for(n=0;n<posBackwards-mPosReverse+1;n++){
		multiplyByTwo(mExt,sizeX);
	}
	
	while(variable != 0){
		
		comparison = isBiggerThanOrEqual(x, mExt, sizeX);
		while (comparison == 1){
			subtraction(x, mExt,x, sizeX);
			comparison = isBiggerThanOrEqual(x, mExt, sizeX);
		}
		divideByTwo(mExt,sizeX);
		variable -= 1;
		if (isBiggerThan(copyOfM,mExt,sizeX)){
			variable = 0;
		}
	}
}
