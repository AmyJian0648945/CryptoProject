#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../Header/additionalFunctions32.h"
#include "../Header/modularInverse32.h"
#include "../Header/modFunctions32.h"
#include "../Header/montExponentiation32.h"

int main(void){
	
	/* Test 1 */
	uint32_t x[5] = {0x45264014,0xD54960DE,0xE62D7186,0x1EE34005,0xCDB7A16A};
	uint32_t y[5] = {0x76B78EFD,0x12BC9C42,0x2A764F79,0x6182B5D3,0x7FBAB408};
	uint32_t m[5] = {0x998E281A,0xC543B079,0x2CE6387F,0xB2B16F3F,0x37AF2027};
	uint32_t R[33] = {0};
	uint32_t Rinv[5] = {0};
	uint32_t mInv[33] = {0};
	uint16_t mInvLastBit = 0;
	uint32_t result[5] = {0};
	uint32_t testArray[5] = {0,0,0,0x1,0x22222222};
  	uint32_t m2[4] = {0x1D56,0x10F19B72,0x9DED7165,0xE4D278FB};
	uint32_t x2[4] = {0x140F,0xCFAAA648,0x2B1FDB47,0xA3F32302};
	uint32_t y2[4] = {0xC09,0x372C2F40,0x9DC6DEB2,0x988CE22F};
	uint32_t R2[4] = {0};
	uint32_t Rinv2[4] = {0};
	uint32_t mInv2[4] = {0};
	uint16_t mInvLastBit2 = 0;
	uint32_t result2[4] = {0};
  	uint32_t e2[2] = {0x12423,0x52312423};
	uint32_t a[4] = {0x00,0x1000,0x23000024,0x11000000};
	uint32_t b[3] = {0x1000,0x23000024,0x10000000};
	uint32_t res[3] = {0x00,0xffffffff,0x00000001};
	
	flipArray(a,4);
	flipArray(b,3);
	SUB_COND(a,b,3);
	flipArray(a,3);
	printArray32(a,"result",3);
	

	zerosArray(R,33);
	R[0] = 0x0001;

	/* Rinv is correct */
	modularInverse(R,m,Rinv,33,5);
	printArray32(Rinv,"Rinv",5);
	
	/* xyRinv is correct */
	modularInverse(m,R,mInv,5,33);
	mInvLastBit = mInv[33-1]%2;
	/* montMultiplication(y,x,m,result,mInvLastBit,5,33); */
	printf("mont\n");
	mont(x,y,m,mInv,result,5,33);
	printArray32(result,"xyR^{-1}modm",5);
	
	/* /////////////////////////////////////////////// */

	/* Test 2 */
	
	zerosArray(R2,4);
	R2[0] = 0x00010000;
	
	
	/* Rinv is correct */
	modularInverse(R2,m2,Rinv2,4,4);
	printArray32(Rinv2,"Rinv2",4);
	
	/* xyRinv is correct */
	modularInverse(m2,R2,mInv2,4,4);
	mInvLastBit2 = mInv2[3]%2;
	/* montMultiplication(x2,y2,m2,result2,mInvLastBit2,4,4); */
	/* printArray32(result2,"result2",4); */
	
	montExp(x2, m2, e2, result2, 4,4,2);
	printArray32(result2,"x^e mod m with montExp",4);

	
	return 1;
}