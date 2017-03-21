
int signatureMessage(uint8_t *message, uint8_t *encodedMessage){

	//emlen = 256
	//hlen = 32
	//slen = 32

	uint8_t output[32];
	simpleHashWithLength(output, message,256);

	uint8_t hash1[32];
	copyArray8(output,hash1,32);

	uint8_t zeros[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	uint8_t salt[32] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

	uint8_t result[72] = {};
	int k;
	for (k=0; k<72; k++){
		if (k<8)
			result[k] = zeros[k];
		else if (k < 40)
			result[k] = output[k-8];
		else
			result[k] = salt[k-40];
	}
	
	simpleHashWithLength(output, result, 72);
	uint8_t hash2[32];
	copyArray8(output,hash2,32);

	uint8_t ps[190];
	for (k=0;k<190;k++){
		ps[k] = 0;
	}

	uint8_t db[223];
	for (k=0;k<223;k++){
		if (k<190)
			db[k] = ps[k];
		else if (k<191)
			db[k] = 0x01;
		else
			db[k] = salt[k-191];
	}

	// Mask generation function //
	uint8_t dbmask[223];
	maskGenerationFunction(hash2,dbmask);
	// End mask generation function //

	uint8_t maskeddb[223];
	for (k=0;k<223;k++){
		maskeddb[k] = db[k] ^ dbmask[k];
	}
	
	for (k=0;k<256;k++){
		if (k<223)
			encodedMessage[k] = maskeddb[k];
		else if (k<255)
			encodedMessage[k] = hash2[k-223];
		else
			encodedMessage[k] = 0xbc;
	}

	printf("Signature succeeded!\n");
	return 1;
}
