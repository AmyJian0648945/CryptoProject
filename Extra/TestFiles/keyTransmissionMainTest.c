#include<stdint.h>
#include<string.h>
#include<stdio.h>

#include "../includesDefinesMacros.h"
#include "../CPRNG/pseudoRandNumGenerator.h"
#include "../Montgomery_Exponentiation/montExponentiation.h"
#include "../Montgomery_Exponentiation/modFunctions.h"
#include "formatting.h"
#include "keyFunctions.h"

#define base 128
#define exp 30
#define modlength 130

#define seedLength 32
#define baseLength 60
#define modLength 64

int main(void){


	uint8_t g8[base*2] = {0};
 	uint8_t x8[exp*2] = {0};
	uint8_t y8[exp*2] = {0};
	uint8_t M8[modlength*2] = {0};
	uint16_t g[base] = {0};
	uint16_t x[exp] = {0};
	uint16_t y[exp] = {0};
	uint16_t M[modlength] = {0};
	
	uint16_t gx[modlength] = {0};
	uint16_t gy[modlength] = {0};
	uint16_t res1[modlength] = {0};
	uint16_t res2[modlength] = {0};
	
	printf("START\n");

	printf("RNG\n");
	RNG(g8,base*2);
 	RNG(x8,exp*2);
	RNG(y8,exp*2);
	RNG(M8,modlength*2);
	
	while(M8[modlength*2-1]%2 == 0){
		RNG(M8,modlength*2);
	}
	
/* 	printArray8(g8,"g uint8_t",base*2);
	printArray8(x8,"x uint8_t",exp*2);
	printArray8(y8,"y uint8_t",exp*2);
	printArray8(M8,"M uint8_t",modlength*2); */
	
	printf("FORMATTING\n");
	from8to16(g8,g,base);
	from8to16(x8,x,exp);
	from8to16(y8,y,exp);
	from8to16(M8,M,modlength);
	
 	printArray16(x,"x",exp);
	printArray16(y,"y",exp);
	printArray16(g,"g",base);
	printArray16(M,"M",modlength);
	
	/* MODEXP */
/* 	
	printf("EXPONENTIATION PART 1 MODEXP\n");
	modExp(g,M,x,gx,base,modlength,exp);
	modExp(g,M,y,gy,base,modlength,exp);
	
	printArray16(gx,"g^x",modlength);
	printArray16(gy,"g^y",modlength);

	printf("EXPONENTIATION PART 2 MODEXP \n");
	modExp(gx,M,y,res1,modlength,modlength,exp);
	modExp(gy,M,x,res2,modlength,modlength,exp);
	
	printArray16(res1,"(g^x)^y",modlength);
	printArray16(res2,"(g^y)^x",modlength);
	 */
	/* MONTEXP */
	
	printf("EXPONENTIATION PART 1 MONTEXP\n");
	
	montExp(g,M,x,gx,base,modlength,exp);
	montExp(g,M,y,gy,base,modlength,exp);
	
	printArray16(gx,"g^x",modlength);
	printArray16(gy,"g^y",modlength);
	
	printf("EXPONENTIATION PART 2 MONTEXP\n");
	
	montExp(gx,M,y,res1,modlength,modlength,exp);
	montExp(gy,M,x,res2,modlength,modlength,exp);
	
	printArray16(res1,"(g^x)^y",modlength);
	printArray16(res2,"(g^y)^x",modlength);

	
	return 0;
}