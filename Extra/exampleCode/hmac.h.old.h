
/* * * * * * * * * * * * * * * * * * * * * * * *
This file calculates the HMAC of a message. The concepts explanation 
and variable specifications are selectively copy pasted from the website 
below. 

--> Concepts explanation: 
	HMAC is a mechanism for message authentication using cryptographic 
	hash functions. The cryptographic strength of HMAC relies on the
	properties of the hash function (SHA256 in this case). 

	To compute HMAC over the data 'text':
	H(K XOR opad, H(K XOR ipad, text))

--> Variable Specifications:

	>> The secret key: 
	The authentication key K can be of any length up to DataBlockSize, 
	the block length of the hash function.  Applications that use keys 
	longer than SHA256_DIGEST_LENGTH bytes will first hash the key using 
	SHA256 and then use the resultant L byte string as the actual key to 
	HMAC.
	
	>> Fixed strings
	ipad = the byte 0x36 repeated B times
	opad = the byte 0x5C repeated B times

--> Notation comparison to reference:
	B = DataBlockSize (bytes)
	L = SHA256_DIGEST_LENGTH (bytes)
	H = SHA256 
	K = Secret key (128 bits = 16 bytes)

*** For more information about the protocol, see https://tools.ietf.org/html/rfc2104  
*** To verify the code, see http://www.freeformatter.com/hmac-generator.html
* * * * * * * * * * * * * * * * * * * * * * * * */


////////// Define Macros Here //////////

//#define SECRET_KEY_SIZE         32
//#define DATA_BLOCK_SIZE         64

#ifndef HMAC_H
#define HMAC_H


////////// Function Declarations //////////
void concat(uint8_t*, uint8_t*, uint16_t, uint16_t);
void XOR(uint8_t*, uint8_t*, uint8_t*, uint16_t);
void hmac(uint8_t*, uint8_t*, uint8_t*);


////////// Function Implementation //////////
void concat(uint8_t* base, uint8_t* arrayToAppend, uint16_t baseLength, uint16_t lengthToAppend){
	uint16_t i = 0, j = 0;

	for(i=baseLength; i<baseLength + lengthToAppend; i++){
		base[i] = arrayToAppend[j];
		j++;
	}
}

void XOR(uint8_t* output, uint8_t* input1, uint8_t* input2, uint16_t lengthToXOR){
	uint16_t i = 0;
	for(i=0; i<lengthToXOR; i++) { 
		output[i] = input1[i] ^ input2[i];
	}
}


/* * * * * Algorithm naming: * * * * * 

	H(K XOR opad, H(K XOR ipad, msg))
=	H(  result2 , H(  result1 , msg))	...(1)
=	H(  result2 , 	      output	)	...(2)
=	 	  		output	 				...(3)

* * * * * * * * * * * * * * * * * * */

void hmac(uint8_t* output, uint8_t* secretKey, uint8_t* inputMsg){
	uint8_t ipad[DATA_BLOCK_SIZE] = {0}, opad[DATA_BLOCK_SIZE] = {0};
	uint8_t paddedKey[DATA_BLOCK_SIZE] = {0};
	uint16_t i = 0;

	uint8_t result1[DATA_BLOCK_SIZE + MSG_LENGTH] = {0};
	uint8_t result2[DATA_BLOCK_SIZE + SHA256_DIGEST_LENGTH] = {0};
	uint8_t resultHash[SHA256_DIGEST_LENGTH] = {0};

	// Initialise ipad and opad
	for(i=0; i<DATA_BLOCK_SIZE; i++){ 
		ipad[i] = 0x36;  
		opad[i] = 0x5C;
	}

	// Initialise the key (the rest is already 0s)
	for(i=0; i<HMAC_SECRET_KEY_SIZE; i++) paddedKey[i] = secretKey[i];
	
	printf("--------------------Debug0:--------------------\n");
	printf("Padded Secret Key: "); printArrayNoSpaces(paddedKey, DATA_BLOCK_SIZE);


	// (1) result = key XOR ipad (or opad)
	XOR(result1, paddedKey, ipad, DATA_BLOCK_SIZE); /* result1 = K XOR ipad */
	XOR(result2, paddedKey, opad, DATA_BLOCK_SIZE); /* result2 = K XOR opad */

	printf("--------------------V Debug1: check XOR--------------------\n");
	printf("result1"); printArrayNoSpaces(result1, DATA_BLOCK_SIZE + MSG_LENGTH);
	printf("input1. secret key"); printArrayNoSpaces(paddedKey, DATA_BLOCK_SIZE);
	printf("input2. ipad"); printArrayNoSpaces(ipad, DATA_BLOCK_SIZE);
	


	printf("--------------------V Debug2: check concat--------------------\n");
	printf("input1. result1"); printArrayNoSpaces(result1, DATA_BLOCK_SIZE + MSG_LENGTH);
	printf("input2. inputMsg"); printArrayNoSpaces(inputMsg, MSG_LENGTH);
	// (2) output = H(result1, text)
	concat(result1, inputMsg, DATA_BLOCK_SIZE, MSG_LENGTH);
	
	printf("result1"); printArrayNoSpaces(result1, DATA_BLOCK_SIZE + MSG_LENGTH);
	

	printf("--------------------V Debug3: check hash--------------------\n");
	
	simpleHashWithLength(output, result1, DATA_BLOCK_SIZE + MSG_LENGTH); 
	
	printf("output"); printArrayNoSpaces(output, SHA256_DIGEST_LENGTH);
	printf("input1. result1"); printArrayNoSpaces(result1, DATA_BLOCK_SIZE + MSG_LENGTH);
	


	printf("--------------------V Debug4: check concat--------------------\n");
	printf("input1. result2"); printArrayNoSpaces(result2, DATA_BLOCK_SIZE + SHA256_DIGEST_LENGTH);
	printf("input2. output"); printArrayNoSpaces(output, SHA256_DIGEST_LENGTH);

	// (3) output = H(result2, output)
	concat(result2, output, DATA_BLOCK_SIZE, SHA256_DIGEST_LENGTH);
	
	printf("output: result2"); printArrayNoSpaces(result2, DATA_BLOCK_SIZE + SHA256_DIGEST_LENGTH);
	


	printf("--------------------V Debug5: check hash--------------------\n");
	simpleHashWithLength(output, result2, DATA_BLOCK_SIZE + SHA256_DIGEST_LENGTH);

	
	printf("output"); printArrayNoSpaces(output, SHA256_DIGEST_LENGTH);
	printf("input1. result2"); printArrayNoSpaces(result2, DATA_BLOCK_SIZE + SHA256_DIGEST_LENGTH);



}





#endif /* HMAC_H */
















