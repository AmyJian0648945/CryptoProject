#include<stdint.h>
#include<string.h>
#include<stdio.h>

#include "../includesDefinesMacros.h"
#include "../CPRNG/pseudoRandNumGenerator.h"
#include "../Montgomery_Exponentiation/montExponentiation.h"
#include "../Montgomery_Exponentiation/modFunctions.h"
#include "formatting.h"

#define base 12
#define exp 10
#define modlength 16

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
	
/*  	printArray16(x,"x",exp);
	printArray16(y,"y",exp);
	printArray16(g,"g",base);
	printArray16(M,"M",modlength); */
	
	/* MODEXP */
	
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
	
/*   	uint16_t a[2] = {0x0402, 0x0001};
	uint16_t m[3] = {0x0001, 0x0650, 0x0001};
	uint16_t e[1] = {0x0002};
	uint16_t q[1] = {0x0003};
	uint16_t p[1] = {0x0006};
	uint16_t d[3] = {0};
	uint16_t res[3] = {0x0000, 0x0000,0x0000};
	uint16_t res1[3] = {0};
	uint16_t res2[3] = {0};
	uint16_t res3[3] = {0};
	
	// montExp(a,m,e,res,2,3,2);
	// printArray16(res,"a^e mod m",3);
	modularInverse(e,m,d,1,3);
	montExp(a,m,e,res,2,3,1);
	montExp(res,m,q,res,3,3,1);
	printArray16(res,"(a^e)^(q) mod m MODEXP",3);
	montExp(a,m,p,res,2,3,1);
	printArray16(res,"a^p mod m",3);
	
	modExp(a,m,e,res1,2,3,2);
	modExp(res1,m,d,res2,3,3,3);
	printArray16(res2,"(a^e)^(d) mod m",3);
	mod(a,m,res3,2,3);
	printArray16(res3,"a mod m",3); */
	
	return 0;
}