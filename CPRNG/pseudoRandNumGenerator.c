#include<stdlib.h>
#include<stdio.h>
#include "sha.h"


/** To compile:
1. get to the folder
2. gcc -o outputVariable CPRNG.c
	then ./outputVariable
OR
2. gcc -o outputFileName.c CPRNG.c
**/



// Concatenate

// Take a subset 

// SHA256
void sha256(uint32_t output, uint32_t input){}


void generateCPRNG(uint32_t* PRNoutput, uint32_t PRNlength, uint32_t seed){
	// Hash initial seed


	PRNoutput[0] = 10;
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
	uint32_t pseudoRandNum[67] = {0}; // first bit indicates array length, the rest are 0s
	uint32_t numBitLength = 20; // random: 2~2048
	uint32_t seed[10] = {0}; 	//SAME for g, random for x,y


	generateCPRNG(pseudoRandNum, 2048, 10);

	printf("num: %d\n", pseudoRandNum[0]);




	
	return 0;
}









