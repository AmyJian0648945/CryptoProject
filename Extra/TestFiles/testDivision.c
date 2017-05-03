#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "additionalFunctions.h"
#include "modularInverse.h"
#include "modFunctions.h"
#include "montExponentiation.h"

int main(void){

	uint16_t t[2] = {0x0238,0x0016};
	/* 	uint16_t t[1] = {0x1601}; */
	/* uint16_t t[5] = {0x0123, 0x0034, 0x0045, 0x3465, 0x0012}; */
	uint16_t u[2] = {0x00,0x0243};
	uint16_t div[2] = {0};
	uint16_t rem[2] = {0};
	division(t,u,div,rem,2,2);
	printArray16(div,"divtu",2);
	printArray16(rem,"remtu",2);
	printArray16(t,"t",2);
	printArray16(u,"u",2);

	return 1;
}