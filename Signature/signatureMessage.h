#ifndef SIGNATUREMESSAGE_H
#define SIGNATUREMESSAGE_H

#include "maskGenerationFunction.h"

#define EMLEN	256
#define	HLEN	32
#define	SLEN	32

/*
	Implementation of the signing of a message via means of the EMSA-PSS algorithm, used in the RSAPSS algorithm.
	The latter is used for phase 1: Key Agreement to check the identity of the other party (signature).
	uint8_t *message = message to be encoded (input)
	uint8_t *encodedMessage = message after the encoding (output).
*/
uint16_t signatureMessage(uint8_t *message, uint8_t *encodedMessage){

	uint8_t hash1[HLEN] = {0};
	uint8_t salt[SLEN] = {0};
	uint8_t result[HLEN+SLEN+8] = {0};
	uint8_t hash2[HLEN] = {0};
	uint8_t ps[EMLEN-HLEN-SLEN-2] = {0};
	uint8_t db[EMLEN-HLEN-1] = {0};
	uint8_t dbmask[EMLEN-HLEN-1] = {0};
	uint8_t maskeddb[EMLEN-HLEN-1] = {0};
	int k;


	/* STEP 2 */
	simpleHashWithLength(hash1, message, EMLEN);

	/* STEP 3 */
	if (EMLEN < HLEN + SLEN + 2)
		return 0;
	
	/* STEP 4 */
	RNG(salt,SLEN);

	/* STEP 5 */
	for (k=0; k<(HLEN+SLEN+8); k++){
		if (k<8)
			result[k] = 0x00;
		else if (k < (8+HLEN))
			result[k] = hash1[k-8];
		else
			result[k] = salt[k-(8+HLEN)];
	}
	
	/* STEP 6 */
	simpleHashWithLength(hash2, result, HLEN+SLEN+8);

	/* STEP 7 */
	for (k=0;k<(EMLEN-HLEN-SLEN-2);k++){
		ps[k] = 0;
	}

	/* STEP 8 */
	for (k=0;k<(EMLEN-HLEN-1);k++){
		if (k<(EMLEN-HLEN-SLEN-2))
			db[k] = ps[k];
		else if (k<(EMLEN-HLEN-SLEN-1))
			db[k] = 0x01;
		else
			db[k] = salt[k-(EMLEN-HLEN-SLEN-1)];
	}
	
	/* STEP 9 - mask generation function */
	maskGenerationFunction(hash2,dbmask);

	/* STEP 10 */
	for (k=0;k<(EMLEN-HLEN-1);k++){
		maskeddb[k] = db[k] ^ dbmask[k];
	}
	
	/* STEP 12 */
	for (k=0;k<EMLEN;k++){
		if (k<(EMLEN-HLEN-1))
			encodedMessage[k] = maskeddb[k];
		else if (k<(EMLEN-1))
			encodedMessage[k] = hash2[k-(EMLEN-HLEN-1)];
		else
			encodedMessage[k] = 0xbc;
	}

	return 1;
}

#endif /* SIGNATUREMESSAGE_H */