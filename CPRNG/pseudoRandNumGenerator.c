#include<stdlib.h>
#include<stdio.h>



/** To compile:
1. get to the folder
2. gcc -o outputVariable CPRNG.c
	then ./outputVariable
OR
2. gcc -o outputFileName.c CPRNG.c
**/


//void generateCPRNG(uint32_t pseudoRandNum*, )


// Concatenate

// Take a subset 

// SHA256
void sha256(uint32_t output, uint32_t input){}



uint32_t main(){

	// initialise variables
	uint32_t pseudoRandNum[67] = 0; // first bit indicates array length, the rest are 0s
	uint32_t numBitLength = 20; // random: 2~2048
	uint32_t currBitLength = 0;
	uint32_t seed[???] = 0; 	//SAME for g, random for x,y

	// Hash initial seed

	while(currBitLength < numBitLength){
		// Seed = Concatenate the rest + num=(count up from numBitLength * large number)
		// 		else num = rand for x, y

		// Hash the seed

		// Take a subset, add it to pseudoRandNum

		// update currBithLength
	}


	printf("Hello world!\n");
	return 0;
}









