
#include "../Header/modularInverse32.h"

/* x <- x - y
	x: first number
	y: second number
	arrayLength: number of elements of x and y
	sign1: 1 if x is negative, 0 if x is positive
	sign2: 1 if y is negative, 0 if y is positive
*/
uint16_t signedSubtraction(uint32_t *x, uint32_t *y, uint16_t arrayLength, uint16_t sign1, uint16_t sign2){

	if (sign1 != 1)
	{
		if (sign2 != 1) {
			sign1 = subtractionWithSign(x,y,x,arrayLength);
		}
		else {
			addition(x,y,x,arrayLength);
		}
	}
	else
	{
		if (sign2 != 1){
			addition(x,y,x,arrayLength);
			sign1 = 1;
		} else {
			sign1 = subtractionWithSign(y,x,x,arrayLength);
		}
	}
	return sign1;
}

/* 	x^(-1) mod y
	input:
		x array
		y array
		sizeX value: x = sizeX elements
		sizeY value: y = modulusLength elements
	output:
		inverse array: inverse = modulusLength elements
*/
void modularInverse(uint32_t *x, uint32_t *y, uint32_t *inverse, uint16_t sizeX, uint16_t modulusLength){
		
		/* Extend x */
		uint32_t copyOfX[MEDIUM] = {0};
		uint32_t copyOfY[MEDIUM] = {0};
		uint32_t u[MEDIUM] = {0};
		uint32_t v[MEDIUM] = {0};
		uint32_t A[MEDIUM] = {0};
		uint32_t B[MEDIUM] = {0};
		uint32_t C[MEDIUM] = {0};
		uint32_t D[MEDIUM] = {0};
		uint16_t size = 0;
		uint16_t g = 0;
		int i;
		
		uint16_t resultIsZero = 0;
		uint16_t signB = 0;
		uint16_t signD = 0;
		uint16_t signC = 0;
		uint16_t signA = 0;
		uint16_t signV = 0;
		uint16_t signU = 0;
		
		
		if(sizeX>modulusLength){
			size = sizeX;
		} else {
			size = modulusLength;
		}
		
		/* Copy of x */
		/*
		for(i=0;i<size;i++){
			if(i<size-sizeX){
				copyOfX[i] = 0x00;
			} else {
				copyOfX[i] = x[i-(size-sizeX)];
			}
		}*/
		for(i=0; i<size-sizeX; i++)    copyOfX[i] = 0x00;
		for(i=size-sizeX; i<size; i++) copyOfX[i] = x[i-(size-sizeX)];
		
		
		/* Copy of y */
			/*
		for(i=0;i<size;i++){
			if (i<size-modulusLength){
				copyOfY[i] = 0x00;
			} else {
				copyOfY[i] = y[i-(size-modulusLength)];
			}
		}*/
		for(i=0; i<size-modulusLength; i++)    copyOfY[i] = 0x00;
		for(i=size-modulusLength; i<size; i++) copyOfY[i] = y[i-(size-modulusLength)];
		
		
		/* Step 1 */
		g = 1;
		
		/* Step 2 */
		if ((copyOfX[size-1]%2 == 0) && (copyOfY[size-1]%2 == 0)){
			divideByTwo(copyOfX, size);
			divideByTwo(copyOfY, size);
			g = g<<1;
		}
		
		/* Step 3 */
		copyArray32(copyOfX,u,size);
		copyArray32(copyOfY,v,size);

		zerosArray(A,size);
		A[size-1]= 0x01;
		zerosArray(B,size);
		zerosArray(C,size);
		zerosArray(D,size);
		D[size-1] = 0x01;


		do {
			/* Step 4 */
			while (u[size-1]%2 == 0) {
				divideByTwo(u, size);
				if ((A[size-1]%2 == 0) && (B[size-1]%2 == 0)){
						divideByTwo(A, size);
						divideByTwo(B, size);
				}
				else
				{
					if (signA != 1)
						addition(A,copyOfY,A,size);
					else
						signA = subtractionWithSign(copyOfY,A,A,size);
					divideByTwo(A, size);
					
					if (signB != 1)
						signB = subtractionWithSign(B,copyOfX,B,size);
					else
					{
						addition(B,copyOfX,B,size);
						signB = 1;
					}
					divideByTwo(B, size);
				}
			}
			
			/* Step 5 */
			while (v[size-1]%2 == 0) {
				divideByTwo(v, size);
				if ((C[size-1]%2 == 0) && (D[size-1]%2 == 0)){
					divideByTwo(C, size);
					divideByTwo(D, size);
				}
				else {
					if (signC != 1){
						addition(C,copyOfY,C ,size);
						divideByTwo(C, size);
					}
					else {
						signC = subtractionWithSign(copyOfY,C,C,size);
						divideByTwo(C, size);
					}
					
					if (signD != 1)
						signD = subtractionWithSign(D,copyOfX,D,size);
					else {
						addition(D,copyOfX,D,size);
						signD = 1;
					}
					divideByTwo(D, size);
				}
			}
			
			/* Step 6 */
			if (isBiggerThanOrEqual(u,v,size) == 1){
				
				signU = signedSubtraction(u,v,size,signU,signV);
				signA = signedSubtraction(A,C,size,signA,signC);
				signB = signedSubtraction(B,D,size,signB,signD);
			}
			else {
				
				signV = signedSubtraction(v,u,size,signV,signU);
				signC = signedSubtraction(C,A,size,signC,signA);
				signD = signedSubtraction(D,B,size,signD,signB);
			}
					
		/* Step 7 */
		resultIsZero = numberIsZero(u, size);
		} while (resultIsZero != 1);

		if (signC == 1){
			subtraction(copyOfY,C,C,size);
		}
		
		for(i=0;i<modulusLength;i++){
			inverse[i] = C[i+(size-modulusLength)];
		}
}

