
#include "../Header/signatureMessage.h"

/*
	Implementation of the signing of a message via means of the EMSA-PSS algorithm, used in the RSAPSS algorithm.
	The latter is used for phase 1: Key Agreement to check the identity of the other party (signature).
	uint8_t *message = message to be encoded (input)
	uint8_t *encodedMessage = message after the encoding (output).
*/
void signatureMessage(uint8_t *message, uint8_t *encodedMessage){

	uint8_t hashResult[HASHLEN] = {0};
	uint8_t salt[SLEN] = {0};
	uint8_t result[HASHLEN+SLEN+8] = {0};
	uint8_t ps[EMLEN-HASHLEN-SLEN-2] = {0};
	uint8_t db[MASKLEN] = {0};
	uint8_t dbmask[MASKLEN] = {0};
	uint8_t maskeddb[MASKLEN] = {0};
	int k;


	/* STEP 2 */
	simpleHashWithLength(hashResult, message, EMLEN);

	/* STEP 3 */
	
	/* STEP 4 */
	RNG(salt,SLEN);

	/* STEP 5 */
	for (k=0; k<(HASHLEN+SLEN+8); k++){
		if (k<8)
			result[k] = 0x00;
		else if (k < (8+HASHLEN))
			result[k] = hashResult[k-8];
		else
			result[k] = salt[k-(8+HASHLEN)];
	}
	
	/* STEP 6 */
	simpleHashWithLength(hashResult, result, HASHLEN+SLEN+8);

	/* STEP 7 */
	for (k=0;k<(EMLEN-HASHLEN-SLEN-2);k++){
		ps[k] = 0;
	}

	/* STEP 8 */
	for (k=0;k<(MASKLEN);k++){
		if (k<(EMLEN-HASHLEN-SLEN-2))
			db[k] = ps[k];
		else if (k<(EMLEN-HASHLEN-SLEN-1))
			db[k] = 0x01;
		else
			db[k] = salt[k-(EMLEN-HASHLEN-SLEN-1)];
	}
	
	/* STEP 9 - mask generation function */
	maskGenerationFunction(hashResult,dbmask);

	/* STEP 10 */
	for (k=0;k<(MASKLEN);k++){
		maskeddb[k] = db[k] ^ dbmask[k];
	}
	
	/* STEP 12 */
	for (k=0;k<EMLEN;k++){
		if (k<(MASKLEN))
			encodedMessage[k] = maskeddb[k];
		else if (k<(EMLEN-1))
			encodedMessage[k] = hashResult[k-(MASKLEN)];
		else
			encodedMessage[k] = 0xbc;
	}
}


