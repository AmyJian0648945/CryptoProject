#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "additionalFunctions.h"
#include "modularInverseShort.h"
#include "montFunctions.h"
#include "montExponentiation.c"

int main(void){
	
	uint16_t a[3] = { 0x00, 0x00, 0x05};
	uint16_t m[3] = { 0x00, 0x00, 0x13};
	uint16_t e[3] = { 0x00, 0x00, 0x02};
	
	int i;
	for(i=5;i>=0;i--){
		printf(" i = %u\n",i);
	}
	
	uint16_t result[3];
	char nameRes[7] = "result";
	zerosArray(result,3);
	
	modularInverseShort(a,m,result,3,3);
	printArray(result,nameRes,3);
	
	montExp(a,m,e,result,3,3,3);
	printArray(result,nameRes,3);
	
	//return 1;
}