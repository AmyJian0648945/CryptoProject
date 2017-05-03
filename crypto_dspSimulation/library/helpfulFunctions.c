#include "helpfulFunctions.h"




void concat(uint8_t* base, uint8_t* arrayToAppend, uint16_t baseLength, uint16_t lengthToAppend){
    uint16_t i = 0, j = 0;

    for(i=baseLength; i<baseLength + lengthToAppend; i++){
        base[i] = arrayToAppend[j];
        j++;
    }
}

void XOR(uint8_t* output, uint8_t* input1, uint8_t* input2, uint16_t lengthToXOR){
    uint16_t i = 0;
    for(i=0; i<lengthToXOR; i++) { 
        output[i] = input1[i] ^ input2[i];
    }
}

uint16_t timeData(){
    time_t timer;
    return time(&timer);
}


void hexToString(uint8_t* output, uint8_t* input, size_t lengthOfInput){ /* let the default hashing style of hex be of capital letters*/
    uint16_t i = 0, j = 0;

    /* Clear the output first */
    for(i=0; i<lengthOfInput*2; i++) output[i] = 0;
    
    /* Separate the first and second digit of each array element */
    for(i = 0; i < lengthOfInput; i++){
        output[j] = input[i] / 16;
        output[j+1] = input[i] % 16;
        j+=2;
    }

    /* convert each array element into output */
    for(i = 0; i < lengthOfInput*2; i++){
        output[i] = output[i] + 48;
        if(output[i] > 57) output[i] += 7;
    }
}

void copyArray(uint8_t* output, uint8_t* input, uint16_t startingIndex, uint16_t lengthToCopy){
    uint16_t i = 0;

    for(i = 0; i < lengthToCopy; i++) {
        output[startingIndex + i] = input[i];
    }
}


void copyArrayFrom0(uint8_t* output, uint8_t* input, uint16_t lengthToCopy){
    uint16_t i = 0;

    for(i = 0; i < lengthToCopy; i++) {
        output[i] = input[i];
    }
}




void printArray(uint8_t* output, uint16_t iter){
    uint16_t i = 0;
    printf("\n");
    for(i = 0; i < iter; i++) {
        printf("%02x\t", output[i]);

        if(i%5 == 4)    printf("\n");
        if(i%25 == 24)  printf("\n");
    }
    if(i%25 != 24) printf("\n");
    printf("\n");
}


void printArrayNoSpaces(uint8_t* output, uint16_t iter){
    uint16_t i = 0;
    printf("\n");
    for(i = 0; i < iter; i++) {
        printf("%02x", output[i]);
    }
    printf("\n");
}

void printChar(uint8_t* output, uint16_t iter){
    uint16_t i = 0;
    printf("\n");
    for(i = 0; i < iter; i++) {
        printf("%c\t", output[i]);

        if(i%5 == 4)    printf("\n");
        if(i%25 == 24)  printf("\n");
    }
    if(i%25 != 24) printf("\n");
    printf("\n");
}

void printCharNoSpaces(uint8_t* output, uint16_t iter){
    uint16_t i = 0;
    printf("\n");
    for(i = 0; i < iter; i++) {
        printf("%c", output[i]);
    }
    printf("\n");
}





void seeTheDifference(uint8_t* input1, uint8_t* input2, uint16_t lengthToCompare){
    uint16_t i = 0;
    for(i = 0; i < lengthToCompare; i++){
        if(input1[i] - input2[i] != 0) {
            printf("--> HMAC is not the same: @ element = %d\n",i);
            abort();
        }
    }
    if(i == lengthToCompare) printf(">> HMAC is the same - data integrity verified.\n");
}





