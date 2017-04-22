#ifndef KEYESTABLISHMENTFUNCTIONS_H
#define KEYESTABLISHMENTFUNCTIONS_H

#include <stdint.h>

#ifndef HELPFULFUNCTIONS_H
#include "../library/helpfulFunctions.h"
#define HELPFULFUNCTIONS_H
#endif

#ifndef USESHA256_H
#include "../library/usesha256.h"
#define USESHA256_H
#endif

#ifndef USEAES_H
#include "../library/useAES.h"
#define USEAES_H
#endif

#ifndef MONTEXPONENTIATION_H
#include "../Montgomery_Exponentiation/montExponentiation.h"
#define MONTEXPONENTIATION_H
#endif

#ifndef PRNG_H
#include "../library/PRNG.h"
#define PRNG_H
#endif

#ifndef FORMATTING_H
#include "formatting.h"
#define FORMATTING_H
#endif

#define expLength 128
#define modLength 64
#define MAXSIZE 256
#define HASHSIZE 32

/* Put zeros at the end of the array at the top of the array.
	Given an array of length size. If the elements at the end of the array
	are zero, the elements of the array will be shifted by one and a zero will be inserted at the first position (index zero) of the array.
*/
void repositionZeros(uint16_t *array, uint16_t size);
/* Create a number x with a random number generator.
	The length of x is random, with a value between 1 and expLength (included).
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
void createMessage( uint16_t *gx, uint16_t *gy, uint8_t *message, uint16_t baseLength);
/* signedMessage = message ^ privateExponent mod modulus
*/
void signMessage(uint8_t *message, uint16_t *signedMessage, uint16_t *modulus, uint16_t *privateExponent, uint16_t sizeMessage, uint16_t sizeMod, uint16_t sizePrivateExp);
/* message = signedMessage ^ publicExponent mod modulus
*/
void unsignMessage(uint16_t *signedMessage, uint8_t *message, uint16_t *modulus, uint16_t *publicExponent, uint16_t sizeSignedMessage, uint16_t sizeMod, uint16_t sizePublicExp);
void encryptMessage(uint16_t *message, uint8_t *encryptedMessage, uint16_t sizeMessage, uint8_t *key);
void decryptMessage(uint8_t *message, uint16_t *decryptedMessage, uint16_t sizeMessage, uint8_t *key);

#endif


