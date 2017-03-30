#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "additionalFunctions.h"
#include "modularInverseShort.h"
#include "montFunctions.h"
#include "montExponentiation.c"

int main(void){
	
	/* Test 1 */
	uint16_t x[10] = {0x4526,0x4014,0xD549,0x60DE,0xE62D,0x7186,0x1EE3,0x4005,0xCDB7,0xA16A};
	uint16_t y[10] = {0x76B7,0x8EFD,0x12BC,0x9C42,0x2A76,0x4F79,0x6182,0xB5D3,0x7FBA,0xB408};
	uint16_t m[10] = {0x998E,0x281A,0xC543,0xB079,0x2CE6,0x387F,0xB2B1,0x6F3F,0x37AF,0x2027};
	uint16_t R[65];
	zerosArray(R,65);
	R[0] = 0x0001;
	
	// Rinv is correct
	uint16_t Rinv[10];
	modularInverse2(R,m,Rinv,65,10);
	char nameRes2[5] = "Rinv";
	printArray(Rinv,nameRes2,10);
	
	uint16_t mInv[65];
	char nameR[2] = "R";
	printArray(R,nameR,65);
	modularInverseShort(m,R,mInv,10,65);
	uint16_t mInvLastBit = mInv[65-1]%2;
	uint16_t result[10];
	montMul(y,x,m,result,mInvLastBit,10);
	char nameRes[7] = "result";
	printArray(result,nameRes,10);
	
	///////////////////////////////////////////////
	
	/* Test 2 */
/*  	uint16_t m[7] = {0x1D56,0x10F1,0x9B72,0x9DED,0x7165,0xE4D2,0x78FB};
	uint16_t x[7] = {0x140F,0xCFAA,0xA648,0x2B1F,0xDB47,0xA3F3,0x2302};
	uint16_t y[7] = {0xC09,0x372C,0x2F40,0x9DC6,0xDEB2,0x988C,0xE22F};
	uint16_t R[8];
	zerosArray(R,8);
	R[0] = 0x0001;
	uint16_t e[4] = {0x1,0x2423,0x5231,0x2423};
	
	// Rinv is correct
	uint16_t Rinv[7];
	modularInverse2(R,m,Rinv,8,7);
	char nameRinv[5] = "Rinv";
	printArray(Rinv,nameRinv,7);
	
	// xyRinv is correct
	uint16_t mInv[8];
	modularInverseShort(m,R,mInv,7,8);
	uint16_t mInvLastBit = mInv[7]%2;
	uint16_t result[7];
	montMul(x,y,m,result,mInvLastBit,7);
	char nameRes[7] = "result";
	printArray(result,nameRes,7);
	
	// uint16_t result2[7];
	// montExp(x,m,e,result2,7,7,4);
	// char nameRes2[7] = "xemodm";
	// printArray(result2,nameRes2,7);  */
	
	//////////////////////////////////////////////////////////////////////
	
	// // uint16_t a[3] = { 0x00, 0x00, 0x05};
	// // uint16_t m[3] = { 0x00, 0x00, 0x13};
	// // uint16_t e[3] = { 0x00, 0x00, 0x02};
	// uint16_t a[1] = {0x05};
	// uint16_t m[1] = {0x13};
	// uint16_t e[1] = {0x02};
	// uint16_t test1[5] = { 0x00, 0x00, 0x00, 0x00, 0X1034};
	// uint16_t test2[3] = { 0x00, 0x00, 0x03};

	// // uint16_t result[3];
	// // char nameRes[7] = "result";
	// // zerosArray(result,3);
	// uint16_t result[1];
	// char nameRes[7] = "result";
	// zerosArray(result,1);
	
	// // modularInverseShort(a,m,result,3,3);
	// // printArray(result,nameRes,3);
		
	// modularInverseShort(a,m,result,1,1);
	// printArray(result,nameRes,1);
	
	// // montExp(a,m,e,result,3,3,3);
	// // printArray(result,nameRes,3);
	
	// montExp(a,m,e,result,1,1,1);
	// printArray(result,nameRes,1);
	
	// // uint16_t div[3];
	// // uint16_t rem[3];
	// // char namediv[4] = "div";
	// // char namerem[4] = "rem";
	// // division(test1,test2,div,rem,3,3);
	// // printArray(div,namediv,3);
	// // printArray(rem,namerem,3);
	
	// //return 1;
}