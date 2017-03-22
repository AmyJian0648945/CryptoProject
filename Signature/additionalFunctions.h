void copyArray16(uint16_t *original, uint16_t *copiedVersion, uint16_t size){
	int i;
	for(i=0;i<size;i++){
		copiedVersion[i] = original[i];
	}
}

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
