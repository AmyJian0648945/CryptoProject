void divideByTwo(uint16_t *input, uint16_t size){
	uint16_t newCarrier = 0;
	uint16_t oldCarrier = 0;
	int k;
	for(k=0;k<size;k++){
		if (input[k]%2 == 0)
			newCarrier = 0;
		else
			newCarrier = 1;
		uint16_t newValue = input[k]>>1;
		uint16_t oldCarrier = oldCarrier<<15;
		input[k] =  oldCarrier + newValue;
		oldCarrier = newCarrier;
	}
}

void addition(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size){
	uint32_t carrier = 0;
	int i;
	for(i=size-1;i>=0;i--){
		printf("number1[i] = %x\n", number1[i]);
		printf("number2[i] = %x\n", number2[i]);
		printf("carrier = %x\n", carrier);
		uint32_t sum = (uint32_t)number1[i] + (uint32_t)number2[i] + carrier;
		carrier = sum>>16;
		result[i] = (uint16_t)sum;
		printf("result[i] = %x\n", result[i]);
	}
	result[0] = (uint16_t)carrier;
}
void subtraction(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size){
	uint16_t carrier = 0;
	int i;
	for(i=size-1;i>=0; i--){
		uint16_t difference = number1[i]-number2[i]-carrier;
		result[i] = difference;
		if (number1[i] >= number2[i]+carrier)
			carrier = 0;
		else
			carrier = 1;
	}
}
int isBiggerThan(uint16_t *number1, uint16_t *number2, uint16_t size){
	int i;
	for (i=0;i<size;i++){
		if (number1[i] > number2[i])
			return 1;
		else
			return 0;
	}
	return 0;
}
int numberIsZero(uint16_t *number, uint16_t numberOfElements){
	int k;
	for (k=0;k<numberOfElements;k++){
		if (number[k] != 0)
			return 0;
	}
	return 1;
}
/*
void copyArray(uint16_t *original, uint16_t *copiedVersion, uint16_t size){
	int i;
	for(i=0;i<size;i++){
		copiedVersion[i] = original[i];
	}
}*/

void copyArray8(uint8_t *original, uint8_t *copiedVersion, uint8_t size){
	int i;
	for(i=0;i<size;i++){
		copiedVersion[i] = original[i];
	}
}
void printArray(uint16_t *array, char *word, uint16_t arrayLength){
	int index;
	printf(" %s[%u] = { ",word,arrayLength);
	for (index=0;index<arrayLength;index++){
		printf("%x, ", array[index]);
	}
	printf("} \n");
}
void printArray8(uint8_t *array, char *word, uint16_t arrayLength){
	int index;
	printf(" %s[%u] = { ",word,arrayLength);
	for (index=0;index<arrayLength;index++){
		printf("%x, ", array[index]);
	}
	printf("} \n");
}
