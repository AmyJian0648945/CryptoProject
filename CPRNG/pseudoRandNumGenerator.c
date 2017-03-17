/* * * * * * * * * * * * * * * * * * * * * * * *
What it does: generates a (pseudo) random number of length 
	PRNlength (each element of type uint_8) based on the input 
	seed (of any length)

/// Function Description ///
void printArray(message To Be Printed, length Of Message In uint8_t);	
void PRNG(Pseudo Random Number, input seed, length of desired pseudo random number in uint8_t); 	
void RNG(Random number output, length of random number in uint8_t); 	
	-> Doesn't require input seed




* * * * * * * * * * * * * * * * * * * * * * * * */

////////// Define Macros Here //////////
#define RNG_Block_Length 	30 		// must be <256/8 = 32!!!
#define RandNumLength 		60		// for testing purposes



////////// Include Functions //////////
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"useSHA256.h" // hashes messages




////////// Function Declarations //////////

void PRNG(uint8_t*, uint8_t*, uint32_t); 	/*Obtains pseudo random number, based on seed - last element is in BYTES */
void RNG(uint8_t*, uint32_t); 			/* Obtains random number, length in BYTES */


void printArray(uint8_t*, uint32_t);	/* prints the array */
void updateQueue(uint8_t*);



////////// Function Implementation //////////


void printArray(uint8_t* output, uint32_t iter){
	uint32_t i=0;

	for(i=0; i<iter; i++) printf("%x", output[i]);
	printf("\n\n");
}



void RNG(uint8_t* output, uint32_t desiredOutputLength){

	// Initialise Variables
	SHA256_CTX ctx;  	/* structure used in SHA256 */
	static uint8_t seed[32] = {0}; 		/* this will use previous results's hash as the seed */
	uint8_t const randString[32] = "8bc73c890d2dd2977128d97ecfcdeb203ca9c27da294454595c61bb1e2684fbb";
		/* This will be used to initialise the hash function at the very beginning - i.e. rand value that is not zero*/
	uint32_t i = 0, j = 0, count = 0;


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

void PRNG(uint8_t* output, uint8_t* seed, uint32_t outputLength){

	// initiliase the streams with seed


}



int main(){

	// initialise variables
	uint8_t pseudoRandNum[RandNumLength] = {0}; // first bit indicates array length, the rest are 0s
	uint16_t numBitLength = 20; // random: 2~2048
	uint8_t seed[36] = "1234567890abcdefghijklmnopqrstuvwxyz";	// message - to initialise some hashings
	uint32_t i = 0;


	

	PRNG(pseudoRandNum, seed, 10);
	//RNG(pseudoRandNum, 60);

	

	// Print hashed message
	printf("The random number: \n");
	for(i = 0; i < RandNumLength+1; i++){
		printf("%02x", pseudoRandNum[i]);
	}
	printf("\n");
	
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




