/**
This file simply hashes the message (of any size), using sha2.h

Variables:
output - 	contains the hashed message (of data type uint32, 256 bits in total)
input -		input message 
lengthOfInput - 
			bit size of the input length 


To check the validity of results, compare with:
http://www.freeformatter.com/sha256-generator.html#ad-output 

**/

#include"sha2.h"
#include"sha2.c"


void hash(uint8_t* output, uint8_t* input){

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













