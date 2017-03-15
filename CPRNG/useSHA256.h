/* * * * * * * * * * * * * * * * * * * * * * * *
This file simply hashes the message (of any size), using sha2.h

Variables: 
	output:		contains the hashed message (of data type uint32, 256 bits in total)
	input:		input message 
	lengthOfInput:
				bit size of the input length 


To check the validity of results, compare with:
http://www.freeformatter.com/sha256-generator.html#ad-output 

* * * * * * * * * * * * * * * * * * * * * * * * */

#define TIME_DATA_LENGTH 6
#define TIME_DATA_BASE 10
#define ASCII_SHIFT 48

#include"sha2.h"
#include"sha2.c"
#include<time.h>


////////// Function Declarations //////////

void simpleHash(uint8_t*, uint8_t*); 	// Does a single SHA256 hash
void hashWithTime(uint8_t*);	// XORs input with time data, then hashed

// Helpful functions
uint8_t timeData(); // Obtain current time to microseconds




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
	uint8_t timeValue = 0;

	timeValue = timeData();


	output[0] = (char) (timeValue % TIME_DATA_BASE + ASCII_SHIFT);
	printf("output = %c\n",output[0]);
	
	//MEMCPY_BCOPY(output*, 3, 1);

	//output[i] ^= timeValue % TIME_DATA_BASE;
	//printf("output = %d\n",output[i]);

	/*
	for(i = 0; i < TIME_DATA_LENGTH; i++){
		output[i] ^= timeValue % TIME_DATA_BASE;
		timeValue /= 10;
	}
	
*/

	//printf("Here2 = %c %c\n",output[0],output[1]);
}



uint8_t timeData(){
	struct timeval tv; /* tv is the time variable */

	gettimeofday(&tv, NULL);
	return tv.tv_usec;
}

















