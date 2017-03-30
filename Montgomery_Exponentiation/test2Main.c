#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "additionalFunctions.h"
#include "modularInverseShort.h"
#include "montFunctions.h"
#include "montExponentiation.c"

int main(void){
		
	uint16_t a[8] = {0x4867, 0x3767, 0x2d60, 0xa503, 0x7fe4, 0xa540, 0xc070, 0x67e7};
	flipArray(a,8);
	char nameA[2] = "a";
	printArray(a,nameA,8);
	uint16_t b[8] = {0x78f9, 0x4952, 0x2293, 0xabbe, 0xb0c7, 0x2fb9, 0xe566, 0x4c4c};
	flipArray(b,8);
	char nameB[2] = "b";
	printArray(b,nameB,8);
	uint16_t m[8] = {0x00, 0x78fa, 0xe4d2, 0x7165, 0x9ded, 0x9b72, 0x10f1, 0x1d56};
	flipArray(m,8);
	char nameM[2] = "m";
	printArray(m,nameM,7);
	uint16_t s[1] = {0x2b73};
	uint16_t aInv[8] = {0x778c, 0x6c90, 0xa80c, 0xe431, 0x4674, 0x1b2c, 0x2a4, 0x3e99};
	flipArray(aInv,8);
	char nameAInv[5] = "aInv";
	printArray(aInv,nameAInv,8);
	uint16_t sizeA = 8;
	uint16_t sizeM = 8;
	uint16_t sizeB = 8;
	uint16_t result[8];
	uint16_t sizeResult = 8;
	uint16_t result9[9];
	uint16_t sizeResult9 = 9;
	uint16_t result16[16];
	uint16_t sizeResult16 = 16;
	uint16_t result18[18];
	uint16_t sizeResult18 = 18;
	uint16_t p[9] = {0x6789, 0x2345, 0xdef1, 0x1abc, 0x5432, 0x9876, 0x7890, 0x3456, 0x12};
	flipArray(p,9);
	uint16_t sizePQ = 9;
	uint16_t q[9] = {0x6789, 0x2345, 0xdef1, 0x1abc, 0x5432, 0x9876, 0x7890, 0x3456, 0x2};
	flipArray(q,9);
	uint16_t r[8] = {0x6789, 0x2345, 0xdef1, 0x1abc, 0x5432, 0x9876, 0x7890, 0x3456};
	flipArray(r,8);
	uint16_t sizeR = 8;
	
	char nameSumAB[6] = "sumAB";
	char nameSubAB[6] = "subAB";
	char nameMultAB[7] = "multAB";
	char nameModAB[6] = "modAB";
	char nameMultSA[7] = "multSA";
	char nameDivAM[6] = "divAM";
	char nameModBM[6] = "modBM";
	char nameModPQ[6] = "modPQ";
	char nameInvPQ[6] = "invpq";
	char nameMultPQ[7] = "multPQ";
	char nameExpPQ[6] = "expPQ";
	char nameExpAB[6] = "expab";
	char nameInvAB[6] = "invAB";
	
	addition(a,b,result,sizeA);
	printArray(result,nameSumAB,sizeResult);
	subtraction(a,b,result,sizeA);
	printArray(result,nameSubAB,sizeResult);
	//mod(a,b,result,sizeA,sizeB);
	//printArray(result,nameModAB,sizeResult);
	//mod(b,m,result,sizeB,sizeM);
	//printArray(result,nameModBM,sizeResult);
	multiplication(a,b,result16,sizeA,sizeB);
	printArray(result16,nameMultAB,sizeResult16);
	multiplication(a,s,result9,sizeA,1);
	printArray(result9,nameMultSA,sizeResult9);
	//mod(p,q,result9,sizePQ,sizePQ);
	//printArray(result9,nameModPQ,sizeResult9);
	modularInverseShort(p,q,result9,sizePQ,sizePQ);
	printArray(result9,nameInvPQ,sizeResult9);
	
	// uint16_t PmodR[8];
	// uint16_t QmodR[8];
	// mod(p,r,PmodR,sizePQ,sizeR);
	// mod(q,r,QmodR,sizePQ,sizeR);
	// multiplication(PmodR,QmodR,result16,sizeR,sizeR);
	// mod(result16,r,result,sizeResult16,sizeR);
	// flipArray(result,sizeResult);
	// printArray(result, nameMultPQ, sizeResult);
	
	// modularInverseShort(a,b,result,sizeA,sizeB);
	// printArray(result,nameInvAB,sizeB);
	// montExp(a,m,b,result,8,8,8);
	// printArray(result,nameExpAB,sizeResult);

	uint16_t div[8];
	uint16_t rem[8];
	division(m,a,div,rem,sizeA,sizeM);
	char nameRem[4] = "rem";
	printArray(rem,nameRem,8);
	printArray(div,nameDivAM,8);
	/*
		Tests succeeded:
			h = a mod b
			c = b mod m
			j = a + b
			k = a - b
			i = a * b
			l = s * a
			p mod q
			p^(-1) mod q
	*/
	
}