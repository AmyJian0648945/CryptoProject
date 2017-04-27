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


#ifndef HMAC_H
#define HMAC_H

#define DATA_BLOCK_SIZE         64
#define MAX_MESSAGE_LENGTH              500 /* CURRENTLY A PATCH: ADJUST THIS VARIABLE after discussion with the processing group!! */
#define MAX_TRANSMISSION_BLOCK_LENGTH   512 /* CURRENTLY A PATCH: needs to be 16x */

#ifndef STDLIB_H
#include <stdint.h>
#endif 
#ifndef HELPFULFUNCTIONS_H
#include "helpfulFunctions.h"
#endif
#ifndef USESHA256_H
#include "useSHA256.h"
#endif

void hmac(uint8_t*, uint8_t*, uint8_t*, uint16_t, uint16_t);
	/* Calculates the HMAC based on an input key and message */

#endif /* HMAC_H */
















