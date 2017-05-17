/* * * * * * * * * * * * * * * * * * * * * * * *
What it does: generates a (pseudo) random number of length 
	PRNlength (each element of type uint_8) based on the input 
	seed (of any length)

*** Function Description ***

void PRNG(Pseudo Random Number, input seed, 
		  length of desired pseudo random number in uint8_t); 

	This function uses A5/1 Stream Cipher to create a psuedo 
	random number. The feedback shift register lengths are 
	specified in the macros as "PRNG_STREAM1_LENGTH", and are 
	created using repetitive calls to SHA256, initialised with
	the specified input seed. "PRNG_CMP_LOCATION" is the element
	that will be compared between the different shift registers.

void RNG(Random number output, length of random number in uint8_t); 	
	-> Doesn't require input seed
* * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PRNG_H
#define PRNG_H

#include "macros.h"
#include "useSHA256.h"



void RNG(uint8_t*, uint16_t); 		
	/* Obtains random number, length in BYTES */
void PRNG(uint8_t*, uint8_t*, uint16_t, uint16_t); 	
	/* Obtains pseudo random number, based on seed - last element is in BYTES */
uint32_t findRandNum(); 
	/* returns a random number using the above functions */
void updateFSR(uint8_t*, uint16_t);
	/* For use in PRNG; to update the shift registers */ 
uint8_t compareFSR(uint8_t*, uint8_t*, uint8_t*, uint16_t);
	/* For use in PRNG; to compare specific elements in the shift registers */ 


#endif


