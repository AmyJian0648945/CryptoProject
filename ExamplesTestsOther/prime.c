#include<stdint.h>
#include<string.h>
#include<stdio.h>

#include "library/pseudoRandNumGenerator.h"
#include "library/encryptDecrypt.h"
#include "Key_Establishment/montExponentiation.h"
#include "Key_Establishment/modFunctions.h"
#include "Key_Establishment/formatting.h"

#define baseLength 60
#define seedLength 32
#define modLength 64
#define expLength 128

int main(void){
	
	// uint8_t seedValue[seedLength*2] = {0};
	// uint8_t g8[baseLength*2] = {0};
	// uint16_t g[baseLength] = {0};
	// RNG(seedValue,seedLength*2);
	// PRNG(g8,seedValue,baseLength*2,seedLength*2);
	// from8to16(g8,g,baseLength*2);
	// printArray16(g,"g",baseLength);
	 0xCF5A,0x4C9E,0xBE8A,0xFBD3,0xB4C6,0x475A,0x2B03,0x361C,0x0108,0xAA51,0x44E6,0x4827,0xAA17,0xA5AD,0xCD09,0x3BCE,0xF88B,0x9A0E,0xAC06,0xE7C3,0xE18A,0x5548,0xD2ED,0xE19D,0x3AD4,0xEB54,0x1AE4,0x73FF,0x3018,0xB4BA,0xC353,0xBFCB
	return 1;
}