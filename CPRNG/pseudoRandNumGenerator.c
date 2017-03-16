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

////////// Define Macros Here //////////
//#define SHA2_USE_INTTYPES_H TRUE // uses <inttypes.h>
#define RNG_Block_Length 50
#define RandNumLength 60


////////// Include Functions //////////
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"useSHA256.h" // hashes messages





////////// Function Declarations //////////
void PRNG(uint8_t*, uint8_t*, uint32_t); 	// Obtains pseudo random number, based on seed
void RNG(uint8_t*, uint32_t); 			// Obtains random number
void printArray(uint8_t*, uint32_t);	// prints the array





////////// Function Implementation //////////

void printArray(uint8_t* output, uint32_t iter){
	uint32_t i=0;

	for(i=0; i<iter; i++)printf("%02x", output[i]);
	printf("\n");
}


void RNG(uint8_t* output, uint32_t desiredOutputLength){

	// Initialise Variables
	SHA256_CTX ctx;  /* structure used in SHA256 */
	static uint8_t seed[257] = {0}; /* this will use previous results's hash as the seed */
	uint8_t const randString[257] = "8bc73c890d2dd2977128d97ecfcdeb203ca9c27da294454595c61bb1e2684fbb";
		/* This will be used to initialise the hash function at the very beginning - i.e. rand value that is not zero*/
	uint32_t i = 0, j = 0, count = 0;


	// generate a new seed
	if(seed[0] == 0) {
		for(i = 0; i < SHA256_DIGEST_LENGTH; i++) seed[i] = randString[i];
		hashWithTime(seed);			
	}
	else hashWithTime(seed);

	printf("begin:\n");
	printArray(output, )



	count = 0;
	// if the desiredOutputLength > RNG_Block_Length
	while (desiredOutputLength > RNG_Block_Length){		
		hashWithTime(seed);
		j = 0;
		for(i = count; i < count + RNG_Block_Length; i++){
			output[i] = seed[j];
			j++;
			if(j==10) printf("\n");
		}

		printf("Iteration num %d:\n",count);
		for(i = 0; i < 320; i++) printf("%02x", output[i]);
		printf("\n\n");

		// Loop statements
		count += RNG_Block_Length;
		desiredOutputLength -= RNG_Block_Length;

	} 

	printf("Iteration num %d:\n",count);
	for(i = 0; i < 320; i++) printf("%02x", output[i]);
	printf("\n\n");

	// operation when the random values needed < RNG_Block_Length
	hashWithTime(seed);
	for(i = count; i < count + desiredOutputLength; i++){
		output[i] = seed[i];
	}





	/*

	// Initialise SHA256	
	SHA256_Init(&ctx); 

	desiredOutputLength /= 50;

	// Input data into hash function
	//SHA256_Update(&ctx, input, lengthOfInput);

	for(i=0; i<5; i++){

		// Obtain current time
		current_time = time(NULL);


		//size_t lengthOfInput = strlen(input); 


	}
	
	
	*/

	

	// writes the hashing output onto output variable
	//SHA256_Final(output, &ctx); 

	// Print the output
	/*
	printf("RN = \n");
	for(i = 0; i < SHA256_DIGEST_LENGTH+10; i++){
		printf("%02x", seed[i]);
	}
	printf("\n");
	*/


}		

void PRNG(uint8_t* output, uint8_t* input, uint32_t outputLength){

	// hash the inputMessage (32 bits), output it in PRNoutput
	simpleHash(output, input);


	//strncat(output, input, strlen(input));

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
	uint8_t pseudoRandNum[RandNumLength] = {0}; // first bit indicates array length, the rest are 0s
	uint16_t numBitLength = 20; // random: 2~2048
	char seed[257] = "12345";	// message - to initialise some hashings
	uint32_t i = 0;

	printf("The random number: \n");
	for(i = 0; i < RandNumLength+1; i++){
		printf("%02x", pseudoRandNum[i]);
	}
	printf("\n");
	

	//PRNG(pseudoRandNum, seed, 10);
	RNG(pseudoRandNum, RandNumLength);

	

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




