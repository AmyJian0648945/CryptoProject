/* * * * * * * * * * * * * * * * * * * * * * * *
What it does: generates a (pseudo) random number of length 
	PRNlength based on the input seed (of any length)

Variables:
PRNoutput 	- pseudo random number output
RNoutput	- random number ouput
seed 		- the initial seed given to the CPRNG (to make
				it random), type hex
outputLength	
			- specifies output length in bits

* * * * * * * * * * * * * * * * * * * * * * * * */


/*** Define Macros Here ***********************/
//#define SHA2_USE_INTTYPES_H TRUE // uses <inttypes.h>
	    

/*** Include functions ***********************/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"useSHA256.h" // hashes messages


/*** Function Declarations ***********************/
void PRNG(uint8_t*, uint8_t*, uint32_t);
void RNG(uint8_t*, uint8_t*, uint32_t);









// Concatenate
// Take a subset 

void RNG(uint8_t* output, uint8_t* input, uint32_t outputLength){
	SHA256_CTX ctx;  // structure used in SHA256
	size_t lengthOfInput = strlen(input); 
	uint32_t i = 0;
	time_t current_time;

	// Initialise SHA256	
	SHA256_Init(&ctx); 

	// Obtain current time
	current_time = time(NULL);
	printf("current time: %d\n", current_time);


	// Input data into hash function
	SHA256_Update(&ctx, input, lengthOfInput);

	// writes the hashing output onto output variable
	SHA256_Final(output, &ctx); 


}		

void PRNG(uint8_t* output, uint8_t* input, uint32_t outputLength){

	// hash the inputMessage (32 bits), output it in PRNoutput
	simpleHash(output, input);


	strncat(output, input, strlen(input));

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
	uint8_t *seed;
	uint32_t i = 0;

	// Define seed (i.e. the message to be hashed)
	seed = "12345";

	PRNG(pseudoRandNum, seed, 10);
	RNG(pseudoRandNum, seed, 10);

	// Print hashed message
	for(i = 0; i < SHA256_DIGEST_LENGTH+10; i++){
		printf("%02x", pseudoRandNum[i]);
	}
	printf("\n");

	return 0;
}






/** To compile:
1. get to the folder
2. gcc -o outputVariable CPRNG.c
	then ./outputVariable
OR
2. gcc -o outputFileName.c CNG.c
**/




