#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* * * Needed for encrypt.h * * */
#define encryptKeyLength 	16
#define macKeyLength	 	16
#define IVlength			16

/* * * Needed for hmac.h * * */
#define DATA_BLOCK_SIZE         64

#define MAX_MESSAGE_LENGTH 			 	500 // CURRENTLY A PATCH: ADJUST THIS VARIABLE after discussion with the processing group!!
#define MAX_TRANSMISSION_BLOCK_LENGTH 	512 // CURRENTLY A PATCH: needs to be 16x

#include "helpfulFunctions.h"
#include "sha2/useSHA256.h"
#include "CPRNG/pseudoRandNumGenerator.h"
#include "HMAC/hmac.h"
#include "aes/useAES.h"
#include "dataTransmission/encrypt.h"









int main()
{
    uint8_t keyInString[encryptKeyLength] = {0};
    uint8_t key[encryptKeyLength] = {0xAA, 0x11, 0x22, 0x33, 0x44, 0xAA, 0XBB};
    uint8_t data[MAX_MESSAGE_LENGTH] = "hello there 0123456789";

    // Processing keys = make sure its in char
    uint16_t keySize = strlen(key); 	/* Not guaranteed to work if first input is 0*/
    uint16_t msgSize = strlen(data); 	/* Not guaranteed to work if first input is 0*/

    hexToString(keyInString, key, keySize);
	encrypt(keyInString, data, keySize*2, msgSize);
	// find a way to detect key + message length?

	




	





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
