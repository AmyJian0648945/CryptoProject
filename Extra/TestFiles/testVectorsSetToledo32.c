#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../Header/additionalFunctions32.h"
#include "../Header/modularInverse32.h"
#include "../Header/modFunctions32.h"
#include "../Header/montExponentiation32.h"

int main(void){
	
	uint32_t a[4] = { 0x67e7c070, 0xa5407fe4, 0xa5032d60, 0x37674867};
	uint32_t b[4] = { 0x4c4ce566, 0x2fb9b0c7, 0xabbe2293, 0x495278f9};
	uint32_t m[4] = { 0x1d56, 0x10f19b72, 0x9ded7165, 0xe4d278fa};
	uint32_t s[1] = { 0x2b73};
	uint32_t p[5] = { 0x12, 0x34567890, 0x98765432, 0x1abcdef1, 0x23456789};
	uint32_t q[5] = { 0x02, 0x34567890, 0x98765432, 0x1abcdef1, 0x23456789};
	uint32_t r[4] = { 0x34567890, 0x98765432, 0x1abcdef1, 0x23456789};

	uint16_t sizeA = 4;
	uint16_t sizeM = 4;
	uint16_t sizeB = 4;
	uint32_t result4[4] = {0};
	uint16_t sizeResult4 = 4;
	uint32_t result5[5] = {0};
	uint16_t sizeResult5 = 5;
	uint32_t result8[8] = {0};
	uint16_t sizeResult8 = 8;
	uint16_t sizePQ = 5;
	uint16_t sizeR = 4;

	addition(a,b,result4,sizeA);
	printArray32(result4,"a+b",sizeResult4);
	
	subtraction(a,b,result4,sizeA);
	printArray32(result4,"a-b",sizeResult4);
	
	mod(a,b,result4,sizeA,sizeB);
	printArray32(result4,"a mod b",sizeResult4);
	printArray32(b,"b",sizeB);
	printArray32(m,"m",sizeM);
	
	mod(b,m,result4,sizeB,sizeM);
	printArray32(result4,"b mod m",sizeM);
	
	multiplication(a,b,result8,sizeA,sizeB);
	printArray32(result8,"a*b",sizeResult8);
	
	multiplication(a,s,result5,sizeA,1);
	printArray32(result5,"a*s",sizeResult5);
	
	mod(p,q,result5,sizePQ,sizePQ);
	printArray32(result5,"p mod q",sizeResult5);
	
	modularInverse(p,q,result5,sizePQ,sizePQ);
	printArray32(result5,"p^{-1} mod q",sizeResult5);	
	
	modularInverse(a,b,result4,sizeA,sizeB);
	printArray32(result4,"a^{-1} mod b",sizeB);
	
	modMult(p,q,r,result4,sizePQ,sizePQ,sizeR);
	printArray32(result4,"p*q mod r",sizeR);
	
	montExp(p,r,q,result4,sizePQ,sizeR,sizePQ);
	printArray32(result4,"p^q mod r",sizeR);
	
	montExp(a,m,b,result4,sizeA,sizeM,sizeB);
	printArray32(result4,"a^b mod m",sizeM);
	
/* 	uint32_t PmodR[8];
	uint32_t QmodR[8];
	mod(p,r,PmodR,sizePQ,sizeR);
	mod(q,r,QmodR,sizePQ,sizeR);
	multiplication(PmodR,QmodR,result32,sizeR,sizeR);
	mod(result32,r,result,sizeResult32,sizeR);
	flipArray(result,sizeResult4);
	printArray32(result, nameMultPQ, sizeResult4);

	montExp(a,m,b,result,8,8,8);
	printArray32(result,nameExpAB,sizeResult4); */

	return 1;
}