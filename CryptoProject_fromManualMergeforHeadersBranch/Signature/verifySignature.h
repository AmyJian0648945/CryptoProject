#ifndef VERIFYSIGNATURE_H
#define VERIFYSIGNATURE_H

#define EMLEN	256
#define HASHLEN	32
#define	SLEN	32

/*
	Verifying the encoded message, after decryption of the received signature, for entity authentication.
	uint8_t *message = what encodedMessage should be after decoding (input)
	uint8_t *encodedMessage = what is received (to be decoded) (input).
*/
uint16_t verifySignature(uint8_t *message, uint8_t *encodedMessage){

	uint8_t mHash[HASHLEN] = {0};
	uint8_t hash2[HASHLEN] = {0};
	uint8_t maskeddb[EMLEN-HASHLEN-1] = {0};
	uint8_t H[HASHLEN] = {0};
	int index;
	uint8_t dbmask[EMLEN-HASHLEN-1] = {0};
	uint8_t db[EMLEN-HASHLEN-1] = {0};
	uint16_t stopLimit = EMLEN - HASHLEN - SLEN - 2;
	uint8_t salt[SLEN] = {0};
	uint8_t M[HASHLEN+SLEN+8] = {0};
	
	/* STEP 2 OF THE ALGORITHM */
	simpleHashWithLength(mHash, message, 256);
	
	/* STEP 4 */
	if (encodedMessage[EMLEN-1] != 0xbc)
		return 0;

	/* STEP 5 */
	for (index=0;index<(EMLEN-HASHLEN-1);index++){
		maskeddb[index] = encodedMessage[index];
	}
	for(index=(EMLEN-HASHLEN-1);index<(EMLEN-1);index++){
		H[index-(EMLEN-HASHLEN-1)] = encodedMessage[index];
	}
	
	/* STEP 7 */
	maskGenerationFunction(H, dbmask);
	
	/* STEP 8 */
	for(index=0;index<(EMLEN-HASHLEN-1);index++){
		db[index] = maskeddb[index] ^ dbmask[index];
	}
	
	/* STEP 10 */
	for(index=0;index<stopLimit;index++){
		if (db[index] != 0)
			return 0;
	}

	if (db[stopLimit] != 0x01)
		return 0;

	/* STEP 11 */
	for(index=0;index<SLEN;index++){
		salt[index] = db[stopLimit+1+index];
	}
	
	/* STEP 12 */
	for(index=0;index<(HASHLEN+SLEN+8);index++){
		if (index<8)
			M[index] = 0x00;
		else if (index<HASHLEN+8)
			M[index] = mHash[index-8];
		else
			M[index] = salt[index-HASHLEN-8];
	}
	
	/* STEP 13 */
	simpleHashWithLength(hash2, M, HASHLEN+SLEN+8);

	/* STEP 14 */
	for(index=0;index<HASHLEN;index++){
		if (hash2[index] != H[index])
			return 0;
	}

	return 1;
}

#endif /* VERIFYSIGNATURE_H */