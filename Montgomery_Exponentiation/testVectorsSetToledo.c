#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "additionalFunctions.h"
#include "modularInverse.h"
#include "modFunctions.h"
#include "montExponentiation.h"

int main(void){
		
	uint16_t a[8] = {0x4867, 0x3767, 0x2d60, 0xa503, 0x7fe4, 0xa540, 0xc070, 0x67e7};
	uint16_t b[8] = {0x78f9, 0x4952, 0x2293, 0xabbe, 0xb0c7, 0x2fb9, 0xe566, 0x4c4c};
	uint16_t m[7] = {0x78fa, 0xe4d2, 0x7165, 0x9ded, 0x9b72, 0x10f1, 0x1d56};
	uint16_t s[1] = {0x2b73};
	uint16_t sizeA = 8;
	uint16_t sizeM = 7;
	uint16_t sizeB = 8;
	uint16_t result[8] = {0};
	uint16_t sizeResult = 8;
	uint16_t result9[9] = {0};
	uint16_t sizeResult9 = 9;
	uint16_t result16[16] = {0};
	uint16_t sizeResult16 = 16;
	uint16_t p[9] = {0x6789, 0x2345, 0xdef1, 0x1abc, 0x5432, 0x9876, 0x7890, 0x3456, 0x12};
	uint16_t sizePQ = 9;
	uint16_t q[9] = {0x6789, 0x2345, 0xdef1, 0x1abc, 0x5432, 0x9876, 0x7890, 0x3456, 0x2};
	uint16_t r[8] = {0x6789, 0x2345, 0xdef1, 0x1abc, 0x5432, 0x9876, 0x7890, 0x3456};
	uint16_t sizeR = 8;	
	
	uint16_t div[8] = {0};
	uint16_t rem[7] = {0};

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
			a^(-1) mod b
			g = a/m
			p*q mod r
			p^q mod r with modExp
			a^b mod m with montExp
	*/	
	
	flipArray(a,8);
	printArray16(a,"a",8);
	flipArray(b,8);
	printArray16(b,"b",8);
	flipArray(m,7);
	printArray16(m,"m",7);
	flipArray(p,9);
	flipArray(q,9);
	flipArray(r,8);
	
	addition(a,b,result,sizeA);
	flipArray(result,sizeResult);
	printArray16(result,"a+b",sizeResult);
	
	subtraction(a,b,result,sizeA);
	flipArray(result,sizeResult);
	printArray16(result,"a-b",sizeResult);
	
	mod(a,b,result,sizeA,sizeB);
	flipArray(result,sizeResult);
	printArray16(result,"a mod b",sizeResult);
	printArray16(b,"b",sizeB);
	printArray16(m,"m",sizeM);
	
	mod(b,m,result,sizeB,sizeM);
	flipArray(result,sizeM);
	printArray16(result,"b mod m",sizeM);
	
	multiplication(a,b,result16,sizeA,sizeB);
	flipArray(result16,sizeResult16);
	printArray16(result16,"a*b",sizeResult16);
	
	multiplication(a,s,result9,sizeA,1);
	flipArray(result9,sizeResult9);
	printArray16(result9,"a*s",sizeResult9);
	
	mod(p,q,result9,sizePQ,sizePQ);
	flipArray(result9,sizeResult9);
	printArray16(result9,"p mod q",sizeResult9);
	
	modularInverse(p,q,result9,sizePQ,sizePQ);
	flipArray(result9,sizeResult9);
	printArray16(result9,"p^{-1} mod q",sizeResult9);	
	
	modularInverse(a,b,result,sizeA,sizeB);
	flipArray(result,sizeB);
	printArray16(result,"a^{-1} mod b",sizeB);

	division(a,m,div,rem,sizeA,sizeM);
	flipArray(div,8);
	printArray16(div,"a/m",8);
	flipArray(rem,8);
	printArray16(rem,"a%m",7);
	
	modMult(p,q,r,result,sizePQ,sizePQ,sizeR);
	flipArray(result,sizeR);
	printArray16(result,"p*q mod r",sizeR);
	
 	modExp(p,r,q,result,sizePQ,sizeR,sizePQ);
	flipArray(result,sizeR);
	printArray16(result,"p^q mod r with modExp",sizeR);
	
	montExp(p,r,q,result,sizePQ,sizeR,sizePQ);
	flipArray(result,sizeR);
	printArray16(result,"p^q mod r with montExp",sizeR);

	modExp(a,m,b,result,8,7,8);
	flipArray(result,7);
	printArray16(result,"a^b mod m with modExp",7);
	
	montExp(a,m,b,result,8,7,8);
	flipArray(result,sizeResult);
	printArray16(result,"a^b mod m with montExp",sizeM);

	return 1;
}