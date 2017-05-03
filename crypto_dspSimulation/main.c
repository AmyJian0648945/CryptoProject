#include<stdint.h>
#include<string.h>
#include<stdio.h>

#ifndef baseLength
/* #define baseLength 30 */
#define baseLength 15
#endif

#ifndef modLength
/* #define modLength 32 */
#define modLength 16
#endif

#ifndef expLengthMAX
/* #define expLengthMAX 32 */
#define expLengthMAX 16
#endif

/*nb of bytes */
#define sizeMessageAB 128
/*nb of 32 bit size words */
#define sizeModulusAB 32
#define sizePrExpAB 32
#define sizePuExpAB 1
/* #define sizeMessageAB 128
#define sizeModulusAB 64
#define sizePrExpAB 64
#define sizePuExpAB 2 */

#define PRINT

#include "library/helpfulFunctions.h"
#include "library/sha2.h"
#include "library/useSHA256.h"
#include "library/aes.h"
#include "library/useAES.h"
#include "library/hmac.h"
#include "library/PRNG.h"
#include "library/encryptDecrypt.h"
#include "Key_Establishment/Header/additionalFunctions32.h"
#include "Key_Establishment/Header/montExponentiation32.h"
#include "Key_Establishment/Header/signatureMessage.h"
#include "Key_Establishment/Header/verifySignature.h"
#include "Key_Establishment/Header/keyEstablishmentFunctions32.h"

int main(void){

	uint8_t K1[encryptKeyLength] = {0};
	
	uint8_t keyInString[encryptKeyLength] = {0};
	uint8_t key[encryptKeyLength] = {0};
    uint8_t data[MAX_MESSAGE_LENGTH] = "AAhello there 0123456789 BBhello there 0123456789 CChello there 0123456789 DDhello there 0123456789 EEhello there 0123456789";
    uint8_t ciphertext[IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + SHA256_DIGEST_LENGTH] = {0};
    uint8_t plaintext[MAX_MESSAGE_LENGTH] = {0};
    uint8_t tempLength = 0;
    uint8_t msgSize[1] = {0};

    /* Processing keys = make sure its in char */
    uint16_t keySize = (uint16_t) strlen((char*)key); 	/* Not guaranteed to work if first input is 0 */


	/*** DATA TRANSMISSION ***/
#ifdef PRINT
	printf("Start of the Data Transmission...\n");
#endif
	copyArray8(K1, key, encryptKeyLength);
    msgSize[0] = (uint16_t) strlen((char*)data); 	/* Not guaranteed to work if first input is 0*/

    hexToString(keyInString, key, keySize);
	
	encrypt(ciphertext, msgSize, data, keyInString, keySize*2);
	decrypt(plaintext, msgSize, ciphertext, keyInString, keySize*2);
	tempLength = (uint8_t) msgSize[0]; 

	/* Printout operation summary */
#ifdef PRINT
	printf("Plaintext before encryption: "); printCharNoSpaces(data, tempLength);
	printf("\nCiphertext after encryption: "); printArrayNoSpaces(ciphertext, tempLength );
	printf("\nPlaintext after decryption: "); printCharNoSpaces(plaintext, tempLength);
#endif



	
	return 0;
}


