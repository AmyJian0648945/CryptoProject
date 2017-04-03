#define MAXLENGTH 128

/* x - y
	x: first number
	y: second number
	arrayLength: number of elements of x and y
	sign1: 1 if x is negative, 0 if x is positive
	sign2: 1 if y is negative, 0 if y is positive
*/
uint16_t signedSubtractionInt(uint16_t *x, uint16_t *y, uint16_t arrayLength, uint16_t sign1, uint16_t sign2){
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
	x = sizeX elements
	y = modLength elements
	inverse = modLength elements
*/
uint16_t modularInverse(uint16_t *x, uint16_t *y, uint16_t *inverse, uint16_t sizeX, uint16_t modLength){
		
		// Extend x //
		uint16_t size = 0;
		uint16_t copyOfX[MAXLENGTH] = {0};
		int i;
		uint16_t copyOfY[MAXLENGTH] = {0};
		uint16_t g = 0;
		
		uint16_t u[MAXLENGTH] = {0};
		uint16_t v[MAXLENGTH] = {0};
		
		if(sizeX>modLength)
			size = sizeX;
		else
			size = modLength;
		
		for(i=0;i<size;i++){
			if(i<size-sizeX){
				copyOfX[i] = 0x00;
			} else {
				copyOfX[i] = x[i-(size-sizeX)];
			}
		}
		
		/* Copy of y */
		zerosArray(copyOfY,size);
		for(i=0;i<size;i++){
			if (i<size-modLength){
				copyOfY[i] = 0x00;
			} else {
				copyOfY[i] = y[i-(size-modLength)];
			}
		}
		
		
		// Step 1 //
		g = 1;
		
		// Step 2 //
		if ((copyOfX[size-1]%2 == 0) && (copyOfY[size-1]%2 == 0)){
			divideByTwo(copyOfX, size);
			divideByTwo(copyOfY, size);
			g = g<<1;
		}
		
		// Step 3 //
		copyArray16(copyOfX,u,size);
		copyArray16(copyOfY,v,size);

		uint16_t A[MAXLENGTH] = {0};
		zerosArray(A,size);
		A[size-1]= 0x01;
		uint16_t B[MAXLENGTH] = {0};
		zerosArray(B,size);
		uint16_t C[MAXLENGTH] = {0};
		zerosArray(C,size);
		uint16_t D[MAXLENGTH] = {0};
		zerosArray(D,size);
		D[size-1] = 0x01;
		
		uint16_t resultIsZero = 0;
		uint16_t signB = 0;
		uint16_t signD = 0;
		uint16_t signC = 0;
		uint16_t signA = 0;
		uint16_t signV = 0;
		uint16_t signU = 0;

		do {
			// Step 4 //
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
			
			// Step 5 //
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
			
			// Step 6 //
			int resultComparison;
			resultComparison = isBiggerThanOrEqual(u,v,size);
			if (resultComparison == 1){
				
				signU = signedSubtractionInt(u,v,size,signU,signV);
				signA = signedSubtractionInt(A,C,size,signA,signC);
				signB = signedSubtractionInt(B,D,size,signB,signD);
			}
			else {
				
				signV = signedSubtractionInt(v,u,size,signV,signU);
				signC = signedSubtractionInt(C,A,size,signC,signA);
				signD = signedSubtractionInt(D,B,size,signD,signB);
			}
		
		//Step 7 //
		resultIsZero = numberIsZero(u, size);
		} while (resultIsZero != 1);
		
		
		if (signC == 1){
			subtraction(copyOfY,C,C,size);
		}
		
		for(i=0;i<modLength;i++){
			inverse[i] = C[i+(size-modLength)];
		}
		return signC;
}
