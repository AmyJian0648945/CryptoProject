/* * * * * * * * * * * * * * * * * * * * * * * *
What it does: generates a (pseudo) random number of length 
	PRNlength (each element of type uint_8) based on the input 
	seed (of any length)

/// Function Description ///

void PRNG(Pseudo Random Number, input seed, 
		  length of desired pseudo random number in uint8_t); 

	This function uses A5/1 Stream Cipher to create a psuedo 
	random number. The feedback shift register lengths are 
	specified in the macros as "PRNG_STREAM1_LENGTH", and are 
	created using repetitive calls to SHA256, initialised with
	the specified input seed. "PRNG_CMP_LOCATION" is the element
	that will be compared between the different shift registers.

void RNG(Random number output, length of random number in uint8_t); 	
	-> Doesn't require input seed




* * * * * * * * * * * * * * * * * * * * * * * * */

////////// Define Macros Here //////////
#define RNG_Block_Length 	30 		// must be <256/8 = 32!!!
#define RandNumLength 		60		// for testing purposes

#define PRNG_FSR1_LENGTH	64
#define PRNG_FSR2_LENGTH	65
#define PRNG_FSR3_LENGTH	72

#define PRNG_CMP_LOCATION	9		// must be < any of PRNG_FSR_LENGTH

#define PRNG_XOR_LOCATION1	7		// For use in "updateFSR" must be < any of PRNG_FSR_LENGTH
#define PRNG_XOR_LOCATION2	11			
#define PRNG_XOR_LOCATION3	15
#define PRNG_XOR_LOCATION4	23

// Also defined in sha2.h, here for clarification and just-in-case purposes 
#ifndef SHA256_DIGEST_LENGTH	 
#define SHA256_DIGEST_LENGTH	32 	
#endif /* SHA256_DIGEST_LENGTH */

////////// Include Functions //////////
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"useSHA256.h" // hashes messages




////////// Function Declarations //////////

void PRNG(uint8_t*, uint8_t*, uint16_t, uint16_t); 	/*Obtains pseudo random number, based on seed - last element is in BYTES */
void RNG(uint8_t*, uint16_t); 			/* Obtains random number, length in BYTES */

void updateFSR(uint8_t*, uint16_t);
uint8_t compareFSR(uint8_t*, uint8_t*, uint8_t*, uint16_t);



////////// Function Implementation //////////






void RNG(uint8_t* output, uint16_t desiredOutputLength){

	// Initialise Variables
	SHA256_CTX ctx;  	/* structure used in SHA256 */
	static uint8_t seed[32] = {0}; 		/* this will use previous results's hash as the seed */
	uint8_t const randString[SHA256_DIGEST_LENGTH*2] = "8bc73c890d2dd2977128d97ecfcdeb203ca9c27da294454595c61bb1e2684fbb";
		/* This will be used to initialise the hash function at the very beginning - i.e. rand value that is not zero*/
	uint16_t i = 0, j = 0, count = 0;

	// Refresh seed, or define a new one AND hash it
	if(seed[0] == 0) {
		for(i = 0; i < SHA256_DIGEST_LENGTH; i++) seed[i] = randString[i];
		hashWithTime(seed);			
	}
	else hashWithTime(seed);

	// Operation if the desiredOutputLength > RNG_Block_Length 
	count = 0;
	while (desiredOutputLength > RNG_Block_Length){ 
		j = 0;

		// Get new hash
		hashWithTime(seed);
		
		// Copy hash array over to output array
		for(i = count; i < count + RNG_Block_Length; i++){	
			output[i] = seed[j];
			j++;
		}

		// Loop statements
		count += RNG_Block_Length;
		desiredOutputLength -= RNG_Block_Length;
	} 

	// operation when the random values needed < RNG_Block_Length
	hashWithTime(seed);
	j = 0;
	for(i = count; i < count + desiredOutputLength; i++){
		output[i] = seed[j];
		j++;
	}
}		




void updateFSR(uint8_t* output, uint16_t size){
	uint16_t i = 0;
	uint8_t filler = 0;
	filler = output[PRNG_XOR_LOCATION1] ^ output[PRNG_XOR_LOCATION2] ^ output[PRNG_XOR_LOCATION3] ^ output[PRNG_XOR_LOCATION4];

	for(i=0; i<size-1; i++) output[i] = output[i+1];
	output[i] = filler;
}



uint8_t compareFSR(uint8_t* FSR1, uint8_t* FSR2, uint8_t* FSR3, uint16_t ref){

	while(1){
		if( FSR1[ref] == FSR2[ref] 	&& 	FSR1[ref] == FSR3[ref] ) {
			printf("update all: %d %d %d ",FSR1[ref], FSR2[ref], FSR3[ref]);
			updateFSR(FSR1, PRNG_FSR1_LENGTH); 
			updateFSR(FSR2, PRNG_FSR2_LENGTH); 
			updateFSR(FSR3, PRNG_FSR3_LENGTH); 
			
			printf("%d \n",FSR1[ref-1]);
			return FSR1[ref-1];
		}
		else if( FSR1[ref] == FSR2[ref] ){ 

			updateFSR(FSR1, PRNG_FSR1_LENGTH); 
			updateFSR(FSR2, PRNG_FSR2_LENGTH); 
		}
		else if( FSR2[ref] == FSR3[ref] ){ 

			updateFSR(FSR2, PRNG_FSR2_LENGTH); 
			updateFSR(FSR3, PRNG_FSR3_LENGTH); 
		}
		else if( FSR1[ref] == FSR3[ref] ){ 

			updateFSR(FSR1, PRNG_FSR1_LENGTH); 
			updateFSR(FSR3, PRNG_FSR3_LENGTH); 
		}
		else{
			printf("ERROR in pseudoRandNumGenerator.c, compareFSR: Comparison doesn't work. \n");
			return -1;
		}
	}
}


void PRNG(uint8_t* output, uint8_t* seed, uint16_t outputLength, uint16_t lengthOfSeed){
	uint8_t FSR1[PRNG_FSR1_LENGTH] = {0}, FSR2[PRNG_FSR2_LENGTH] = {0}, FSR3[PRNG_FSR3_LENGTH] = {0}; /* FSR = feedback shift registers */ 
	uint8_t flag = 0;
	uint16_t i = 0;
	

	// Generate shift registers
	printf("FSR1///////////////:\n");
	hashOfLength(FSR1, seed, PRNG_FSR1_LENGTH, lengthOfSeed);
	//printArray(FSR1, PRNG_FSR1_LENGTH);

	printf("FSR2///////////////:\n");
	hashOfLength(FSR2, FSR1, PRNG_FSR2_LENGTH, PRNG_FSR1_LENGTH);
	//printArray(FSR2, PRNG_FSR2_LENGTH);

	printf("FSR3///////////////:\n");
	hashOfLength(FSR3, FSR2, PRNG_FSR3_LENGTH, PRNG_FSR2_LENGTH);
	//printArray(FSR3, PRNG_FSR3_LENGTH);

	

	
	

	
	

	
	
/*
	for(i=0; outputLength > 0; i++){
		output[i] = compareFSR(FSR1, FSR2, FSR3, PRNG_CMP_LOCATION);
		//printf("%x ",output[i]);
		outputLength--;
	}
*/
}



int main(){

	// initialise variables
	uint8_t pseudoRandNum[RandNumLength+10] = {0}; // first bit indicates array length, the rest are 0s
	uint8_t seed[36] = "1234567890abcdefghijklmnopqrstuvwxyz";	// message - to initialise some hashings



	printf("PRNG - Initial:\n"); printArray(pseudoRandNum, RandNumLength);

	PRNG(pseudoRandNum, seed, RandNumLength, 36);
	//RNG(pseudoRandNum, RandNumLength);

	//printf("PRNG - After Hashing:\n"); printArray(pseudoRandNum, RandNumLength);

	// Print hashed message
	
	return 0;
}




//uint8_t* timeHash[TIME_DATA_LENGTH];
//simpleHash(timeHash, tv.tv_usec);
//seed = "8bc73c890d2dd2977128d97ecfcdeb203ca9c27da294454595c61bb1e2684fbb";


/** To compile:
1. get to the folder
2. gcc -o outputVariable CPRNG.c
	then ./outputVariable
OR
2. gcc -o outputFileName.c CNG.c
**/


/*

		switch(compareFSR(FSR1, FSR2, FSR3, PRNG_CMP_LOCATION)) {
	   		case 12: 	
	      		break; 
	   		case 23: 	
	      		break; 
	      	case 13: 	
	      		break;
	      	case 123: 	
	      		break;
	   		default :	
	   			printf("ERROR in pseudoRandNumGenerator.c, PRNG: Switch statement doesn't work. \n");
	   			break;
		}

*/



