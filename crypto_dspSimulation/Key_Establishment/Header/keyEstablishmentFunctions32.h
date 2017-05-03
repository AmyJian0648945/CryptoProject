#ifndef KEYESTABLISHMENTFUNCTIONS_H
#define KEYESTABLISHMENTFUNCTIONS_H

#include <stdint.h>
#include "../../library/helpfulFunctions.h"
#include "../../library/useSHA256.h"
#include "../../library/useAES.h"
#include "../../library/PRNG.h"
#include "montExponentiation32.h"

#ifndef baseLength
#define baseLength 15
#endif

#ifndef expLengthMAX
#define expLengthMAX 16
#endif

#ifndef modLength
#define modLength 16
#endif

#ifndef MAXSIZE
#define MAXSIZE 128
#endif

#ifndef HASHLEN
#define HASHLEN 32
#endif

#ifndef KEYLEN
#define KEYLEN 	16
#endif

/*nb of bytes */
#define sizeMessageAB 128
/*nb of 32 bit size words */
#define sizeModulusAB 32
#define sizePrExpAB 32
#define sizePuExpAB 1

/* Put zeros at the end of the array at the top of the array.
	Given an array of length size. If the elements at the end of the array
	are zero, the elements of the array will be shifted by one and a zero will be inserted at the first position (index zero) of the array.
*/
void repositionZeros(uint32_t *array, uint16_t size);
/* Create a number x with a random number generator.
	The length of x is random, with a value between 1 and expLengthMAX (included).
	The number x will not be equal to 0.
*/
void createExponent( uint32_t *x, uint16_t sizeX);
/* compute g^exponent modulus m.
*/
void computePartOfKey(uint32_t *g, uint32_t *m, uint32_t *exponent, uint32_t *partOfKey);
/* Key = Hash(g^exponent mod m)(bits0..128)
*/
void calculateKey(uint32_t *g, uint32_t *m, uint32_t *exponent, uint8_t *Key);
/* message = gx || gy
*/
void createMessage( uint32_t *gx, uint32_t *gy, uint8_t *message);
/* signedMessage = message ^ privateExponent mod modulus */

void signMessage(uint8_t *message, uint32_t *signedMessage, uint32_t *modulus, uint32_t *privateExponent);
/* message = signedMessage ^ publicExponent mod modulus */

void unsignMessage(uint32_t *signedMessage, uint8_t *message, uint32_t *modulus, uint32_t *publicExponent);
void encryptMessage(uint32_t *message, uint8_t *encryptedMessage, uint8_t *key);
void decryptMessage(uint8_t *message, uint32_t *decryptedMessage, uint8_t *key);


void signAndEncryptMessage(uint8_t *message, uint8_t *encryptedMessage, uint32_t *modulus, uint32_t *privateExponent, uint8_t *key);
void decryptAndUnsignMessage(uint8_t *message, uint8_t *unsignedMessage, uint8_t *key, uint32_t *modulus, uint32_t *publicExponent);

/* Reformatting the array
	From 8 bit words to 16 bit words.
	uint8_t *input = array of 8 bit words (input).
	uint16_t *output = array of 16 bit words (output).
	size = 2 * number of elements in input
		 = number of elements in output
*/
void from8to32(uint8_t *input, uint32_t *output, uint16_t size);
/* Reformatting the array.
	From 16 bit words to 8 bit words.
	Inputs:
		uint16_t *input = array of 16 words (input).
		uint8_t *output = array of 8 words (output).
		size = number of elements in input
			 = 2 * number of elements in output
*/
void from32to8(uint32_t *input, uint8_t *output, uint16_t size);

#endif


