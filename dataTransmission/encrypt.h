/* * * * * * * * * * * * * * * * * * * * * * * *
This file encrypts the message, and outputs the ciphertext and corresponding 
information (HMAC and IV) to allow for decryption. 

--> Protocol Specifications:
	Encryption method: AES-128, CBC Mode
	Message authentication: HMAC-SHA256
	Encryption and MAC assembly: Encrypt-then-MAC
	Padding: PKCS#7



*** For more info about Encrypt-then-Mac, see https://goo.gl/8wAanl
*** For more info about PKCS#7, see https://tools.ietf.org/html/rfc5652#section-6.3
* * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef ENCRYPT_H
#define ENCRYPT_H



/* * * DEBUGGING STAAAAAATION! * * * * * * * * */ 
//#define step1 1
//#define step3 1
#define step4 1

/* * * Uncomment if you want to activate! * * */





// Function Introduction
void encrypt(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);
void decrypt(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);



/*	 {		IV || C 	  || HMAC(		IV || C 	  }  *
 * = { IVciphertextConcat || HMAC( IVciphertextConcat }  *
 * =  				registKey (i.e. output)				 *
 */
// Function Definition
void encrypt(uint8_t* output, uint8_t* msgLength, uint8_t* data, uint8_t* inputKey, uint16_t keyLength){
	uint8_t key[encryptKeyLength + macKeyLength] = {0};
	uint8_t macKey_String[macKeyLength*2] = {0};
	uint8_t IV[IVlength] = {0};
	uint8_t paddedData[MAX_TRANSMISSION_BLOCK_LENGTH] = {0};

	uint8_t IV_ciphertextLength = 0;
	uint8_t IVciphertextConcat[IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + 16] = {0}; // 16 is a safety number
	uint8_t IVciphertextConcat_String[(IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + 16)*2] = {0};
	uint8_t hmacData[SHA256_DIGEST_LENGTH] = {0};

	printf(">> Entering encryption...\n");

	// (1) Hash the key; k = {encryptKey, macKey} 
	simpleHashWithLength(key, inputKey, keyLength); /*input = STRING; output = HEX */
	hexToString(macKey_String, key+encryptKeyLength, encryptKeyLength); /*Key for HMAC must be in string*/

	// (2) Generate a random IV of 128 bits.
	RNG(IV, IVlength); /* output = HEX */

	// (3) Pad the data until length is 16x 
	padding(data, msgLength);

	// (4) Encrypt the data, using: paddedData, IV, key 
	aesCBCencrypt(output, data, msgLength, IV, key);

	// IVciphertextConcat = IV || C
	copyArrayFrom0(IVciphertextConcat, IV, IVlength);
	copyArray(IVciphertextConcat, output, IVlength, *msgLength);

	// get the length of the current array
	IV_ciphertextLength = IVlength + *msgLength;

	// convert key to string (it was in hex, after the has), and the data as well (after AES, it was hex)
	hexToString(IVciphertextConcat_String, IVciphertextConcat, IV_ciphertextLength);
	
	// (5) HMAC
	hmac(hmacData, macKey_String, IVciphertextConcat_String, macKeyLength*2, IV_ciphertextLength*2);

	// (6) {IV || C || HMAC(IV || C) } = regist key
	copyArrayFrom0(output, IVciphertextConcat, IV_ciphertextLength);
	copyArray(output, hmacData, IV_ciphertextLength, SHA256_DIGEST_LENGTH);
	
	// Update message length
	*msgLength = IV_ciphertextLength + SHA256_DIGEST_LENGTH;
	printf(">> Encryption successful!"); 
 }


void decrypt(uint8_t* output, uint8_t* msgLength, uint8_t* registKey, uint8_t* inputKey, uint16_t keyLength){
	uint8_t key[encryptKeyLength + macKeyLength] = {0};	
	uint8_t hmacData[SHA256_DIGEST_LENGTH] = {0};
	uint8_t macKey_String[macKeyLength*2] = {0};
	uint8_t registKey_String[(IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + SHA256_DIGEST_LENGTH)*2] = {0};

	printf(">> Entering decryption...\n");

	/* * * Verification step; if failed, abort * * */
	/* * * {IV || C || HMAC(IV || C) } = regist key * * */
	// Calculate the key (by hashing)
	simpleHashWithLength(key, inputKey, keyLength); /*input = STRING; output = HEX */
	hexToString(macKey_String, key+encryptKeyLength, encryptKeyLength);

	// Turn the hashed value into string 
	hexToString(registKey_String, registKey, *msgLength);
	
	// (1) Compute HMAC: of {IV || C} = macMsg, with macKey
	hmac(hmacData, macKey_String, registKey_String, macKeyLength*2, (*msgLength-SHA256_DIGEST_LENGTH)*2);

	// (2) Compare the HMAC with the registKey's HMAC
	seeTheDifference(hmacData, registKey+(*msgLength-SHA256_DIGEST_LENGTH), SHA256_DIGEST_LENGTH);
	
	/* * * Decryption step; verification step ends above * * */


}




#endif	


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











/* Details of the implementation:
Encrypt-then-MAC:
Provides integrity of Ciphertext. Assuming the MAC shared secret has not been compromised, we ought to be able to deduce whether a given ciphertext is indeed authentic or has been forged; for example, in public key cryptography anyone can send you messages. EtM ensures you only read valid messages.
Plaintext integrity.
If the cipher scheme is malleable we need not be so concerned, since the MAC code will filter out this invalid ciphertext.
The MAC does not provide any information on the plaintext since, assuming the output of the cipher appears random, so does the MAC. In other words, we haven't carried any structure from the plaintext into the MAC code.

*/