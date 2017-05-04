

int main(){

	// initialise variables
	uint8_t pseudoRandNum[RandNumLength+10] = {0}; // first bit indicates array length, the rest are 0s
	uint8_t seed[36] = "4567890abcdefghijklmnopqrstuvwxyz";	// message - to initialise some hashings


	findRandNum();


	//printf("PRNG - Initial:\n"); printArray(pseudoRandNum, RandNumLength);

	//PRNG(pseudoRandNum, seed, RandNumLength, 36);
	//RNG(pseudoRandNum, RandNumLength);

	//printf("PRNG - After Hashing:\n"); printArray(pseudoRandNum, RandNumLength);

	
	return 0;
}
