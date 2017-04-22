#include<stdint.h>
#include<string.h>
#include<stdio.h>

#include "../includesDefinesMacros.h"
#include "../CPRNG/pseudoRandNumGenerator.h"
#include "../dataTransmission/encryptDecrypt.h"
#include "../Montgomery_Exponentiation/montExponentiation.h"
#include "../Montgomery_Exponentiation/modFunctions.h"
#include "formatting.h"

#define baseLength 60
#define seedLength 32
#define modLength 64
#define expLength 128

int main(void){
	
	uint8_t seedValue[seedLength*2] = {0};
	uint8_t g8[baseLength*2] = {0};
	uint16_t g[baseLength] = {0};
	RNG(seedValue,seedLength*2);
	PRNG(g8,seedValue,baseLength*2,seedLength*2);
	from8to16(g8,g,baseLength*2);
	printArray16(g,"g",baseLength);
	
	return 1;
}