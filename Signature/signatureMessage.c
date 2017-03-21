
int signatureMessage(uint8_t *message, uint8_t *encodedMessage){

	uint16_t emlen = 256;
	uint16_t hlen = 32;
	uint16_t slen = 32;

	// STEP 2 //
	uint8_t output[hlen];
	simpleHashWithLength(output, message,emlen);

	uint8_t hash1[hlen];
	copyArray8(output,hash1,hlen);

	// STEP 3 //
	if (emlen < hlen + slen + 2)
		return 0;
	
	// STEP 4 //
	uint8_t salt[32];
	RNG(salt,32);

	// STEP 5 //
	uint8_t zeros[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	uint8_t result[hlen+slen+8];
	int k;
	for (k=0; k<(hlen+slen+8); k++){
		if (k<8)
			result[k] = zeros[k];
		else if (k < (8+hlen))
			result[k] = output[k-8];
		else
			result[k] = salt[k-(8+hlen)];
	}
	
	// STEP 6 //
	simpleHashWithLength(output, result, hlen+slen+8);
	uint8_t hash2[hlen];
	copyArray8(output,hash2,hlen);

	// STEP 7 //
	uint8_t ps[emlen-hlen-slen-2];
	for (k=0;k<(emlen-hlen-slen-2);k++){
		ps[k] = 0;
	}

	// STEP 8 //
	uint8_t db[emlen-hlen-1];
	for (k=0;k<(emlen-hlen-1);k++){
		if (k<(emlen-hlen-slen-2))
			db[k] = ps[k];
		else if (k<(emlen-hlen-slen-1))
			db[k] = 0x01;
		else
			db[k] = salt[k-(emlen-hlen-slen-1)];
	}

	// STEP 9 - Mask generation function //
	uint8_t dbmask[emlen-hlen-1];
	maskGenerationFunction(hash2,dbmask);

	// STEP 10 //
	uint8_t maskeddb[emlen-hlen-1];
	for (k=0;k<(emlen-hlen-1);k++){
		maskeddb[k] = db[k] ^ dbmask[k];
	}
	
	// STEP 12 //
	for (k=0;k<emlen;k++){
		if (k<(emlen-hlen-1))
			encodedMessage[k] = maskeddb[k];
		else if (k<(emlen-1))
			encodedMessage[k] = hash2[k-(emlen-hlen-1)];
		else
			encodedMessage[k] = 0xbc;
	}

	printf("Signature succeeded!\n");
	return 1;
}
