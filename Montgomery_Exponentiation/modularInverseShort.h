
void signedSubtraction(uint16_t *x, uint16_t *y, uint16_t modLength, uint16_t *sign1, uint16_t *sign2){
	if (*sign1 != 1)
	{
		if (*sign2 != 1) {
			*sign1 = subtraction(x,y,x,modLength);
		}
		else {
			addition(x,y,x,modLength);
		}
	}
	else
	{
		if (*sign2 != 1){
			addition(x,y,x,modLength);
			*sign1 = 1;
		} else {
			*sign1 = subtraction(y,x,x,modLength);
		}
	}
}

/* 	x^(-1) mod y
	x = sizeX elements
	y = modLength elements
	a_result = modLength elements
	sizeX <= modLength
	x <= y
*/
uint16_t modularInverseShort(uint16_t *x, uint16_t *y, uint16_t *a_result, uint16_t sizeX, uint16_t modLength){
		
		// Extend x //
		uint16_t xExtended[modLength];
		int i;
		for(i=0;i<modLength;i++){
			if(i<modLength-sizeX)
				xExtended[i] = 0x00;
			else
				xExtended[i] = x[i-(modLength-sizeX)];
		}
		
		// Step 1 //
		uint16_t g = 1;
		
		uint16_t u[modLength];
		uint16_t v[modLength];
		
		// Step 2 //
		if ((xExtended[modLength-1]%2 == 0) && (y[modLength-1]%2 == 0)){
			divideByTwo(xExtended, modLength);
			divideByTwo(y, modLength);
			g = g<<1;
		}
		
		// Step 3 //
		copyArray(xExtended,u,modLength);
		copyArray(y,v,modLength);

		uint16_t zeros[modLength];
		zerosArray(zeros,modLength);
		uint16_t A[modLength];
		copyArray(zeros,A,modLength);
		A[modLength-1]= 0x01;
		uint16_t B[modLength];
		copyArray(zeros,B,modLength);
		uint16_t C[modLength];
		copyArray(zeros,C,modLength);
		uint16_t D[modLength];
		copyArray(zeros,D,modLength);
		D[modLength-1] = 0x01;
		
		uint16_t resultIsZero = 0;
		uint16_t signBInt = 0;
		uint16_t signDInt = 0;
		uint16_t signCInt = 0;
		uint16_t signAInt = 0;
		uint16_t signVInt = 0;
		uint16_t signUInt = 0;
		uint16_t *signB = &signBInt;
		uint16_t *signD = &signDInt;
		uint16_t *signA = &signAInt;
		uint16_t *signC = &signCInt;
		uint16_t *signV = &signVInt;
		uint16_t *signU = &signUInt;

		do {
			// Step 4 //
			while (u[modLength-1]%2 == 0) {
				divideByTwo(u, modLength);
				if ((A[modLength-1]%2 == 0) && (B[modLength-1]%2 == 0)){
						divideByTwo(A, modLength);
						divideByTwo(B, modLength);
				}
				else
				{
					if (signAInt != 1)
						addition(A,y,A,modLength);
					else
						signAInt = subtraction(y,A,A,modLength);
					divideByTwo(A, modLength);
					
					if (signBInt != 1)
						signBInt = subtraction(B,xExtended,B,modLength);
					else
					{
						addition(B,xExtended,B,modLength);
						signBInt = 1;
					}
					divideByTwo(B, modLength);
				}
			}
			
			// Step 5 //
			while (v[modLength-1]%2 == 0) {
				divideByTwo(v, modLength);
				if ((C[modLength-1]%2 == 0) && (D[modLength-1]%2 == 0)){
					divideByTwo(C, modLength);
					divideByTwo(D, modLength);
				}
				else {
					if (signCInt != 1){
						addition(C,y,C ,modLength);
						divideByTwo(C, modLength);
					}
					else {
						signCInt = subtraction(y,C,C,modLength);
						divideByTwo(C, modLength);
					}
					
					if (signDInt != 1)
						signDInt = subtraction(D,xExtended,D,modLength);
					else {
						addition(D,xExtended,D,modLength);
						signDInt = 1;
					}
					divideByTwo(D, modLength);
				}
			}
			
			// Step 6 //
			int resultComparison;
			resultComparison = isBiggerThanOrEqual(u,v,modLength);
			if (resultComparison == 1){
				
				signedSubtraction(u,v,modLength,signU,signV);
			
				signedSubtraction(A,C,modLength,signA,signC);
				
				signedSubtraction(B,D,modLength,signB,signD);
			}
			else {
				
				signedSubtraction(v,u,modLength,signV,signU);
				
				signedSubtraction(C,A,modLength,signC,signA);

				signedSubtraction(D,B,modLength,signD,signB);
			}
		
		//Step 7 //
		resultIsZero = numberIsZero(u, modLength);
		} while (resultIsZero != 1);
		
		copyArray(C,a_result,modLength);
		char namea[2] = "a";
		printArray(a_result,namea,modLength);
		char name[9] = "b_result";
		printArray(D,name,modLength);
		printf("g = %x ",g);
		char nameV[2] = "v";
		printArray(v,nameV,modLength);
		
		printf("signCInt = %u\n",signCInt);
		printf("signC = %u\n",*signC);
		printf("signD  %u\n",*signD);
		return signCInt;
}


uint16_t modularInverse2(uint16_t *x, uint16_t *y, uint16_t *a_result, uint16_t sizeX, uint16_t modLength){
		
		// Extend x //
		uint16_t yExtended[sizeX];
		int i;
		for(i=0;i<sizeX;i++){
			if(i<sizeX-modLength)
				yExtended[i] = 0x00;
			else
				yExtended[i] = y[i-(sizeX-modLength)];
		}
		
		// Step 1 //
		uint16_t g = 1;
		
		uint16_t u[sizeX];
		uint16_t v[sizeX];
		
		// Step 2 //
		if ((x[-1]%2 == 0) && (yExtended[modLength-1]%2 == 0)){
			divideByTwo(x, modLength);
			divideByTwo(yExtended, modLength);
			g = g<<1;
		}
		
		// Step 3 //
		copyArray(x,u,sizeX);
		copyArray(yExtended,v,sizeX);

		uint16_t zeros[sizeX];
		zerosArray(zeros,sizeX);
		uint16_t A[sizeX];
		copyArray(zeros,A,sizeX);
		A[sizeX-1]= 0x01;
		uint16_t B[sizeX];
		copyArray(zeros,B,sizeX);
		uint16_t C[sizeX];
		copyArray(zeros,C,sizeX);
		uint16_t D[sizeX];
		copyArray(zeros,D,sizeX);
		D[sizeX-1] = 0x01;
		
		uint16_t resultIsZero = 0;
		uint16_t signBInt = 0;
		uint16_t signDInt = 0;
		uint16_t signCInt = 0;
		uint16_t signAInt = 0;
		uint16_t signVInt = 0;
		uint16_t signUInt = 0;
		uint16_t *signB = &signBInt;
		uint16_t *signD = &signDInt;
		uint16_t *signA = &signAInt;
		uint16_t *signC = &signCInt;
		uint16_t *signV = &signVInt;
		uint16_t *signU = &signUInt;

		do {
			// Step 4 //
			while (u[sizeX-1]%2 == 0) {
				divideByTwo(u, sizeX);
				if ((A[sizeX-1]%2 == 0) && (B[sizeX-1]%2 == 0)){
						divideByTwo(A, sizeX);
						divideByTwo(B, sizeX);
				}
				else
				{
					if (signAInt != 1)
						addition(A,yExtended,A,sizeX);
					else
						signAInt = subtraction(yExtended,A,A,sizeX);
					divideByTwo(A, sizeX);
					
					if (signBInt != 1)
						signBInt = subtraction(B,x,B,sizeX);
					else
					{
						addition(B,x,B,sizeX);
						signBInt = 1;
					}
					divideByTwo(B, sizeX);
				}
			}
			
			// Step 5 //
			while (v[sizeX-1]%2 == 0) {
				divideByTwo(v, sizeX);
				if ((C[sizeX-1]%2 == 0) && (D[sizeX-1]%2 == 0)){
					divideByTwo(C, sizeX);
					divideByTwo(D, sizeX);
				}
				else {
					if (signCInt != 1){
						addition(C,yExtended,C ,sizeX);
						divideByTwo(C, sizeX);
					}
					else {
						signCInt = subtraction(yExtended,C,C,sizeX);
						divideByTwo(C, sizeX);
					}
					
					if (signDInt != 1)
						signDInt = subtraction(D,x,D,sizeX);
					else {
						addition(D,x,D,sizeX);
						signDInt = 1;
					}
					divideByTwo(D, sizeX);
				}
			}
			
			// Step 6 //
			int resultComparison;
			resultComparison = isBiggerThanOrEqual(u,v,sizeX);
			if (resultComparison == 1){
				
				signedSubtraction(u,v,sizeX,signU,signV);
			
				signedSubtraction(A,C,sizeX,signA,signC);
				
				signedSubtraction(B,D,sizeX,signB,signD);
			}
			else {
				
				signedSubtraction(v,u,sizeX,signV,signU);
				
				signedSubtraction(C,A,sizeX,signC,signA);

				signedSubtraction(D,B,sizeX,signD,signB);
			}
		
		//Step 7 //
		resultIsZero = numberIsZero(u, sizeX);
		} while (resultIsZero != 1);
		
		for (i=0;i<modLength;i++){
			a_result[i] = C[i+(sizeX-modLength)];
		}
		// copyArray(C,a_result,sizeX);
		// char namea[2] = "a";
		// printArray(a_result,namea,modLength);
		// char name[9] = "b_result";
		// printArray(D,name,sizeX);
		// printf("g = %x ",g);
		// char nameV[2] = "v";
		// printArray(v,nameV,sizeX);

		return signCInt;
}