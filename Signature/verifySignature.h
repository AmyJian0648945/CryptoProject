int verifySignature(uint8_t *message, uint8_t *encodedMessage);
// Verifies the integrity of the message.


/// Implementation of the algorithm ///


int verifySignature(uint8_t *message, uint8_t *encodedMessage){

	uint16_t emlen = 256;
	uint16_t hlen = 32;
	uint16_t slen = 32;

	uint8_t output[hlen];
	
	// STEP 2 OF THE ALGORITHM //
	simpleHashWithLength(output, message,256);
	uint8_t mHash[hlen];
	copyArray8(output,mHash,hlen);

	// STEP 4 //
	if (encodedMessage[emlen-1] != 0xbc)
		return 0;

	// STEP 5 //
	uint8_t maskeddb[emlen-hlen-1];
	uint8_t H[hlen];
	int index;
	for (index=0;index<(emlen-hlen-1);index++){
		maskeddb[index] = encodedMessage[index];
	}
	for(index=(emlen-hlen-1);index<(emlen-1);index++){
		H[index-(emlen-hlen-1)] = encodedMessage[index];
	}
	
	// STEP  7 //	
	uint8_t dbmask[emlen-hlen-1];
	maskGenerationFunction(H, dbmask);
	
	// STEP 8 //
	uint8_t db[emlen-hlen-1];
	for(index=0;index<(emlen-hlen-1);index++){
		db[index] = maskeddb[index] ^ dbmask[index];
	}
	
	// STEP 10 //
	uint16_t stopLimit = emlen - hlen - slen - 2;
	for(index=0;index<stopLimit;index++){
		if (db[index] != 0)
			return 0;
	}

	if (db[stopLimit] != 0x01)
		return 0;

	// STEP 11 //
	uint8_t salt[slen];
	for(index=0;index<slen;index++){
		salt[index] = db[stopLimit+1+index];
	}
	
	// STEP 12 //
	uint8_t M[hlen+slen+8];
	for(index=0;index<(hlen+slen+8);index++){
		if (index<8)
			M[index] = 0x00;
		else if (index<hlen+8)
			M[index] = mHash[index-8];
		else
			M[index] = salt[index-hlen-8];
	}
	
	// STEP 13 //
	simpleHashWithLength(output, M, hlen+slen+8);
	uint8_t hash2[hlen];
	copyArray8(output,hash2,hlen);

	// STEP 14 //	
	int i;
	for(i=0;i<hlen;i++){
		if (hash2[i] != H[i])
			return 0;
	}
	printf("Program succeeded!\n");	

	return 1;
}

