#ifndef KEYESTABLISHMENTFUNCTIONS_H
#define KEYESTABLISHMENTFUNCTIONS_H

#include <stdint.h>
#include "../../library/helpfulFunctions.h"
#include "../../library/useSHA256.h"
#include "../../library/useAES.h"
#include "../../library/PRNG.h"
#include "montExponentiation.h"

#ifndef expLengthMAX
#define expLengthMAX 32
#endif

#ifndef modLength
#define modLength 32
#endif

#ifndef MAXSIZE
#define MAXSIZE 256
#endif

#ifndef HASHLEN
#define HASHLEN 32
#endif

#define sizeMessageAB 128
#define sizeModulusAB 64
#define sizePrExpAB 64
#define sizePuExpAB 2

/* Put zeros at the end of the array at the top of the array.
	Given an array of length size. If the elements at the end of the array
	are zero, the elements of the array will be shifted by one and a zero will be inserted at the first position (index zero) of the array.
*/
void repositionZeros(uint16_t *array, uint16_t size);
/* Create a number x with a random number generator.
	The length of x is random, with a value between 1 and expLengthMAX (included).
	The number x will not be equal to 0.
*/
void createExponent( uint16_t *x, uint16_t sizeX);
/* compute g^exponent modulus m.
*/
void computePartOfKey(uint16_t *g, uint16_t *m, uint16_t *exponent, uint16_t *partOfKey, uint16_t sizeG, uint16_t sizeM, uint16_t sizeExp);
/* Key = Hash(g^exponent mod m)(bits0..128)
*/
void calculateKey(uint16_t *g, uint16_t *m, uint16_t *exponent, uint8_t *Key, uint16_t sizeG, uint16_t sizeM, uint16_t sizeExp);
/* message = gx || gy
*/
void createMessage( uint16_t *gx, uint16_t *gy, uint8_t *message, uint16_t sizegxgy);
/* signedMessage = message ^ privateExponent mod modulus
*/
void signMessage(uint8_t *message, uint16_t *signedMessage, uint16_t *modulus, uint16_t *privateExponent, uint16_t sizeMessage, uint16_t sizeMod, uint16_t sizePrivateExp);
/* message = signedMessage ^ publicExponent mod modulus
*/
void unsignMessage(uint16_t *signedMessage, uint8_t *message, uint16_t *modulus, uint16_t *publicExponent, uint16_t sizeSignedMessage, uint16_t sizeMod, uint16_t sizePublicExp);
void encryptMessage(uint16_t *message, uint8_t *encryptedMessage, uint16_t sizeMessage, uint8_t *key);
void decryptMessage(uint8_t *message, uint16_t *decryptedMessage, uint16_t sizeMessage, uint8_t *key);


void signAndEncryptMessage(uint8_t *message, uint8_t *encryptedMessage, uint16_t *modulus, uint16_t *privateExponent, uint8_t *key);
void decryptAndUnsignMessage(uint8_t *message, uint8_t *unsignedMessage, uint8_t *key, uint16_t *modulus, uint16_t *publicExponent);

/* Reformatting the array
	From 8 bit words to 16 bit words.
	uint8_t *input = array of 8 bit words (input).
	uint16_t *output = array of 16 bit words (output).
	size = 2 * number of elements in input
		 = number of elements in output
*/
void from8to16(uint8_t *input, uint16_t *output, uint16_t size);
/* Reformatting the array.
	From 16 bit words to 8 bit words.
	Inputs:
		uint16_t *input = array of 16 words (input).
		uint8_t *output = array of 8 words (output).
		size = number of elements in input
			 = 2 * number of elements in output
*/
void from16to8(uint16_t *input, uint8_t *output, uint16_t size);

#endif


