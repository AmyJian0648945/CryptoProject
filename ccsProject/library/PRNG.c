#include "PRNG.h"

void RNG(uint8_t* output, uint16_t desiredOutputLength){

	/* Initialise Variables */
	static uint8_t seed[32] = {0}; 		/* this will use previous results's hash as the seed */
	uint8_t const randString[SHA256_DIGEST_LENGTH*2] = "8bc73c890d2dd2977128d97ecfcdeb203ca9c27da294454595c61bb1e2684fbb";
		/* This will be used to initialise the hash function at the very beginning - i.e. rand value that is not zero*/
	uint16_t i = 0, j = 0, count = 0;

	/* Refresh seed, or define a new one AND hash it */
	if(seed[0] == 0) {
		for(i = 0; i < SHA256_DIGEST_LENGTH; i++) seed[i] = randString[i];
		hashWithTime(seed);			
	}
	else hashWithTime(seed);

	/* Operation if the desiredOutputLength > RNG_Block_Length  */
	count = 0;
	while (desiredOutputLength > RNG_Block_Length){ 
		j = 0;

		/* Get new hash */
		hashWithTime(seed);
		
		/* Copy hash array over to output array */
		for(i = count; i < count + RNG_Block_Length; i++){	
			output[i] = seed[j];
			j++;
		}

		/* Loop statements */
		count += RNG_Block_Length;
		desiredOutputLength -= RNG_Block_Length;
	} 

	/* operation when the random values needed < RNG_Block_Length */
	hashWithTime(seed);
	j = 0;
	for(i = count; i < count + desiredOutputLength; i++){
		output[i] = seed[j];
		j++;
	}
}		

void PRNG(uint8_t* output, uint8_t* seed, uint16_t outputLength, uint16_t lengthOfSeed){
	uint8_t FSR1[PRNG_FSR1_LENGTH] = {0}, FSR2[PRNG_FSR2_LENGTH] = {0}, FSR3[PRNG_FSR3_LENGTH] = {0}; /* FSR = feedback shift registers */ 
	uint16_t i = 0;

	/* Generate shift registers */
	hashOfLength(FSR1, seed, PRNG_FSR1_LENGTH, lengthOfSeed);
	hashOfLength(FSR2, FSR1, PRNG_FSR2_LENGTH, PRNG_FSR1_LENGTH);
	hashOfLength(FSR3, FSR2, PRNG_FSR3_LENGTH, PRNG_FSR2_LENGTH);

	/* For each iteration, generate a random character */
	for(i=0; outputLength > 0; i++){
		output[i] = compareFSR(FSR1, FSR2, FSR3, PRNG_CMP_LOCATION);
		outputLength--;
	}

}


void updateFSR(uint8_t* output, uint16_t size){
	uint16_t i = 0;
	uint8_t filler = 0;
	filler = output[PRNG_XOR_LOCATION1] ^ output[PRNG_XOR_LOCATION2] ^ output[PRNG_XOR_LOCATION3] ^ output[PRNG_XOR_LOCATION4];

	for(i=0; i<size-1; i++) output[i] = output[i+1];
	output[i] = filler;
}



uint8_t compareFSR(uint8_t* FSR1, uint8_t* FSR2, uint8_t* FSR3, uint16_t ref){

	while(1){
		if( FSR1[ref] == FSR2[ref] 	&& 	FSR1[ref] == FSR3[ref] ) {
			updateFSR(FSR1, PRNG_FSR1_LENGTH); 
			updateFSR(FSR2, PRNG_FSR2_LENGTH); 
			updateFSR(FSR3, PRNG_FSR3_LENGTH); 

			return FSR1[ref-1];
		}
		else if( FSR1[ref] == FSR2[ref] ){ 
			updateFSR(FSR1, PRNG_FSR1_LENGTH); 
			updateFSR(FSR2, PRNG_FSR2_LENGTH); 
		}
		else if( FSR2[ref] == FSR3[ref] ){ 
			updateFSR(FSR2, PRNG_FSR2_LENGTH); 
			updateFSR(FSR3, PRNG_FSR3_LENGTH); 
		}
		else if( FSR1[ref] == FSR3[ref] ){ 
			updateFSR(FSR1, PRNG_FSR1_LENGTH); 
			updateFSR(FSR3, PRNG_FSR3_LENGTH); 
		}
		else{
			updateFSR(FSR1, PRNG_FSR1_LENGTH); 
			updateFSR(FSR2, PRNG_FSR2_LENGTH); 
			updateFSR(FSR3, PRNG_FSR3_LENGTH); 
		}
	}
}


uint32_t findRandNum(){
	uint8_t getNum[2] = {0};
	uint32_t randNum = 0;

	while(1){
		RNG(getNum, 2); 

		/* concatenate 2 hex values */
		randNum = getNum[0];
		randNum <<= 8;
		randNum += getNum[1];

		/* Make sure its smaller than 2048 */
		if(randNum > MaxRandNumLength) randNum %= MaxRandNumLength;
		if(randNum > MinRandNumLength) return randNum;
	}

}





