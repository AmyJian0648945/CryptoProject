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

#define RNG_Block_Length    30      /* must be <256/8 = 32!!! */
#define RandNumLength       60      /* for testing purposes */

#define MaxRandNumLength    2048    /* for up / down boundaries of x,y,g */
#define MinRandNumLength    2

#define PRNG_FSR1_LENGTH    64
#define PRNG_FSR2_LENGTH    65
#define PRNG_FSR3_LENGTH    72

#define PRNG_CMP_LOCATION   9       /* must be < any of PRNG_FSR_LENGTH */
#define PRNG_XOR_LOCATION1  7       /* For use in "updateFSR" must be < any of PRNG_FSR_LENGTH */
#define PRNG_XOR_LOCATION2  11          
#define PRNG_XOR_LOCATION3  15
#define PRNG_XOR_LOCATION4  23

#ifndef USESHA256
#include "useSHA256.h"
#endif





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


