#include "hmac.h"

/* * * * * Algorithm subparts: * * * * * 

	H(K XOR opad, H(K XOR ipad, msg))
=	H(  result2 , H(  result1 , msg))	...(1)
=	H(  result2 , 	      output	)	...(2)
=	 	  		output	 				...(3)

* * * * * * * * * * * * * * * * * * * * */

void hmac(uint8_t* output, uint8_t* secretKey, uint8_t* inputMsg, uint16_t secretKeySize, uint16_t inputMsgSize){
	uint8_t ipad[DATA_BLOCK_SIZE] = {0}, opad[DATA_BLOCK_SIZE] = {0};
	uint8_t paddedKey[DATA_BLOCK_SIZE] = {0};
	uint16_t i = 0;

	uint8_t result1[DATA_BLOCK_SIZE + MAX_MESSAGE_LENGTH] = {0};
	uint8_t result2[DATA_BLOCK_SIZE + SHA256_DIGEST_LENGTH] = {0};


	/* Initialise ipad and opad */
	for(i=0; i<DATA_BLOCK_SIZE; i++){ 
		ipad[i] = 0x36;  
		opad[i] = 0x5C;
	}

	/* Check if the key is too long */
	if(secretKeySize > DATA_BLOCK_SIZE){
		simpleHashWithLength(paddedKey, secretKey, secretKeySize);
	}
	else{
		for(i=0; i<secretKeySize; i++) paddedKey[i] = secretKey[i];
	}

	/* (1) result = key XOR ipad (or opad) */
	XOR(result1, paddedKey, ipad, DATA_BLOCK_SIZE); /* result1 = K XOR ipad */
	XOR(result2, paddedKey, opad, DATA_BLOCK_SIZE); /* result2 = K XOR opad */

	/* (2) output = H(result1, text) */
	concat(result1, inputMsg, DATA_BLOCK_SIZE, inputMsgSize);
	simpleHashWithLength(output, result1, DATA_BLOCK_SIZE + inputMsgSize); 
	
	/* (3) output = H(result2, output) */
	concat(result2, output, DATA_BLOCK_SIZE, SHA256_DIGEST_LENGTH);
	simpleHashWithLength(output, result2, DATA_BLOCK_SIZE + SHA256_DIGEST_LENGTH);
}




















