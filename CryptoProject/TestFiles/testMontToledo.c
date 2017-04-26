#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "Montgomery_Exponentiation/additionalFunctions.h"
#include "Montgomery_Exponentiation/modularInverse.h"
#include "Montgomery_Exponentiation/modFunctions.h"
#include "Montgomery_Exponentiation/montExponentiation.h"

int main(void){
	
	/* Test 1 */
	uint16_t x[10] = {0x4526,0x4014,0xD549,0x60DE,0xE62D,0x7186,0x1EE3,0x4005,0xCDB7,0xA16A};
	uint16_t y[10] = {0x76B7,0x8EFD,0x12BC,0x9C42,0x2A76,0x4F79,0x6182,0xB5D3,0x7FBA,0xB408};
	uint16_t m[10] = {0x998E,0x281A,0xC543,0xB079,0x2CE6,0x387F,0xB2B1,0x6F3F,0x37AF,0x2027};
	uint16_t R[65] = {0};
	uint16_t Rinv[10] = {0};
	uint16_t mInv[65] = {0};
	uint16_t mInvLastBit = 0;
	uint16_t result[10] = {0};
  	uint16_t m2[7] = {0x1D56,0x10F1,0x9B72,0x9DED,0x7165,0xE4D2,0x78FB};
	uint16_t x2[7] = {0x140F,0xCFAA,0xA648,0x2B1F,0xDB47,0xA3F3,0x2302};
	uint16_t y2[7] = {0xC09,0x372C,0x2F40,0x9DC6,0xDEB2,0x988C,0xE22F};
	uint16_t R2[8] = {0};
	uint16_t Rinv2[7] = {0};
	uint16_t mInv2[8] = {0};
	uint16_t mInvLastBit2 = 0;
	uint16_t result2[7] = {0};
  	uint16_t e2[4] = {0x1,0x2423,0x5231,0x2423};
	
	zerosArray(R,65);
	R[0] = 0x0001;
	
	/* Rinv is correct */
	modularInverse(R,m,Rinv,65,10);
	printArray16(Rinv,"Rinv",10);
	
	/* xyRinv is correct */
	modularInverse(m,R,mInv,10,65);
	mInvLastBit = mInv[65-1]%2;
	montMultiplication(y,x,m,result,mInvLastBit,10,65);
	printArray16(result,"result",10);
	
	/* /////////////////////////////////////////////// */
	
	/* Test 2 */
	
	zerosArray(R2,8);
	R2[0] = 0x0001;
	
	/* Rinv is correct */
	modularInverse(R2,m2,Rinv2,8,7);
	printArray16(Rinv2,"Rinv2",7);
	
	/* xyRinv is correct */
	modularInverse(m2,R2,mInv2,7,8);
	mInvLastBit2 = mInv2[7]%2;
	montMultiplication(x2,y2,m2,result2,mInvLastBit2,7,8);
	printArray16(result2,"result2",7);
	
	modExp(x2,m2,e2,result2,7,7,4);
	printArray16(result2,"x^emodm with modExp",7);
	modExp2(x2,m2,e2,result2,7,7,4);
	printArray16(result2,"x^emodm with modExp2",7);
	
	montExp(x2, m2, e2, result2, 7,7,4);
	printArray16(result2,"x^e mod m with montExp",7);

	
	return 1;
}