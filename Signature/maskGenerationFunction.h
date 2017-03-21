
void maskGenerationFunction(uint8_t *input, uint8_t *dbmask){
	
	// masklen = 223 [octets]
	// hashlen = 32 [octets]
	// masklen / hashlen (rounded up) = 7
	// rounded up - 1 = 6
	int counter;
	uint8_t T[224] = {};
	for (counter=0; counter<7; counter++){
		// I2OSP(counter,4) - STEP A //
		uint8_t string[4];
		string[1] = 0;
		string[2] = 0;
		string[3] = 0;
		string[0] = counter;
		// CONCATENATION - STEP B //
		uint8_t tobehashed[36];
		int i;
		for (i=0;i<36;i++){
			if (i<32)
				tobehashed[i] = input[i];
			else
				tobehashed[i] = string[i-32];
		}

		uint8_t output[32];
		simpleHashWithLength(output,tobehashed,36);
		/* Concatenation of T and new Hash value (hashcounter) */
		for(i=0;i<32;i++){
			T[counter*32+i]=output[i];
		}	
	}
	int index;
	for(index=0;index<223;index++){
		dbmask[index]=T[index];
	}
}
