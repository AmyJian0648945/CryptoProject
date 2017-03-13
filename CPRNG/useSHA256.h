/**
This file simply hashes the message (of any size), using sha2.h

Variables:
output - 	contains the hashed input (of data type uint32, 256 bits in total)
input -		input message 
lengthOfInput - 
			bit size of the input length 
**/






void hash(uint8_t* output, uint8_t* input){

	/*** initialise the structure and variables ***/
	SHA256_CTX ctx;  // initialise SHA256
	size_t lengthOfInput = strlen(input) - 1; // "-1" gets rid of endline character 
	


	SHA256_Init(&ctx); 
	SHA256_Update(&ctx, input, lengthOfInput); 
	SHA256_Final(output, &ctx); 


}













