/*** Define Macros Here ***********************/

//#define SHA2_USE_INTTYPES_H TRUE // uses <inttypes.h>
	    


/*** Include functions ***********************/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"sha2.h"
#include"useSHA256.h"
#include"sha2.c"
//#include"test.h"

// Concatenate
// Take a subset 





/*** generateCPRNG ***********************
What it does: generates a pseudo random number of length 
	PRNlength based on the input seed (of any length)

Variables:
PRNoutput 	- the pseudo random number output, of size 
				'PRNlength' bits, type hex
seed 		- the initial seed given to the CPRNG (to make
				it random), type hex
PRNlength	- specifies output length in bits
*********************/


void PRNG(uint8_t* PRNoutput, uint8_t* input, uint32_t PRNlength){
	// hash the inputMessage (32 bits), output it in PRNoutput
	hash(PRNoutput, input);


	////////// Steps to implement:
	// XOR seed with time
	// Hash the XOR-ed values

	//PRNoutput[0] = 13;
	//uint32_t inputMessage[10] = {0};
	//inputMessage[0] = 22;


	/*
	while(currBitLength < numBitLength){
		// Seed = Concatenate the rest + num=(count up from numBitLength * large number)
		// 		else num = rand for x, y
		// Hash the seed
		// Take a subset, add it to pseudoRandNum
		// update currBithLength
	}
	*/
}



int main(){

	// initialise variables
	uint8_t pseudoRandNum[256] = {0}; // first bit indicates array length, the rest are 0s
	uint16_t numBitLength = 20; // random: 2~2048
	uint8_t seed[256] = "abcef12345"; 	// SAME for g, random for x,y
	uint32_t i = 0;


	PRNG(pseudoRandNum, seed, 10);

	printf("\n\nSeed: %s\nHashed message: %s\n\n",seed,pseudoRandNum[0]);
	
	for(i=0; i<numBitLength; i++){
		printf("%d\t", pseudoRandNum[i]);
		if(i%6 == 5) printf("\n");
	}


	
	return 0;
}






/** To compile:
1. get to the folder
2. gcc -o outputVariable CPRNG.c
	then ./outputVariable
OR
2. gcc -o outputFileName.c CNG.c
**/




