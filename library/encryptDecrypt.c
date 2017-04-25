
#include "encryptDecrypt.h"


void encryptHMAC(uint8_t* output, uint16_t* msgLength, uint8_t* data, uint8_t* inputKey, uint16_t keyLength){
	uint8_t key[encryptKeyLength + macKeyLength] = {0};
	uint8_t macKey_String[macKeyLength*2] = {0};
	uint8_t IV[IVlength] = {0};
	
	uint16_t IV_ciphertextLength = 0;
	uint8_t IVciphertextConcat[IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + 16] = {0}; /* 16 is a safety number */
	uint8_t IVciphertextConcat_String[(IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + 16)*2] = {0};
	uint8_t hmacData[SHA256_DIGEST_LENGTH] = {0};

	printf(">> Entering encryption...\n");

	/* (1) Hash the key; k = {encryptKey, macKey} */
	simpleHashWithLength(key, inputKey, keyLength); /*input = STRING; output = HEX */
	hexToString(macKey_String, key+encryptKeyLength, encryptKeyLength); /*Key for HMAC must be in string*/

	/* (2) Generate a random IV of 128 bits. */
	RNG(IV, IVlength); /* output = HEX */

	/* (3) Pad the data until length is 16x */
	padding(data, msgLength);

	/* (4) Encrypt the data, using: paddedData, IV, key */
	aesCBCencrypt(output, data, msgLength, IV, key);
	
	/* IVciphertextConcat = IV || C */
	copyArrayFrom0(IVciphertextConcat, IV, IVlength);
	copyArray(IVciphertextConcat, output, IVlength, msgLength[0]);

	/* get the length of the current array */
	IV_ciphertextLength = IVlength + msgLength[0];

	/* convert key to string (it was in hex, after the has), and the data as well (after AES, it was hex) */
	hexToString(IVciphertextConcat_String, IVciphertextConcat, IV_ciphertextLength);
	
	/* (5) HMAC */
	hmac(hmacData, macKey_String, IVciphertextConcat_String, macKeyLength*2, IV_ciphertextLength*2);

	/* (6) {IV || C || HMAC(IV || C) } = regist key */
	copyArrayFrom0(output, IVciphertextConcat, IV_ciphertextLength);
	copyArray(output, hmacData, IV_ciphertextLength, SHA256_DIGEST_LENGTH);
	
	/* Update message length */
	msgLength[0] = IV_ciphertextLength + SHA256_DIGEST_LENGTH;
	printf(">> Encryption ended\n"); 
 }


void decryptHMAC(uint8_t* output, uint16_t* msgLength, uint8_t* registKey, uint8_t* inputKey, uint16_t keyLength){
	uint8_t key[encryptKeyLength + macKeyLength] = {0};	
	uint8_t hmacData[SHA256_DIGEST_LENGTH] = {0};
	uint8_t macKey_String[macKeyLength*2] = {0};
	uint8_t registKey_String[(IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + SHA256_DIGEST_LENGTH)*2] = {0};
	uint16_t temp = 0;

	printf(">> Entering decryption...\n");

	/* * * Verification step; if failed, abort * * */
	
	/* Calculate the key (by hashing) */
	simpleHashWithLength(key, inputKey, keyLength); /*input = STRING; output = HEX */
	hexToString(macKey_String, key+encryptKeyLength, encryptKeyLength);

	/* Turn the hashed value into string */
	hexToString(registKey_String, registKey, *msgLength);

	/* (1) Compute HMAC: of {IV || C} = macMsg, with macKey */
	hmac(hmacData, macKey_String, registKey_String, macKeyLength*2, (*msgLength-SHA256_DIGEST_LENGTH)*2);

	/* (2) Compare the HMAC with the registKey's HMAC */
	seeTheDifference(hmacData, registKey+(*msgLength-SHA256_DIGEST_LENGTH), SHA256_DIGEST_LENGTH);
	

	/* * * Decryption step; verification step ends above * * */
	temp = *msgLength - SHA256_DIGEST_LENGTH - IVlength;

	aesCBCdecrypt(output, registKey + IVlength, temp, registKey, key);

	/* update message length */
	*msgLength = *msgLength - SHA256_DIGEST_LENGTH - IVlength;

	printf(">> Decryption ended\n"); 
}


void encrypt(uint8_t* output, uint8_t* msgLength, uint8_t* data, uint8_t* inputKey, uint16_t keyLength){
	uint8_t key[encryptKeyLength + macKeyLength] = {0};
	uint8_t macKey_String[macKeyLength*2] = {0};
	uint8_t IV[IVlength] = {0};

	uint8_t IV_ciphertextLength = 0;
	uint8_t IVciphertextConcat[IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + 16] = {0}; /* 16 is a safety number */
	uint8_t IVciphertextConcat_String[(IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + 16)*2] = {0};

	printf(">> Entering encryption...\n");

	/* (1) Hash the key; k = {encryptKey, macKey} */
	simpleHashWithLength(key, inputKey, keyLength); /*input = STRING; output = HEX */
	hexToString(macKey_String, key+encryptKeyLength, encryptKeyLength); /*Key for HMAC must be in string*/

	/* (2) Generate a random IV of 128 bits. */
	RNG(IV, IVlength); /* output = HEX */

	/* (3) Pad the data until length is 16x */
	padding(data, msgLength);

	/* (4) Encrypt the data, using: paddedData, IV, key */
	aesCBCencrypt(output, data, msgLength, IV, key);
	
	/* IVciphertextConcat = IV || C */
	copyArrayFrom0(IVciphertextConcat, IV, IVlength);
	copyArray(IVciphertextConcat, output, IVlength, msgLength[0]);

	/* get the length of the current array */
	IV_ciphertextLength = IVlength + msgLength[0];

	/* convert key to string (it was in hex, after the has), and the data as well (after AES, it was hex) */
	hexToString(IVciphertextConcat_String, IVciphertextConcat, IV_ciphertextLength);
	
	/* (6) {IV || C || HMAC(IV || C) } = regist key */
	copyArrayFrom0(output, IVciphertextConcat, IV_ciphertextLength);
	
	/* Update message length */
	msgLength[0] = IV_ciphertextLength;
	printf(">> Encryption ended\n"); 
 }


void decrypt(uint8_t* output, uint8_t* msgLength, uint8_t* registKey, uint8_t* inputKey, uint16_t keyLength){
	uint8_t key[encryptKeyLength + macKeyLength] = {0};	
	uint8_t macKey_String[macKeyLength*2] = {0};
	uint8_t registKey_String[(IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + SHA256_DIGEST_LENGTH)*2] = {0};
	uint8_t temp = 0;

	printf(">> Entering decryption...\n");

	/* * * Verification step; if failed, abort * * */
	
	/* Calculate the key (by hashing) */
	simpleHashWithLength(key, inputKey, keyLength); /*input = STRING; output = HEX */
	hexToString(macKey_String, key+encryptKeyLength, encryptKeyLength);

	/* Turn the hashed value into string */
	hexToString(registKey_String, registKey, *msgLength);

	/* * * Decryption step; verification step ends above * * */
	temp = *msgLength - IVlength;

	aesCBCdecrypt(output, registKey + IVlength, temp, registKey, key);

	/* update message length */
	*msgLength = *msgLength - IVlength;

	printf(">> Decryption ended\n"); 
}






/* Operation:
Encryption
(1)	Hash the key K with SHA-256 so as to get 256 bits of "key material". 
	Split that hash into two halves: 128 bits for encryption (encryptKey), 128 bits for MAC (macKey).

(2)	Generate a random IV of 128 bits. You need a new one every time you encrypt. 

(3) Pad the data (usual PKCS#5 padding) so that its length is a multiple of the AES block size (16 bytes).

(4)	Encrypt the data with AES in CBC mode, using the IV generated just above, and Ke as key. Let's call C the resulting ciphertext.

(5)	Compute HMAC/SHA-256 with key Km over the concatenation of IV and C, in that order. Call M the resulting value. 
	// It is crucial that the IV is part of the input to HMAC.

(6)	Concatenate IV, C and M, in that order. This is your "registration key".

Decryption
(7)	When receiving a registration request, first verify the HMAC (by recomputing it), then (and only then) proceed to the decryption step.

*/




/* * * * * Algorithm subparts: * * * * * 

	H(K XOR opad, H(K XOR ipad, msg))
=	H(  result2 , H(  result1 , msg))	...(1)
=	H(  result2 , 	      output	)	...(2)
=	 	  		output	 				...(3)

* * * * * * * * * * * * * * * * * * * * */


