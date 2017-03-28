/*	Print input array of size ArrayLength; word is the name for the array.
*/
void printArray(uint16_t *array, char *word, uint16_t arrayLength){
	int index;
	printf(" %s[%u] = { ",word,arrayLength);
	for (index=0;index<arrayLength;index++){
		printf("%x, ", array[index]);
	}
	printf("} \n");
}
/*	Make all arrayLength elements of array result equal to zero.
*/
void zerosArray(uint16_t *result, uint16_t arrayLength){
	int i;
	for(i=0;i<arrayLength;i++){
		result[i] = 0;
	}
}
/* Returns one if number1 is strictly bigger than number2. Both arrays have size elements.
*/
int isBiggerThan(uint16_t *number1, uint16_t *number2, uint16_t size){
	int i;
	for (i=0;i<size;i++){
		if (number1[i] > number2[i])
			return 1;
		else if (number2[i] > number1[i])
			return 0;
	}
	return 0;
}
/*	Returns one if number1 is bigger than or equal to number2. Both arrays have size elements.
*/
int isBiggerThanOrEqual(uint16_t *number1, uint16_t *number2, uint16_t size){
	int i;
	for (i=0;i<size;i++){
		if (number1[i] > number2[i])
			return 1;
		else if (number2[i] > number1[i])
			return 0;
	}
	return 1;
}
/*	Returns 1 if number is equal to 0.
*/
int numberIsZero(uint16_t *number, uint16_t numberOfElements){
	int k;
	for (k=0;k<numberOfElements;k++){
		if (number[k] != 0)
			return 0;
	}
	return 1;
}

/*	Copies the arrayLength elements of original into copiedVersion.
*/
void copyArray(uint16_t *original, uint16_t *copiedVersion, uint16_t arrayLength){
	int i;
	for(i=0;i<arrayLength;i++){
		copiedVersion[i] = original[i];
	}
}

/* Switches the order of the (size) elements of array.
*/
void flipArray(uint16_t *array, uint16_t size){
	int i;
	uint16_t stock[size];
	for(i=0;i<size;i++){
		stock[i] = array[size-1-i];
	}
	for(i=0;i<size;i++){
		array[i] = stock[i];
	}
}

void divideByTwo(uint16_t *input, uint16_t size){
	uint16_t newCarrier = 0x00;
	uint16_t oldCarrier = 0x00;
	int k;
	for(k=0;k<size;k++){
		if (input[k]%2 == 0)
			newCarrier = 0;
		else
			newCarrier = 0x01;
		uint16_t newValue = input[k]>>1;
		oldCarrier = oldCarrier<<15;
		input[k] =  oldCarrier + newValue;
		oldCarrier = newCarrier;
	}
}
void multiplyByTwo(uint16_t *input, uint16_t size){
	uint16_t newCarrier = 0x00;
	uint16_t oldCarrier = 0x00;
	int k;
	for(k=size-1;k>=0;k--){
		newCarrier = input[k]>>15;
		uint16_t newValue = input[k]<<1;
		input[k] =  oldCarrier + newValue;
		oldCarrier = newCarrier;
	}
}

/*	Divide the input by 16. The number of elements in the array is equal to size.
*/
void divideBy16(uint16_t *input, uint16_t size){
	int k;
	for(k=0;k<4;k++){
		divideByTwo(input,size);
	}
}

void addition(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size){
	uint32_t carrier = 0;
	int i;
	for(i=size-1;i>=0;i--){
		uint32_t sum = (uint32_t)number1[i] + (uint32_t)number2[i] + carrier;
		carrier = sum>>16;
		result[i] = (uint16_t)sum;
	}
}

void subtractionShort(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size){
	uint16_t carrier = 0;
	int i;
	for(i=size-1;i>=0; i--){
		uint16_t difference = number1[i]-number2[i]-carrier;
		if (number1[i] >= number2[i]+carrier)
			carrier = 0;
		else
			carrier = 1;
		result[i] = difference;
	}
}

uint16_t subtraction(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size){
	uint16_t carrier = 0;
	uint16_t resultComparison;
	resultComparison = isBiggerThan(number2, number1, size);
	if (resultComparison == 1){
		int i;
		for(i=size-1;i>=0; i--){
			uint16_t difference = number2[i]-number1[i]-carrier;
			if (number2[i] >= number1[i]+carrier)
				carrier = 0;
			else
				carrier = 1;
			result[i] = difference;
		}
		return 1;
	}
	else {
		int i;
		for(i=size-1;i>=0; i--){
			uint16_t difference = number1[i]-number2[i]-carrier;
			if (number1[i] >= number2[i]+carrier)
				carrier = 0;
			else
				carrier = 1;
			result[i] = difference;
		}
		return 0;
	}
}