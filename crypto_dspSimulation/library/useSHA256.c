#include "useSHA256.h"


/*
void simpleHash(uint8_t* output, uint8_t* input){
	SHA256_CTX ctx;  
	size_t lengthOfInput = strlen(input); 

	SHA256_Init(&ctx); 
	SHA256_Update(&ctx, input, lengthOfInput); 
	SHA256_Final(output, &ctx); 
}
*/


void inline simpleHashWithLength(uint8_t* output, uint8_t* input, size_t lengthOfInput){
	SHA256_CTX ctx;  /* initialise structure used in SHA256 */

	/* Hash and output */
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
	
	simpleHashWithLength(output, output, TIME_DATA_LENGTH);
}


void hashOfLength(uint8_t* output, uint8_t* seed, uint16_t lengthOfHash, size_t lengthOfSeed){
	uint8_t tempHashStorage[SHA256_DIGEST_LENGTH] = {0};
	uint16_t count_ref = 0;

	/* Hash once */
	simpleHashWithLength(tempHashStorage, seed, lengthOfSeed);

	/* While lengthOfHash > SHA256_DIGEST_LENGTH, iteratively add hashed values over to output */
	count_ref = 0;
	while (lengthOfHash > SHA256_DIGEST_LENGTH){ 
		/* Get new hash */
		simpleHashWithLength(tempHashStorage, tempHashStorage, SHA256_DIGEST_LENGTH);
		
		/* Copy hash array over to output array */
		copyArray(output, tempHashStorage, count_ref, SHA256_DIGEST_LENGTH);

		/* Loop statements */
		count_ref += SHA256_DIGEST_LENGTH;
		lengthOfHash -= SHA256_DIGEST_LENGTH;
	} 


	/* When lengthOfHash < SHA256_DIGEST_LENGTH, Add hashed values one last time (same operation as in while loop) */
	simpleHashWithLength(tempHashStorage, tempHashStorage, lengthOfHash);
	copyArray(output, tempHashStorage, count_ref, lengthOfHash);

}




