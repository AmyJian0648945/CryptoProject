/* * * * * * * * * * * * * * * * * * * * * * * *
This file simply hashes the message (of any size), using sha2.h

Variables: 
	output:		contains the hashed message (of data type uint16, 256 bits in total)
	input:		input message 
	lengthOfInput:
				bit size of the input length 


To check the validity of results, compare with:
http://www.freeformatter.com/sha256-generator.html


* * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef	USESHA256_H
#define	USESHA256_H



/******* Function Declarations *******/

/* void simpleHash(uint8_t*, uint8_t*); */ 	/* Does a single SHA256 hash */
void simpleHashWithLength(uint8_t*, uint8_t*, size_t); 
	/* same as simpleHash, but with specified length 
	 * OUTPUT = hex, INPUT = hex */
void hashWithTime(uint8_t*); 
	/* XORs input with time data, then hashed */
void hashOfLength(uint8_t*, uint8_t*, uint16_t, size_t); 
	/* Gives a hashed value of specified length based on seed */ 


#endif


