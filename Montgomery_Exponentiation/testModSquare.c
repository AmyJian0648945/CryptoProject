#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include "additionalFunctions.h"
#include "modularInverse.h"
#include "modFunctions.h"

int main(void){
	
	uint16_t a[2] = {0x00, 0x0365};
	uint16_t n[1] = {0x0437};
	uint16_t b[3] = {0x0234, 0x5678, 0x2323};
	uint16_t r[3] = {0x4356, 0x7586, 0x4321};
	uint16_t result[1] = {0};
	printArray16(a,"a",2);
	printArray16(n,"n",1);
	modSquare(a,n,result,2,1);
	printArray16(result,"result",1);
	uint16_t res[3] = {0};
	printArray16(b,"b",3);
	printArray16(r,"r",3);
	modSquare(b,r,res);
	printArray16(res,"res",3);
	
	return 1;
}