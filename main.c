#include "library/includesDefinesMacros.h"


int main(void)
{
    uint8_t keyInString[encryptKeyLength] = {0};
    uint8_t key[encryptKeyLength] = {0xAA, 0x11, 0x22, 0x33, 0x44, 0xAA, 0XBB};
    uint8_t data[MAX_MESSAGE_LENGTH] = "hello there 0123456789 hello there 0123456789";
    uint8_t registKey[IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + SHA256_DIGEST_LENGTH] = {0};
    uint8_t plaintext[MAX_MESSAGE_LENGTH] = {0};
    uint8_t tempLength = 0;
    uint8_t msgSize[1] = {0};

    /* Processing keys = make sure its in char */
    uint16_t keySize = (uint16_t) strlen((char*)key); 	/* Not guaranteed to work if first binput is 0*/
    msgSize[0] = (uint8_t) strlen((char*)data); 	/* Not guaranteed to work if first input is 0*/

    hexToString(keyInString, key, keySize);
	
	encrypt(registKey, msgSize, data, keyInString, keySize*2);
	
	decrypt(plaintext, msgSize, registKey, keyInString, keySize*2);
	tempLength = (uint8_t) msgSize[0]; 
	/* Printout operation summary */
	
	printf("\n---\nSummary...\n---\n");
	printf("Plaintext before encryption: "); printCharNoSpaces(data, tempLength);
	printf("\nCiphertext after encryption: "); printArrayNoSpaces(registKey, tempLength );
	printf("\nPlaintext after decryption: "); printCharNoSpaces(plaintext, tempLength);
	printf("\n\n");
	

	




	





    return 0;
}

/* Operation:
-   Hash the key K with SHA-256 so as to get 256 bits of "key material". 
	Split that into two halves: 128 bits for encryption (Ke), 128 bits for MAC (Km).

-   Generate a random IV of 128 bits. 

-   Pad the data (usual PKCS#5 padding) so that its length is a multiple of the AES block size (16 bytes).

-   Encrypt the data with AES in CBC mode, using the IV generated just above, and Ke as key. Let's call C the resulting ciphertext.
Compute HMAC/SHA-256 with key Km over the concatenation of IV and C, in that order. Call M the resulting value. It is crucial that the IV is part of the input to HMAC.

-   Concatenate IV, C and M, in that order. This is your "registration key".

-   When receiving a registration request, first verify the HMAC (by recomputing it), then (and only then) proceed to the decryption step.

*/
