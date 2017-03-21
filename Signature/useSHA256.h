/* * * * * * * * * * * * * * * * * * * * * * * *
This file simply hashes the message (of any size), using sha2.h

Variables: 
	output:		contains the hashed message (of data type uint16, 256 bits in total)
	input:		input message 
	lengthOfInput:
				bit size of the input length 


To check the validity of results, compare with:



* * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef SHA256_DIGEST_LENGTH
#define SHA256_DIGEST_LENGTH	32 	/* Also defined in sha2.h, here for clarification and just-in-case purposes */
#endif /* SHA256_DIGEST_LENGTH */

#define TIME_DATA_BASE			10
#define SHA2_USE_INTTYPES_H

#include<time.h>
#include"sha2.h"
#include"sha2.c"

////////// Function Declarations //////////

void simpleHash(uint8_t*, uint8_t*); 	/* Does a single SHA256 hash */
void simpleHashWithLength(uint8_t*, uint8_t*, size_t); /* same as simpleHash, but with specified length */
void hashWithTime(uint8_t*);	/* XORs input with time data, then hashed */
void hashOfLength(uint8_t*, uint8_t*, uint16_t, size_t); /* Gives a hashed value of specified length based on seed */ 

// Helpful functions
uint16_t timeData(); /* Obtain current time to microseconds */
void copyArray(uint8_t*, uint8_t*, uint16_t, uint16_t); /* Copies array over from input to output, starting from "index" */
//void printArray(uint8_t*, uint16_t);	/* prints the array */



////////// Function Implementation //////////



void simpleHash(uint8_t* output, uint8_t* input){

	SHA256_CTX ctx;  /* initialise structure used in SHA256 */
	size_t lengthOfInput = strlen(input); 
	
	SHA256_Init(&ctx); /* Initialise SHA256 */
	SHA256_Update(&ctx, input, lengthOfInput); /* Input data into hash function */
	SHA256_Final(output, &ctx); /* writes the hashing output onto output variable */
}


void simpleHashWithLength(uint8_t* output, uint8_t* input, size_t lengthOfInput){

	SHA256_CTX ctx;  /* initialise structure used in SHA256 */

	SHA256_Init(&ctx); /* Initialise SHA256 */
	SHA256_Update(&ctx, input, lengthOfInput); /* Input data into hash function */
	SHA256_Final(output, &ctx); /* writes the hashing output onto output variable */
}


void hashWithTime(uint8_t* output){
	uint8_t i = 0;
	uint16_t timeValue = 0;

	timeValue = timeData();
	
	while(timeValue > 0){
		output[i] = timeValue % TIME_DATA_BASE;
		timeValue /= 10; 
		i++;
	}
	
	simpleHash(output, output);
}


void hashOfLength(uint8_t* output, uint8_t* seed, uint16_t lengthOfHash, size_t lengthOfSeed){
	uint8_t tempHashStorage[SHA256_DIGEST_LENGTH] = {0};
	uint16_t output_count = 0, temp_count = 0, count_ref = 0;

	// Hash once
	simpleHashWithLength(tempHashStorage, seed, lengthOfSeed);

	// While lengthOfHash > SHA256_DIGEST_LENGTH, iteratively add hashed values over to output
	count_ref = 0;
	while (lengthOfHash > SHA256_DIGEST_LENGTH){ 
		// Get new hash
		simpleHashWithLength(tempHashStorage, tempHashStorage, SHA256_DIGEST_LENGTH);
		
		// Copy hash array over to output array
		copyArray(output, tempHashStorage, count_ref, SHA256_DIGEST_LENGTH);

		// Loop statements
		count_ref += SHA256_DIGEST_LENGTH;
		lengthOfHash -= SHA256_DIGEST_LENGTH;
	} 


	// When lengthOfHash < SHA256_DIGEST_LENGTH, Add hashed values one last time (same operation as in while loop)
	simpleHashWithLength(tempHashStorage, tempHashStorage, lengthOfHash);
	copyArray(output, tempHashStorage, count_ref, lengthOfHash);

}


uint16_t timeData(){
	struct timeval tv; /* tv is the time variable */

	gettimeofday(&tv, NULL);
	return tv.tv_usec;
}


void copyArray(uint8_t* output, uint8_t* input, uint16_t startingIndex, uint16_t lengthToCopy){
	uint16_t i = 0;

	for(i = 0; i < lengthToCopy; i++) {
		output[startingIndex + i] = input[i];
	}
}

/*
void printArray(uint8_t* output, uint16_t iter){
	uint16_t i = 0;

	for(i = 0; i < iter; i++) {
		printf("%x\t", output[i]);

		if(i%5 == 4) 	printf("\n");
		if(i%25 == 24) 	printf("\n");
	}
}*/


















