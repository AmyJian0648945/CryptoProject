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
	size_t lengthOfInput = strlen(input); 



	//printf("string length: %d\n", lengthOfInput);
	
	SHA256_Init(&ctx);
	//SHA256_Update(&ctx, input, n); // call this each time there are new elements coming in (including the first time)
	




	/*
	SHA256_CTX ctx;
	char *buf;
	size_t n;
	buf = "abc";
	n = strlen(buf);
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, buf, n);
	SHA256_Final(output, &ctx);
	*/
	//output[0] = input[0];
	//output[1] = 4;
}













