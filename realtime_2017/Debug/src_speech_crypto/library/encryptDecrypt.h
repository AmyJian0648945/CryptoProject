/* * * * * * * * * * * * * * * * * * * * * * * *
This file encrypts the message, and outputs the ciphertext and corresponding 
information (HMAC and IV) to allow for decryption. 

--> Protocol Specifications:
	Encryption method: AES-128, CBC Mode
	Message authentication: HMAC-SHA256
	Encryption and MAC assembly: Encrypt-then-MAC
	Padding: PKCS#7
--> Note: 
	{IV || C || HMAC(IV || C) } = regist key 


*** For more info about Encrypt-then-Mac, see https://goo.gl/8wAanl
*** For more info about PKCS#7, see https://tools.ietf.org/html/rfc5652#section-6.3
* * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef ENCRYPT_H
#define ENCRYPT_H

#ifndef STDINT
#include <stdint.h>
#endif
#ifndef USESHA256_H
#include "useSHA256.h"
#endif
#ifndef USEAES_H
#include "useAES.h"
#endif
#ifndef PRNG_H
#include "PRNG.h"
#endif
#ifndef HMAC_H
#include "hmac.h"
#endif
#ifndef HELPFULFUNCTIONS_H
#include "helpfulFunctions.h"
#endif



/* Function Introduction */



void encryptHMAC(uint8_t*, uint16_t*, uint8_t*, uint8_t*, uint16_t);
	/* Encrypts with AES, and appends HMAC (in a specific way) */
void decryptHMAC(uint8_t*, uint16_t*, uint8_t*, uint8_t*, uint16_t);
	/* Decrypts with AES, and appends HMAC (in a makespecific way) */
void encrypt(uint8_t*, uint16_t*, uint8_t*, uint8_t*, uint16_t);
	/* Encrypts with AES */
void decrypt(uint8_t*, uint16_t*, uint8_t*, uint8_t*, uint16_t);
	/* Decrypts with AES */

#endif


