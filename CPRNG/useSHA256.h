/* * * * * * * * * * * * * * * * * * * * * * * *
This file simply hashes the message (of any size), using sha2.h

Variables: 
	output:		contains the hashed message (of data type uint32, 256 bits in total)
	input:		input message 
	lengthOfInput:
				bit size of the input length 


To check the validity of results, compare with:



* * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef SHA256_DIGEST_LENGTH
#define SHA256_DIGEST_LENGTH	32 	/* Also defined in sha2.h, here for clarification and just-in-case purposes */
#endif /* SHA256_DIGEST_LENGTH */

#define TIME_DATA_BASE			10


#include<time.h>
#include"sha2.h"
#include"sha2.c"



////////// Function Declarations //////////

void simpleHash(uint8_t*, uint8_t*); 	// Does a single SHA256 hash
void hashWithTime(uint8_t*);	// XORs input with time data, then hashed
void hashOfLength(uint8_t*, uint8_t*, uint32_t); /* Gives a hashed value of specified length based on seed*/ 

// Helpful functions
uint32_t timeData(); // Obtain current time to microseconds
void copyArray(uint32_t*, uint32_t*, uint32_t, uint32_t); /* Copies array over from input to output, starting from "index"*/




////////// Function Implementation //////////

void simpleHash(uint8_t* output, uint8_t* input){

	// initialise variables
	SHA256_CTX ctx;  // structure used in SHA256
	size_t lengthOfInput = strlen(input); 
	uint32_t i = 0;

	// Initialise SHA256	
	SHA256_Init(&ctx); 

	// Input data into hash function
	SHA256_Update(&ctx, input, lengthOfInput);
	
	// writes the hashing output onto output variable
	SHA256_Final(output, &ctx); 
}


void hashWithTime(uint8_t* output){
	uint8_t i = 0;
	uint32_t timeValue = 0;

	timeValue = timeData();
	
	while(timeValue > 0){
		output[i] = timeValue % TIME_DATA_BASE;
		timeValue /= 10; 
		i++;
	}
	
	simpleHash(output, output);
}


uint32_t timeData(){
	struct timeval tv; /* tv is the time variable */

	gettimeofday(&tv, NULL);
	return tv.tv_usec;
}

void copyArray(uint32_t* output, uint32_t* input, uint32_t startingIndex, uint32_t lengthToCopy){
	uint32_t i = 0;
	for(i=0; i<lengthToCopy; i++) output[startingIndex + i] = input[i];
}

void hashOfLength(uint8_t* output, uint8_t* seed, uint32_t lengthOfHash){
	uint32_t tempHashStorage[32] = {0};
	uint32_t output_count = 0, temp_count = 0, count_ref = 0;

	// Hash once
	simpleHash(tempHashStorage, seed);
	
	// While lengthOfHash > SHA256_DIGEST_LENGTH, iteratively add hashed values over to output
	count_ref = 0;
	while (lengthOfHash > SHA256_DIGEST_LENGTH){ 
		// Get new hash
		simpleHash(tempHashStorage, tempHashStorage);
		
		// Copy hash array over to output array
		copyArray(uint32_t* output, uint32_t* tempHashStorage, uint32_t count_ref, SHA256_DIGEST_LENGTH){

		// Loop statements
		count_ref += SHA256_DIGEST_LENGTH;
		lengthOfHash -= SHA256_DIGEST_LENGTH;
	} 

	// When lengthOfHash > SHA256_DIGEST_LENGTH, Add hashed values one last time (same operation as in while loop)
	simpleHash(tempHashStorage, tempHashStorage);
	copyArray(uint32_t* output, uint32_t* tempHashStorage, uint32_t count_ref, SHA256_DIGEST_LENGTH){

}
















