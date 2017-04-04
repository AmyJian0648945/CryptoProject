#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "Montgomery_Exponentiation/additionalFunctions.h"
#include "Montgomery_Exponentiation/modularInverse.h"
#include "Montgomery_Exponentiation/modFunctions.h"
#include "Montgomery_Exponentiation/montExponentiation.h"

int main(void){
	
	uint16_t k[3] = { 0x00, 0x02, 0x1234};
	uint16_t l[3] = { 0x00, 0x00, 0x0056};
	uint16_t n[3] = { 0x00, 0x01, 0x0342};
	uint16_t e[2] = { 0x00, 0x0a};
	
	uint16_t product[6] = {0};
	uint16_t sum[3] = {0};
	uint16_t sub[3] = {0};
	uint16_t sub2[3] = {0};
	uint16_t sign = 0;
	uint16_t div[3] = {0};
	uint16_t rem[3] = {0};
	uint16_t result[3] = {0};
	
	/* product = k * l - succeeded - */
	multiplication(k,l,product,3,3);
	printArray16(product,"k*l",6);
	
	/* addition = k + l - succeeded - */
	addition(k,l,sum,3);
	printArray16(sum,"k+l",3);
	
	/* subtraction = k - l - succeeded - */
	sign = subtractionWithSign(k,l,sub,3);
	subtraction(k,l,sub2,3);
	printArray16(sub,"sub",3);
	printArray16(sub2,"sub2",3);
	printf("sign = %u\n",sign);

	/* division = k / l - succeeded - */
	division(k,l,div,rem,3,3);
	printArray16(div,"k/l",3);
	printArray16(rem,"k%l",3);

	/* result = k mod n - succeeded; */
	mod(k,n,result,3,3);
	printArray16(result,"k mod n",3);
	/* result = l mod n - succeeded; */
	mod(l,n,result,3,3);
	printArray16(result,"l mod n",3);
	/* result = (k+l)mod n - succeeded - */
	mod(sum,n,result,3,3);
	printArray16(result,"(k+l) mod n",3);
	/* result = (k-l)mod n - succeeded - */
	mod(sub,n,result,3,3);
	printArray16(result,"(k-l) mod n",3);
	/* result = (k*l) mod n - succeeded */
	mod(product,n,result,6,3);
	printArray16(result,"(k*l) mod n",3);
	/* result = (k*l) mod n with modMult - succeeded */
	modMult(k,l,n,result,3,3,3);
	printArray16(result,"(k*l) mod n",3);
	
	/* result = k^e mod n - succeeded */
	zerosArray(result,3);
	modExp(k,n,e,result,3,3,2);
	printArray16(result,"k^e mod n",3);
	
	return 1;
}