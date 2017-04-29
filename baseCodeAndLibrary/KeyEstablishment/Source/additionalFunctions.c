#include "../Header/additionalFunctions.h"

/*	Print input array of size ArrayLength; word is the name for the array.
*/
void printArray16(uint16_t *array, char *word, uint16_t arrayLength){
	int index;
	printf("%s[%u] = { ",word,arrayLength);
	for (index=0;index<arrayLength;index++){
		printf("%x, ", array[index]);
	}
	printf("} \n");
}
/*	Print input array of size ArrayLength; word is the name for the array.
*/
void printArray8(uint8_t *array, char *word, uint16_t arrayLength){
	int index;
	printf("%s[%u] = { ",word,arrayLength);
	for (index=0;index<arrayLength;index++){
		printf("%x, ", array[index]);
	}
	printf("} \n");
}
/*	Make all arrayLength elements of array result equal to zero.
*/
void inline zerosArray(uint16_t *result, uint16_t arrayLength){
	int i;
	for(i=0;i<arrayLength;i++){
		result[i] = 0;
	}
}
/* Returns one if number1 is strictly bigger than number2. Both arrays have size elements.
*/
uint16_t isBiggerThan(uint16_t *number1, uint16_t *number2, uint16_t size){
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
uint16_t isBiggerThanOrEqual(uint16_t *number1, uint16_t *number2, uint16_t size){
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
uint16_t numberIsZero(uint16_t *number, uint16_t numberOfElements){
	int k;
	for (k=0;k<numberOfElements;k++){
		if (number[k] != 0)
			return 0;
	}
	return 1;
}

/*	Copies the arrayLength elements of original into copiedVersion.
*/
void copyArray16(uint16_t *original, uint16_t *copiedVersion, uint16_t arrayLength){
	int i;
	for(i=0;i<arrayLength;i++){
		copiedVersion[i] = original[i];
	}
}
/*	Copies the arrayLength elements of original into copiedVersion.
*/
void copyArray8(uint8_t *original, uint8_t *copiedVersion, uint16_t arrayLength){
	int i;
	for(i=0;i<arrayLength;i++){
		copiedVersion[i] = original[i];
	}
}

/* Switches the order of the (size) elements of array.
*/
void flipArray(uint16_t *input, uint16_t size){
	int i;
	uint16_t stock[MAXLENGTH] = {0};
	for(i=0;i<size;i++){
		stock[i] = input[size-1-i];
	}
	for(i=0;i<size;i++){
		input[i] = stock[i];
	}
}

void divideByTwo(uint16_t *input, uint16_t size){
	uint16_t newValue = 0x00;
	uint16_t carrier = 0x00;
	int k;
	for(k=0;k<size;k++){
		carrier = carrier<<15;
		newValue = input[k]>>1;
		newValue = newValue + carrier;
		if (input[k]%2 == 0)
			carrier = 0;
		else
			carrier = 0x01;
		input[k] = newValue;
	}
}
void multiplyByTwo(uint16_t *input, uint16_t size){
	uint16_t carrier = 0x00;
	uint16_t newValue = 0x00;
	int k;
	for(k=size-1;k>=0;k--){
		newValue = input[k]<<1;
		newValue = newValue + carrier;
		carrier = input[k]>>15;
		input[k] = newValue;
	}
}

/*	Divide the input by 16. The number of elements in the array is equal to size.
*/
void divideBy16(uint16_t *input, uint16_t size){
	divideByTwo(input,size);
	divideByTwo(input,size);
	divideByTwo(input,size);
	divideByTwo(input,size);
 }

void addition(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size){
	uint32_t carrier = 0;
	uint32_t sum = 0;
	int i;
	for(i=size-1;i>=0;i--){
		sum = (uint32_t)number1[i] + (uint32_t)number2[i] + carrier;
		carrier = sum>>16;
		result[i] = (uint16_t)sum;
	}
}

void subtraction(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size){
	uint16_t carrier = 0;
	uint16_t difference = 0;
	int i;
	for(i=size-1;i>=0; i--){
		difference = number1[i]-number2[i]-carrier;
		if (number1[i] >= number2[i]+carrier)
			carrier = 0;
		else
			carrier = 1;
		result[i] = difference;
	}
}

uint16_t subtractionWithSign(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size){
	if (isBiggerThanOrEqual(number1, number2, size) == 1){
		subtraction(number1,number2,result,size);
		return 0;
	}
	else {
		subtraction(number2,number1,result,size);
		return 1;
	}
}

