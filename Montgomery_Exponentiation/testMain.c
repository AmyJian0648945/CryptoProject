#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "additionalFunctions.h"
#include "modularInverseShort.h"
#include "montMultiplication.h"
#include "montFunctions.h"

int main(void){
	
	uint16_t k[3] = { 0x00, 0x02, 0x1234};
	uint16_t l[3] = { 0x00, 0x00, 0x0056};
	uint16_t m[3] = { 0x00, 0x02, 0x1700};
	uint16_t n[3] = { 0x00, 0x01, 0x0342};
	uint16_t e[2] = { 0x00, 0x02};
	uint16_t two[2] = { 0x00, 0x02};
	
	uint16_t product[6];
	char nameProduct[8] = "product";
	// product = k * l - succeeded -
	multiplication(k,l,product,3,3);
	printArray(product,nameProduct,6);
	// addition = k + l - succeeded -
	uint16_t sum[3];
	char nameSum[4] = "sum";
	addition(k,l,sum,3);
	printArray(sum,nameSum,3);
	// subtraction = k - l - succeeded -
	uint16_t sub[3];
	uint16_t sub2[3];
	char nameSub[4] = "sub";
	char nameSub2[5] = "sub2";
	uint16_t sign;
	sign = subtraction(k,l,sub,3);
	subtractionShort(k,l,sub2,3);
	printArray(sub,nameSub,3);
	printArray(sub2,nameSub,3);
	printf("sign = %u\n",sign);
/* 	// division = k / l - succeeded -
	uint16_t div[3];
	uint16_t rem[3];
	char nameDiv[4] = "div";
	char nameRem[4] = "rem";
	division(k,l,div,rem,3,3);
	printArray(div,nameDiv,3);
	printArray(rem,nameRem,3); */

	uint16_t result[3];
	uint16_t resultDoubleLength[6];
	char nameResult[7] = "result";
	char nameResultDouble[19] = "resultDoubleLength";
	// result = k mod n - succeeded;
	//mod(k,n,result,3,3);
	//printArray(result,nameResult,3);
	// result = l mod n - succeeded;
	mod(l,n,result,3,3);
	printArray(result,nameResult,3);
	// result = (k+l)mod n - succeeded -
	mod(sum,n,result,3,3);
	printArray(result,nameResult,3);
	// result = (k-l)mod n - succeeded -
	mod(sub,n,result,3,3);
	printArray(result,nameResult,3);
	// result = (k*l) mod n - succeeded
	mod(product,n,result,6,3);
	printArray(result,nameResult,3);
	// result = (k*l) mod n with modMult - succeeded
	modMult(k,l,n,result,3,3,3);
	printArray(result,nameResult,3);
	
	// result = k^e mod n - succeeded
	zerosArray(result,3);
	result[2]= 0x01;
	modExp(k,n,e,result,3,3,2);
	printArray(result,nameResult,3);
}