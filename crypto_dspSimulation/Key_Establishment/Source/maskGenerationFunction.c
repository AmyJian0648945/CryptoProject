
#include "../Header/maskGenerationFunction.h"

/*
	Implementation of the mask generation function, used in the signatureMessage function.
	uint8_t *input = number to be masked (input)
	uint8_t *dbmask = mask (output)
*/
void maskGenerationFunction(uint8_t *input, uint8_t *dbmask){

	/* 	
	masklen / hashlen (rounded up) = 3
	rounded up - 1 = 2
	=> from 0 to 2 (2 included) */
	int counter;
	uint8_t T[MASKLEN+1] = {0};
	uint8_t string[4] = {0};
	uint8_t tobehashed[36] = {0};
	uint8_t output[HASHLEN] = {0};
	int i;
	int index;
	for(i=0;i<32;i++){
		tobehashed[i] = input[i];
	}
	for (counter=0; counter<3; counter++){
		/* STEP A */
		string[0] = counter;
		/* CONCATENATION - STEP B */
		for (i=32;i<36;i++){
			tobehashed[i] = string[i-32];
		}
		simpleHashWithLength(output,tobehashed,36);
		/* Concatenation of T and new Hash value (hashcounter) */
		for(i=0;i<HASHLEN;i++){
			T[counter*HASHLEN+i]=output[i];
		}
	}
	string[0] = counter;
	for(index=0;index<MASKLEN;index++){
		dbmask[index]=T[index];
	}
	
}


