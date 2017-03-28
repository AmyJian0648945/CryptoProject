
void ifElseClauseSub(uint16_t *x, uint16_t *y, uint16_t modLength, uint16_t *reversed1, uint16_t *reversed2){
	if (*reversed1 != 1)
	{
		if (*reversed2 != 1) {
			*reversed1 = subtraction(x,y,x,modLength);
		}
		else {
			addition(x,y,x,modLength);
		}
	}
	else
	{
		if (*reversed2 != 1){
			addition(x,y,x,modLength);
			*reversed1 = 1;
		} else {
			*reversed1 = subtraction(y,x,x,modLength);
		}
	}
}

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
		uint16_t reversedBInt = 0;
		uint16_t reversedDInt = 0;
		uint16_t reversedCInt = 0;
		uint16_t reversedAInt = 0;
		uint16_t reversedVInt = 0;
		uint16_t reversedUInt = 0;
		uint16_t *reversedB = &reversedBInt;
		uint16_t *reversedD = &reversedDInt;
		uint16_t *reversedA = &reversedAInt;
		uint16_t *reversedC = &reversedCInt;
		uint16_t *reversedV = &reversedVInt;
		uint16_t *reversedU = &reversedUInt;

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
					if (reversedAInt != 1)
						addition(A,y,A,modLength);
					else
						reversedAInt = subtraction(y,A,A,modLength);
					divideByTwo(A, modLength);
					
					if (reversedBInt != 1)
						reversedBInt = subtraction(B,xExtended,B,modLength);
					else
					{
						addition(B,xExtended,B,modLength);
						reversedBInt = 1;
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
					if (reversedCInt != 1){
						addition(C,y,C ,modLength);
						divideByTwo(C, modLength);
					}
					else {
						reversedCInt = subtraction(y,C,C,modLength);
						divideByTwo(C, modLength);
					}
					
					if (reversedDInt != 1)
						reversedDInt = subtraction(D,xExtended,D,modLength);
					else {
						addition(D,xExtended,D,modLength);
						reversedDInt = 1;
					}
					divideByTwo(D, modLength);
				}
			}
			
			// Step 6 //
			int resultComparison;
			resultComparison = isBiggerThanOrEqual(u,v,modLength);
			if (resultComparison == 1){
				
				ifElseClauseSub(u,v,modLength,reversedU,reversedV);
			
				ifElseClauseSub(A,C,modLength,reversedA,reversedC);
				
				ifElseClauseSub(B,D,modLength,reversedB,reversedD);
			}
			else {
				
				ifElseClauseSub(v,u,modLength,reversedV,reversedU);
				
				ifElseClauseSub(C,A,modLength,reversedC,reversedA);

				ifElseClauseSub(D,B,modLength,reversedD,reversedB);
			}
		
		//Step 7 //
		resultIsZero = numberIsZero(u, modLength);
		} while (resultIsZero != 1);
		
		copyArray(C,a_result,modLength);
		char name[9] = "b_result";
		printArray(D,name,modLength);
		printf("g = %x ",g);
		char nameV[2] = "v";
		printArray(v,nameV,modLength);
		
		printf("reversedCInt = %u\n",reversedCInt);
		printf("reversedC = %u\n",*reversedC);
		printf("reversedD  %u\n",*reversedD);
		return reversedCInt;
}