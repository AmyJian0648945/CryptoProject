
#include "../Header/maskGenerationFunction.h"

/*
	Implementation of the mask generation function, used in the signatureMessage function.
	uint8_t *input = number to be masked (input)
	uint8_t *dbmask = mask (output)
*/
void maskGenerationFunction(uint8_t *input, uint8_t *dbmask){

	/* 	
	masklen / hashlen (rounded up) = 7
	rounded up - 1 = 6
	=> from 0 to 6 (6 included) */
	int counter;
	uint8_t T[MASKLEN+1] = {0};
	uint8_t string[4];
	uint8_t tobehashed[36] = {0};
	uint8_t output[HASHLEN] = {0};
	int i;
	int index;
	for (counter=0; counter<3; counter++){
		/* STEP A */
		string[1] = 0;
		string[2] = 0;
		string[3] = 0;
		string[0] = counter;
			
		for(i=0;  i<33; i++) tobehashed[i] = input[i];
		for(i=32; i<36; i++)  tobehashed[i] = string[i-32];

		simpleHashWithLength(output,tobehashed,36);
		/* Concatenation of T and new Hash value (hashcounter) */
		for(i=0;i<HASHLEN;i++){
			T[counter*HASHLEN+i]=output[i];
		}
	}
	for(index=0;index<MASKLEN;index++){
		dbmask[index]=T[index];
	}
	
}


