#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "additionalFunctions.h"
#include "modularInverse.h"
#include "modFunctions.h"
#include "montExponentiation.h"

int main(void){
	
	uint16_t a[2] = {0X23BE,0X024};
	uint16_t result[4] = {0};
	uint16_t e[1] = {3};
	uint16_t m[2] = {0x11,0x07};
	uint16_t x[2] = {0x01,0x04};
	uint16_t expResult[3] = {0};
	uint16_t expectedResult[2] = {0xf,0xD142};
	uint16_t expectedResult2[2] = {0x3,0xf16E};
	uint16_t expectedResult3[4] = {0x4FD,0x810E,0x0D70,0x0510};
	uint16_t result8[8] = {0};
	uint16_t b[4] = {0x4FD,0x810E,0x0D70,0x0510};
	uint16_t expectedResult4[2] = {0xC,0xE45D};
	
	squareProduct(a,result,2);
	printArray16(result,"a^2",4);
	printArray16(expectedResult3,"expectedResult",4);
	
	mod(a,m,result,2,2);
	printArray16(result,"amod",2);
	printArray16(expectedResult2,"expectedResult",2);
	
	zerosArray(result,4);
	modSquare(a,m,result,2,2);
	printArray16(result,"a2mod",2);
	printArray16(expectedResult4,"expectedResult",2);
	
	montExp(x,m,e,expResult,2,2,1);
	printArray16(expResult,"exponentiationResult",2);
	printArray16(expectedResult,"expectedResult",2);
	
	multiplication(b,b,result8,4,4);
	printArray16(result8,"b*b",8);
	squareProduct(b,result8,4);
	printArray16(result8,"b^2",8);
	modMult(b,b,m,result,4,4,2);
	printArray16(result,"b*b mod m",2);
	modSquare(b,m,result,4,2);
	printArray16(result,"b^2 mod m",2);
	
	return 1;
}