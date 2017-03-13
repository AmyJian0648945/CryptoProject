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






	printf("length of input: %d\n", lengthOfInput);

	// Checks if input size is larger than digest; call "update" as many 
	//	times as needed to input all data

/*
	do{
		SHA256_Update(&ctx, input, lengthOfInput); 
		lengthOfInput -= SHA256_DIGEST_LENGTH;
	} while(lengthOfInput > SHA256_DIGEST_LENGTH)
*/
	
	SHA256_Update(&ctx, input, lengthOfInput); 







	// writes the hashing output onto output variable
	SHA256_Final(output, &ctx); 

}













