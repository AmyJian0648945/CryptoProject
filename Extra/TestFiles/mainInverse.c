#include<stdio.h>
#include<stdint.h>
#include<string.h>

#define modLen 128
#define hashLen 32


#include "additionalFunctions.h"
#include "modularInverse.h"

int main(void){

	uint16_t test[modLen] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x343};
	
	uint16_t testModulus[modLen] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x09};
	
	uint16_t result[modLen] = {0};
	uint16_t expected[3] = {0x12,0xEE86,0x48FB};
	uint16_t test2[3] = {0x0000,0x002,0x1233};
	uint16_t testmod2[3] = {0x0021,0x01,0x860A};
	uint16_t inv[3] = {0};
	uint16_t expected2[1] = {0xD4FB};
	uint16_t result2[3] = {0};	
	uint16_t sign = 0;
	uint16_t testmod23[3] = {0x0021,0x01,0x860A};
	uint16_t test22[3] = {0x0000,0x002,0x1233};
	uint16_t expected3[3] = {0x20,0xFFFF,0x73D7};
	
	
	modularInverse(test, testModulus, result, modLen, modLen);
	printArray16(result, "inverse", modLen);
	printArray16(expected,"expectedInverse",3);
	
	modularInverse(testmod2,test2,inv,3,3);
	printArray16(inv,"inv",3);
	printArray16(expected2,"expectedInv",1);

	sign = signedSubtraction(test2,testmod23,3,0,0);
	printf("sign = %u\n",sign);
	printArray16(test2,"subresult",3);
	printArray16(expected3,"expectedResult",3);
	
	sign = subtractionWithSign(test22,testmod2,result2,3);
	printf("sign= %u\n",sign);
	printArray16(result2,"subwithsign",3);
	printArray16(expected3,"expectedResult",3);
	
	subtraction(testmod2,test22,result2,3);
	printArray16(result2,"result2",3);
	printArray16(expected3,"expectedResult",3);
	
	return 0;
}