
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
	K = Secret key 

For more information about the protocol, see https://tools.ietf.org/html/rfc2104  
To verify the code, see http://www.freeformatter.com/hmac-generator.html
* * * * * * * * * * * * * * * * * * * * * * * * */


////////// Define Macros Here //////////
#ifndef HMAC_H
#define HMAC_H

#ifndef SHA256_DIGEST_LENGTH 	
#define SHA256_DIGEST_LENGTH	32 	
#endif 

#define DataBlockSize			64







////////// Function Declarations //////////

////////// Function Implementation //////////



void hmac(uint8_t* output, uint8_t* secretKey){







	printf("hello world!\n");
}











#endif /* HMAC_H */
















